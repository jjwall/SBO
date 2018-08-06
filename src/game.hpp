#ifndef GAME_HPP
#define GAME_HPP

#include "base_state.hpp"
#include "entity.hpp"
// #include "game_server.hpp"
#include <vector>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;

class game_server;

class game: public base_state {
public:
    // Default constructor
    game();

    // Method to set the game server pointer property, necessary to fully set up the game class
    void set_game_server_ptr(game_server* g_server_ptr);

    // Method to update a frame of the game state
    void update();

    // Message data structure, takes a connection pointer and a json blob
    struct message {
        server::connection_ptr con;
        json event;
    };

    // Method to add messsages to the message list. Messages are handled within the event_handler_system free function
    void add_message(const message msg);

private:
    game_server* game_server_ptr;
    std::vector<message> message_list;
    std::vector<entity> entity_list;
};

#endif // GAME_HPP