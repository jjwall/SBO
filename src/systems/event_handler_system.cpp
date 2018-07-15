#include "../game.hpp"
#include "../entity.hpp"
#include "position_system.hpp"
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
        for (int i = 0; i < ents.size(); i++) {
            if (ents[i].connection == msgs[j].con) {
                if (msgs[j].event["eventType"] == "position") {
                    // position_system(msgs[j].event, ents[i]);
                    handle_position_event(msgs[j].event, ents[i]);
                }
            }
        }
        // delete event
        msgs.erase(msgs.begin() + j);
    }
}