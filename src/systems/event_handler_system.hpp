#include "../game.hpp"
#include "../entity.hpp"
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void event_handler_system(std::vector<game::message> &msgs, std::vector<entity> &ents);

void handle_position_event(const json &event, entity &ent);