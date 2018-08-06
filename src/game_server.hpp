#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

#include <vector>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>

using websocketpp::connection_hdl;
using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;

class game;

class game_server {
public:
    // Constructor to initialize the private static data members
    game_server(int p);

    // Setter for setting the game_state_ptr, necessary for fully setting up game_server
    void set_game_state_ptr(game* g_state_ptr);

    // Method for receiving messages from connected clients
    void on_message(connection_hdl, server::message_ptr msg);

    // Method for handling new connections
    void on_open(connection_hdl hdl);

    // Method for handling disconnections
    void on_close(connection_hdl hdl);

    // Method to send messages to all connected clients
    void broadcast(json msg);

    // Method to poll the server for messages
    void poll();

    // Retrieves port number
    int get_port();

    // Retrieves number of connections
    int get_connections();
    
private:
    server s;
    int port;
    std::vector<server::connection_ptr> connection_list;
    game* game_state_ptr;
};

#endif // GAME_SERVER_HPP