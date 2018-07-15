#ifndef GAME_HPP
#define GAME_HPP

#include "base_state.hpp"
#include "entity.hpp"
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
// #include <websocketpp/config/asio_no_tls.hpp>
// #include <websocketpp/server.hpp>

class game: public base_state {
public:
    game();

    void update();

    std::vector<json> messages;

    static std::vector<entity> entity_list;
};

#endif // GAME_HPP