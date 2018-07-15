#include "position_system.hpp"
#include "../game.hpp"
#include "../entity.hpp"
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void position_system(std::vector<entity> &ents) {
    for (int i = 0; i < ents.size(); i++) {
        if (ents[i].position) {
            if (ents[i].position->left) {
                ents[i].position->x_pos -= ents[i].position->x_vel;
                std::cout << "Pos:" << ents[i].position->x_pos << std::endl;
                // broadcast() -> set up position handling on frontend
            }
            if (ents[i].position->right) {
                ents[i].position->x_pos += ents[i].position->x_vel;
                std::cout << "Pos:" << ents[i].position->x_pos << std::endl;
                // broadcast() -> set up position handling on frontend
            }
        }
    }
}