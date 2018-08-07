#include "game.hpp"
#include "networking_system.hpp"
#include "entity.hpp"
#include "event_handler_system.hpp"
#include "position_system.hpp"
#include <vector>
// #include <websocketpp/config/asio_no_tls.hpp>
// #include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// typedef websocketpp::server<websocketpp::config::asio> server;

game::game() {
    message_list = std::vector<message>();
    entity_list = std::vector<entity>();
}

void game::set_networking_system_ptr(networking_system* networking_ptr) {
    networking_system_ptr = networking_ptr;
}

void game::update() {
    event_handler_system(message_list, entity_list);
    position_system(entity_list, networking_system_ptr);
}

void game::add_message(const message msg) {
    message_list.push_back(msg);
}