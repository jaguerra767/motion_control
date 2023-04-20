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
    EthernetTcpClient clients[max_clients];
}

struct disconnected_t{};

struct setup_t{};

struct connected_t{
    explicit connected_t(EthernetTcpServer&& server):_server(server){}
private:
    EthernetTcpServer _server;
};

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
    state_t operator()(const connected_t&){}
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



