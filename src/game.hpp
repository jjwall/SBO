#ifndef GAME_HPP
#define GAME_HPP

#include "base_state.hpp"
#include "entity.hpp"
#include <vector>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;

class game: public base_state {
public:
    game();

    void update();

    struct message {
        server::connection_ptr con;
        json event;
    };

    // std::tuple<server::connection_ptr, std::vector<json 
    // std::vector<std::tuple<server::connection_ptr, json>> messages;
    // std::vector<json> messages;
    std::vector<message> messages;

    static std::vector<entity> entity_list;
};

#endif // GAME_HPP