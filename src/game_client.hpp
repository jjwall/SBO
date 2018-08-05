#ifndef GAME_CLIENT_HPP
#define GAME_CLIENT_HPP

#include "game_server.hpp"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

using websocketpp::connection_hdl;

typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
typedef websocketpp::client<websocketpp::config::asio_client> client;

class game_client {
public:
    // Constructor for initializing private data members
    game_client(std::string uri, std::shared_ptr<game_server> g_server_ptr);

    // Method for receiving messages from lobby server (about connection info)
    void on_message(client* c, connection_hdl hdl, message_ptr msg);

    // Method for handling newly created connection with lobby server
    void on_open(client* c, connection_hdl hdl);

    // Method to poll the client for messages
    void poll();

private:
    client c;
    std::string uri_str;
    std::shared_ptr<game_server> game_server_ptr;
};

#endif // GAME_CLIENT_HPP