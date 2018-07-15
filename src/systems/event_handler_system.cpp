#include "../game.hpp"
#include <iostream>
#include <vector>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;

void event_handler_system(std::vector<game::message> &msgs) {
    for (int i = 0; i < msgs.size(); i++) {
    // for (auto& msg : *msgs) {
        // handle event
        std::cout << msgs[i].event << std::endl;
        // delete evet
        msgs.erase(msgs.begin() + i);
    }
}