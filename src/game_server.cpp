#include "game_server.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>

using websocketpp::connection_hdl;
using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;

void game_server::init(int p) {
    if (initialized) throw std::runtime_error("DON'T TRY AND RE-INIT");
    initialized = true;
    port = p;
}

void game_server::on_message(connection_hdl, server::message_ptr msg) {
    std::cout << msg->get_payload() << std::endl;
}

void game_server::on_open(connection_hdl hdl) {
    server::connection_ptr con = websocket.get_con_from_hdl(hdl);

    connection_list.push_back(con);
    std::cout << "We gained a connection: now we have " << connection_list.size() << std::endl;
}

void game_server::on_close(connection_hdl hdl) {
    server::connection_ptr con = websocket.get_con_from_hdl(hdl);
    
    connection_list.erase(std::find(connection_list.begin(), connection_list.end(), con));
    std::cout << "We lost a connection: now we have " << connection_list.size() << std::endl;
}

void game_server::broadcast(server* s, json msg) {
    std::string msg_string = msg.dump();
    for (int i = 0; i < connection_list.size(); i++) {
        s->send(connection_list[i], msg_string, websocketpp::frame::opcode::text);
    }
}

int game_server::get_port() {
    return port;
}

int game_server::get_connections() {
    return connection_list.size();
}