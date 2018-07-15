#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void event_handler_system(std::vector<json> *msgs);