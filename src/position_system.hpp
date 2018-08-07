#include "game.hpp"
#include "networking_system.hpp"
#include "entity.hpp"
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void position_system(std::vector<entity> &ents, networking_system* networking_ptr);
