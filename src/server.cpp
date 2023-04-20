//
// Created by Jorge Guerra on 4/20/23.
//
#include "server.hpp"
#include "ClearCore.h"
#include "EthernetTcpServer.h"
#include <cstdint>
#include <optional>
#include <variant>

//http://khuttun.github.io/2017/02/04/implementing-state-machines-with-std-variant.html
//https://www.cppstories.com/2018/06/variant/

using namespace server;
struct disconnected_t{};
struct setup_t{};
struct connected_t{};
struct interrupted_t{};
using state_t = std::variant<disconnected_t, setup_t, connected_t, interrupted_t>;
namespace {
    constexpr int port_number = 8888;
    constexpr int max_packet_length = 100;
    constexpr int max_clients = 6;
    char out_packet_buffer[max_packet_length];
    bool use_dhcp = false; //TODO: This should be able to be configured via serial at commissioning (and on the fly?)
    std::uint32_t timeout = 5000; //TODO: This should be able to be configured via serial at commissioning (and on the fly?)
    state_t connection_state = disconnected_t();
}





