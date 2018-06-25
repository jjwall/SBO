#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

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

    static void init(int p);

    static void on_message(connection_hdl, server::message_ptr msg);

    static void on_open(connection_hdl hdl);

    static void on_close(connection_hdl hdl);

    static void broadcast(server* s, json msg);

    static int get_port();

    static int get_connections();
    
private:
    static bool initialized;
    static int port;
    static std::vector<server::connection_ptr> connection_list;

};

#endif // GAME_SERVER_HPP