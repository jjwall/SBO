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
    static server websocket;

    // Initializes the private static data members
    static void init(int p, std::shared_ptr<game> gsp);

    // Method for receiving messages from connected clients
    static void on_message(connection_hdl, server::message_ptr msg);

    // Method for handling new connections
    static void on_open(connection_hdl hdl);

    // Method for handling disconnections
    static void on_close(connection_hdl hdl);

    // Method to send messages to all connected clients
    static void broadcast(server* s, json msg);

    // Retrieves port number
    static int get_port();

    // Retrieves number of connections
    static int get_connections();
    
private:
    static bool initialized;
    static int port;
    static std::vector<server::connection_ptr> connection_list;
    static std::shared_ptr<game> game_state_ptr;
};

#endif // GAME_SERVER_HPP