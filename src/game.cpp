#include "game.hpp"
#include "game_server.hpp"
#include "systems/event_handler_system.hpp"
#include <vector>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;

game::game() {
    messages = std::vector<message>();
}

void game::update() {

    event_handler_system(messages);
    // std::cout << "hey" << std::endl;
}