#ifndef GAME_CLIENT_HPP
#define GAME_CLIENT_HPP

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

using websocketpp::connection_hdl;

typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
typedef websocketpp::client<websocketpp::config::asio_client> client;

class game_client {
public:
    static client c;

    static void on_message(client* c, connection_hdl hdl, message_ptr msg);

    static void on_open(client* c, connection_hdl hdl);
};

#endif // GAME_SERVER_HPP