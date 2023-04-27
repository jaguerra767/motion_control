//
// Created by Jorge Guerra on 4/20/23.
//
#include "server.hpp"
#include "ClearCore.h"
#include "EthernetTcpServer.h"
#include "config.h"
#include <optional>
#include <variant>


using namespace server;
namespace {
    constexpr int port_number = 8888;
    constexpr int max_packet_length = 100;
    constexpr int max_clients = 6;
    bool use_dhcp = false; //TODO: This should be able to be configured via serial at commissioning (and on the fly?)
}

struct disconnected_t {
};

struct setup_t {
};

struct connected_t {
    explicit connected_t(EthernetTcpServer &&server) : _server(server) {}
    auto cycle() -> void;

private:
    auto update_clients() -> void;
    auto send_message(const char *message) -> void;
    auto receive_messages() -> std::array<unsigned char *, max_clients>;
    EthernetTcpServer _server;
    std::array<EthernetTcpClient, max_clients> _clients{};
};

auto connected_t::cycle() -> void {
    update_clients();
    EthernetMgr.Refresh();
}

auto connected_t::update_clients() -> void {
    auto new_client = _server.Accept();
    if (new_client.Connected()) {
        for (auto &client: _clients) {
            if (!client.Connected()) {
                client = new_client;
                break;
            }
        }
        new_client.Close();
    }
}

auto connected_t::receive_messages() -> std::array<unsigned char *, max_clients> {
    std::array<unsigned char *, max_clients> recv_msg_buffer{};
    for (auto i = 0u; i < _clients.size() - 1; i++) {
        if (_clients[i].Connected()) {
            unsigned char *packet_received;
            while (_clients[i].BytesAvailable()) {
                _clients[i].Read(packet_received, max_packet_length);
            }
            std::memcpy(recv_msg_buffer[i], packet_received, max_packet_length);
        }
    }
    return recv_msg_buffer;
}

auto connected_t::send_message(const char *message) -> void {
    for (auto &client: _clients) {
        if (client.Connected()) {
            if (client.Send(message) == 0) {
                client.Close();
                client = EthernetTcpClient();
            }
        }
    }
}


struct interrupted_t {
};

using state_t = std::variant<disconnected_t, setup_t, connected_t, interrupted_t>;
//Mom, can we have pattern matching?
//We have pattern matching at home.
//Pattern matching at home:
struct visit_connection {
    auto operator()(const disconnected_t &) -> state_t {
        if (EthernetMgr.PhyLinkActive()) {
            return setup_t();
        }
    }
    auto operator()(const setup_t &) -> state_t {
        EthernetMgr.Setup();
        if (use_dhcp) {
            if (!EthernetMgr.DhcpBegin()) {
                return disconnected_t();
            }
        } else {
            EthernetMgr.LocalIp(config::default_ip_addr);
            auto server = EthernetTcpServer(port_number);
            server.Begin();
            return connected_t(std::move(server));
        }
        return disconnected_t();
    }
    auto operator()(connected_t &connection) -> state_t {
        if (EthernetMgr.PhyLinkActive()) {
            connection.cycle();
            return connection;
        } else {
            return interrupted_t();
        }
    }
    auto operator()(const interrupted_t &) -> state_t {
        return disconnected_t();
    }
};

auto dhcp_enable() -> void {
    use_dhcp = true;
}

auto dhcp_disable() -> void {
    use_dhcp = false;
}

namespace {
    state_t connection_state = disconnected_t();
}

auto run() -> void {
    std::visit(visit_connection(), connection_state);
}



