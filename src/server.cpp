//
// Created by Jorge Guerra on 4/20/23.
//
#include "server.hpp"
#include "ClearCore.h"
#include "EthernetTcpServer.h"
#include "../config.h"
#include <cstdint>
#include <optional>
#include <variant>
#include <array>

//http://khuttun.github.io/2017/02/04/implementing-state-machines-with-std-variant.html
//https://www.cppstories.com/2018/06/variant/

using namespace server;
namespace {
    constexpr int port_number = 8888;
    constexpr int max_packet_length = 100;
    constexpr int max_clients = 6;
    char out_packet_buffer[max_packet_length];
    bool use_dhcp = false; //TODO: This should be able to be configured via serial at commissioning (and on the fly?)
    std::uint32_t timeout = 5000; //TODO: This should be able to be configured via serial at commissioning (and on the fly?)
}

struct disconnected_t{};

struct setup_t{};

struct connected_t{
    explicit connected_t(EthernetTcpServer&& server):_server(server){}
    void cycle();
private:
    void update_clients(EthernetTcpClient* new_client);
    std::array<unsigned char*, max_clients> receive_messages();
    EthernetTcpServer _server;
    std::array<EthernetTcpClient, max_clients> _clients;
};
void connected_t::cycle() {
    auto temp_client = _server.Accept();
    update_clients(&temp_client);
    auto messages = receive_messages();
}

void connected_t::update_clients(EthernetTcpClient* new_client){
    if(new_client->Connected()){
        for (auto& client: _clients){
            if(!client.Connected()){
                client.Close();
                client = *new_client;
            }
        }
        new_client->Close();
    }
}

std::array<unsigned char*, max_clients> connected_t::receive_messages() {
    std::array<unsigned char*, max_clients> recv_msg_buffer{};
    auto msg_count = 0u;
    for(auto& client:_clients){
        unsigned char* packet_received;
        if(client.Connected()){
            //TODO: Copied this from example but it makes no sense that you would keep looping since .Read() reads
            //the whole buffer at once rather than char by char, investigate.
            while(client.BytesAvailable()){
                client.Read(packet_received, max_packet_length);
            }
            recv_msg_buffer[msg_count] = packet_received;
        }
        msg_count++;
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
    state_t operator()(const connected_t&){

    }
    state_t operator()(const interrupted_t&){}
};


state_t connection_state = disconnected_t();
void connect(){
    const auto* state = std::get_if<disconnected_t>(&connection_state);
    if(state){
        connection_state = setup_t();
    }
}

void dhcp_enable(){
    use_dhcp = true;
}
void dhcp_disable(){
    use_dhcp = false;
}



