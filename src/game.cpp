#include "game.hpp"
#include "game_server.hpp"
#include "systems/event_handler_system.hpp"
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

game::game() {
    messages = std::vector<json>();
}

void game::update() {

    event_handler_system(&messages);
    // std::cout << "hey" << std::endl;
}