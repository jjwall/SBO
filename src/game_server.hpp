#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

#include "game.hpp"
#include <vector>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>

using websocketpp::connection_hdl;
using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;

class game_server {
public:
    // Constructor to initialize the private static data members
    game_server(int p, std::shared_ptr<game> gsp);

    // Method for receiving messages from connected clients
    void on_message(connection_hdl, server::message_ptr msg);

    // Method for handling new connections
    void on_open(connection_hdl hdl);

    // Method for handling disconnections
    void on_close(connection_hdl hdl);

    // Method to send messages to all connected clients
    void broadcast(server* s, json msg);

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
    std::shared_ptr<game> game_state_ptr;
};

#endif // GAME_SERVER_HPP