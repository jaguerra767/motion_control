//
// Created by Jorge Guerra on 4/20/23.
//
#include "server.hpp"
#include "ClearCore.h"
#include "EthernetTcpServer.h"
#include "config.h"
#include <optional>
#include <variant>
#include <etl/vector.h>


using namespace server;
namespace {
    constexpr int port_number = 8888;
    constexpr int max_packet_length = 100;
    constexpr int max_clients = 6;
    bool use_dhcp = false; //TODO: This should be able to be configured via serial at commissioning (and on the fly?)
}

struct disconnected_t{};

struct setup_t{};

struct connected_t{
    explicit connected_t(EthernetTcpServer&& server):_server(server){}
    void cycle();
private:
    void update_clients();
    void send_message(const char* message);
    etl::vector<unsigned char*, max_clients> receive_messages();
    EthernetTcpServer _server;
    etl::vector<EthernetTcpClient, max_clients> _clients;
};
void connected_t::cycle(){
    update_clients();
    EthernetMgr.Refresh();
}

void connected_t::update_clients(){
    auto new_client = _server.Accept();
    if(new_client.Connected()){
        if(!_clients.full()){
            _clients.push_back(new_client);
        }else{
            for(auto& client:_clients){
                if(!client.Connected()){
                    client = new_client;
                    break;
                }
            }
        }
        new_client.Close();
    }
}

etl::vector<unsigned char*, max_clients> connected_t::receive_messages() {
    etl::vector<unsigned char*, max_clients> recv_msg_buffer;
    for(auto& client:_clients){
        if(client.Connected()){
            unsigned char* packet_received;
            //TODO: Copied this from example but it makes no sense that you would keep looping.
            while(client.BytesAvailable()){
                client.Read(packet_received, max_packet_length);
            }
            recv_msg_buffer.push_back(packet_received);
        }
    }
    return recv_msg_buffer;
}

void connected_t::send_message(const char* message) {
    for(auto& client:_clients){
        if(client.Connected()){
            //This is from the examples, we should not be using the send message method to close connections
            if(client.Send(message)==0){
                client.Close();
                client = EthernetTcpClient();
            }
        }
    }
}


struct interrupted_t{};

using state_t = std::variant<disconnected_t, setup_t, connected_t, interrupted_t>;

struct visit_connection {
    state_t operator()(const disconnected_t&){
        if(EthernetMgr.PhyLinkActive()){
            return setup_t();
        }
    }
    state_t operator()(const setup_t&){
        EthernetMgr.Setup();
        if(use_dhcp){
            if(!EthernetMgr.DhcpBegin()){
                return disconnected_t();
            }
        }else{
            EthernetMgr.LocalIp(config::default_ip_addr);
            auto server = EthernetTcpServer(port_number);
            server.Begin();
            return connected_t(std::move(server));
        }
        return disconnected_t();
    }
    state_t operator()(connected_t& connection){
        if(EthernetMgr.PhyLinkActive()){
            connection.cycle();
            return connection;
        }else{
            return interrupted_t();
        }
    }
    state_t operator()(const interrupted_t&){
        return disconnected_t();
    }
};

void dhcp_enable(){
    use_dhcp = true;
}
void dhcp_disable(){
    use_dhcp = false;
}
namespace {
    state_t connection_state = disconnected_t();
}

void run(){
    std::visit(visit_connection(), connection_state);
}



