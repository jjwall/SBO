#include "game_server.hpp"
#include "game.hpp"
// #include "entity.hpp"
// #include "position_component.hpp" // -> will need event for handling entity creation
#include <iostream>
#include <vector>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>

using websocketpp::connection_hdl;
using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;

game_server::game_server(int p) {
    port = p;
    
    s.set_message_handler([this](auto hdl, auto msg){ on_message(hdl, msg); });
    s.set_open_handler([this](auto hdl){ on_open(hdl); });
    s.set_close_handler([this](auto hdl){ on_close(hdl); });
    s.set_access_channels(websocketpp::log::alevel::all);
    s.set_error_channels(websocketpp::log::elevel::all);

    s.init_asio();
    s.listen(game_server::get_port());
    s.start_accept();
}

void game_server::set_game_state_ptr(game* g_state_ptr) {
    game_state_ptr = g_state_ptr;
}

void game_server::on_message(connection_hdl hdl, server::message_ptr msg) {
    server::connection_ptr incoming_con = s.get_con_from_hdl(hdl);
    json event = json::parse(msg->get_payload());
    game::message message;
    message.con = incoming_con;
    message.event = event;
    game_state_ptr->add_message(message);
}

void game_server::on_open(connection_hdl hdl) {
    server::connection_ptr con = s.get_con_from_hdl(hdl);
    connection_list.push_back(con);
    std::cout << "We gained a connection: now we have " << connection_list.size() << std::endl;
}

void game_server::on_close(connection_hdl hdl) {
    server::connection_ptr con = s.get_con_from_hdl(hdl);
    connection_list.erase(std::find(connection_list.begin(), connection_list.end(), con));
    std::cout << "We lost a connection: now we have " << connection_list.size() << std::endl;
}

void game_server::broadcast(json msg) {
    std::string msg_string = msg.dump();

    for (int i = 0; i < connection_list.size(); i++) {
        s.send(connection_list[i], msg_string, websocketpp::frame::opcode::text);
    }
}

void game_server::poll() {
    s.poll();
}

int game_server::get_port() {
    return port;
}

int game_server::get_connections() {
    return connection_list.size();
}