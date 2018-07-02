#ifndef GAME_HPP
#define GAME_HPP

#include "entity.hpp"
#include <vector>
// #include <websocketpp/config/asio_no_tls.hpp>
// #include <websocketpp/server.hpp>
// #include <nlohmann/json.hpp>

class game {
public:
    static std::vector<entity> entity_list;
};

#endif // GAME_HPP