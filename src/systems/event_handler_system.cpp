#include "../game.hpp"
#include "../game_server.hpp"
#include "../entity.hpp"
#include <iostream>
#include <vector>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;

void event_handler_system(std::vector<game::message> &msgs, std::vector<entity> &ents) {
    for (int j = 0; j < msgs.size(); j++) {
    // for (auto& msg : *msgs) {
        // handle event
        std::cout << msgs[j].event << std::endl;
        for (int i = 0; i < ents.size(); i++) {
            if (game_server::websocket.get_con_from_hdl(ents[i].handle) == msgs[j].con) {
                if (msgs[j].event["eventType"] == "position") {
                    if (msgs[j].event["eventData"]["key"] == "left" && msgs[j].event["eventData"]["state"] == "down") {
                        ents[i].position->x_pos -= ents[i].position->x_vel; //.pos.x -= 10;
                        std::cout << "Pos:" << ents[i].position->x_pos << std::endl;
                        // broadcast() -> set up position handling on frontend
                    }
                    if (msgs[j].event["eventData"]["key"] == "right" && msgs[j].event["eventData"]["state"] == "down") {
                        ents[i].position->x_pos += ents[i].position->x_vel; //.pos.x -= 10;
                        // ents[i].pos.x += 10;
                        std::cout << "Pos:" << ents[i].position->x_pos << std::endl;
                        // broadcast() -> set up position handling on frontend
                    }
                }
            }
        }
        // delete event
        msgs.erase(msgs.begin() + j);
    }
}