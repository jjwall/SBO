#include "game.hpp"
#include "game_server.hpp"
#include "entity.hpp"
#include "systems/event_handler_system.hpp"
#include "systems/position_system.hpp"
#include <vector>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;

game::game() {
    message_list = std::vector<message>();
    entity_list = std::vector<entity>();
}

void game::update() {
    event_handler_system(message_list, entity_list);
    position_system(entity_list);
}