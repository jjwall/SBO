#include "game.hpp"
#include "game_server.hpp"
#include "entity.hpp"
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void position_system(std::vector<entity> &ents, game_server* g_server_ptr);
