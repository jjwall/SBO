#include "game_server.hpp"
#include "game.hpp"
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

void game_server::on_message(connection_hdl hdl, server::message_ptr msg) {
    server::connection_ptr incoming_con = websocket.get_con_from_hdl(hdl);
    json event = json::parse(msg->get_payload());

    // convert this code into "event_handler" free function
    for (int i = 0; i < game::entity_list.size(); i++) {
        if (websocket.get_con_from_hdl(game::entity_list[i].handle) == incoming_con) {
            if (event["eventType"] == "input") {
                if (event["eventData"]["key"] == "left" && event["eventData"]["state"] == "down") {
                    game::entity_list[i].pos.x -= 10;
                    std::cout << "Pos:" << game::entity_list[i].pos.x << std::endl;
                    // broadcast() -> set up position handling on frontend
                }
                if (event["eventData"]["key"] == "right" && event["eventData"]["state"] == "down") {
                    game::entity_list[i].pos.x += 10;
                    std::cout << "Pos:" << game::entity_list[i].pos.x << std::endl;
                    // broadcast() -> set up position handling on frontend
                }
            }
        }
    }
    // if (event["eventType"] == "input") {
    //     std::cout << "THE JSON = \"" << event["eventData"]["key"] << "\"" << std::endl;
    // }
}

void game_server::on_open(connection_hdl hdl) {
    entity e(hdl);
    game::entity_list.push_back(e); // -> merge connection_list with entity_list? -> yes

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