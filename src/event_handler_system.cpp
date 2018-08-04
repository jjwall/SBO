#include "game.hpp"
#include "entity.hpp"
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

// using websocketpp::connection_hdl;

using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;

// void handle_player_creation_event(const server::connection_ptr &con, std::vector<entity> &ents) {
void handle_player_creation_event(const game::message &msg, std::vector<entity> &ents) {
    // do something with msg.event to create character class with certain stats ect.
    position_component pos(100, 0,5, 1, 32, 64); // -> hard coded values for now
    entity e(msg.con, pos);
    ents.push_back(std::move(e)); // -> merge connection_list with entity_list? -> yes
}

void handle_position_event(const json &event, entity &ent) {
    if (ent.position) {
        if (event["eventData"]["key"] == "left" && event["eventData"]["state"] == "down") {
            ent.position->left = true;
        }
        if (event["eventData"]["key"] == "right" && event["eventData"]["state"] == "down") {
            ent.position->right = true;
        }
        if (event["eventData"]["key"] == "left" && event["eventData"]["state"] == "up") {
            ent.position->left = false;
        }
        if (event["eventData"]["key"] == "right" && event["eventData"]["state"] == "up") {
            ent.position->right = false;
        }
    }
}

void event_handler_system(std::vector<game::message> &msgs, std::vector<entity> &ents) {
    for (int j = 0; j < msgs.size(); j++) {
    // for (auto& msg : *msgs) {
        // handle event
        std::cout << msgs[j].event << std::endl;

        // check for player creation event
        if (msgs[j].event["eventType"] == "newPlayer") {
            handle_player_creation_event(msgs[j], ents);
        }

        for (int i = 0; i < ents.size(); i++) {
            if (ents[i].connection) {
                if (ents[i].connection == msgs[j].con) {
                    // handle position event
                    if (msgs[j].event["eventType"] == "position") {
                        handle_position_event(msgs[j].event, ents[i]);
                    }
                    // checking for other eventTypes goes here
                }
            }
        }

        // delete message
        msgs.erase(msgs.begin() + j);
    }
}