#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void event_handler_system(std::vector<json> *msgs) {
    for (int i = 0; i < msgs->size(); i++) {
        // handle event
        std::cout << msgs[i] << std::endl;
        // delete event
        msgs->erase(msgs->begin() + i);
    }
}