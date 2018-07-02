#include "game_client.hpp"
#include "game_server.hpp"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
typedef websocketpp::client<websocketpp::config::asio_client> client;

void game_client::on_message(client* c, connection_hdl hdl, message_ptr msg) {
    c->get_alog().write(websocketpp::log::alevel::app, "Received Reply: "+msg->get_payload());

    if (msg->get_payload() == "get connections") {
        json port_con_info = {
            {"port", game_server::get_port()},
            {"connections", game_server::get_connections()}
        };

        std::cout << "Sending game server info from port " << game_server::get_port() << std::endl;
        c->send(hdl,port_con_info.dump(),websocketpp::frame::opcode::text);
    }
    // c->close(hdl,websocketpp::close::status::normal,"");
}

void game_client::on_open(client* c, connection_hdl hdl) {
    // std::string msg = "Hi from the C++!";
    // c->send(hdl,msg,websocketpp::frame::opcode::text);
    //c->close(hdl, websocketpp::close::status::normal,"");
    //c->get_alog().write(websocketpp::log::alevel::app, "Sent Message: "+msg);
}