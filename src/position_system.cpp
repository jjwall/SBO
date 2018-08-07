#include "position_system.hpp"
#include "game.hpp"
#include "networking_system.hpp"
#include "entity.hpp"
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void position_system(std::vector<entity> &ents, networking_system* networking_ptr) {
    json json_blob;
    json_blob["event_type"] = "position";

    for (int i = 0; i < ents.size(); i++) {
        if (ents[i].position) {
            if (ents[i].position->left) {
                ents[i].position->x_pos -= ents[i].position->x_vel;

                std::cout << "Pos:" << ents[i].position->x_pos << std::endl;

                json_blob["event_subtype"] = "movement";

                // get unique player number
                json_blob["event_data"] = {{"player", 1}, {"posX", ents[i].position->x_pos}};

                networking_ptr->broadcast(json_blob);
            }
            if (ents[i].position->right) {
                ents[i].position->x_pos += ents[i].position->x_vel;

                std::cout << "Pos:" << ents[i].position->x_pos << std::endl;

                json_blob["event_subtype"] = "movement";

                // get unique player number
                json_blob["event_data"] = {{"player", 1}, {"posX", ents[i].position->x_pos}};

                networking_ptr->broadcast(json_blob);
            }
        }
    }
}