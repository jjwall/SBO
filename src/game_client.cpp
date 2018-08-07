#include "game_client.hpp"
#include "networking_system.hpp"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
typedef websocketpp::client<websocketpp::config::asio_client> client;

game_client::game_client(std::string uri, networking_system* networking_ptr) {
    uri_str = uri;
    networking_system_ptr = networking_ptr;

    // Set logging to be pretty verbose (everything except message payloads)
    //c.set_access_channels(websocketpp::log::alevel::all);
    //c.clear_access_channels(websocketpp::log::alevel::frame_payload);
    c.set_open_handler([this](auto hdl){ on_open(&c, hdl); });

    // Register our message handler
    c.set_message_handler([this](auto hdl, auto msg){ on_message(&c, hdl, msg); });

    // Initialize ASIO
    c.init_asio();

    websocketpp::lib::error_code ec;
    client::connection_ptr con = c.get_connection(uri, ec);

    if (ec) {
        std::cout << "could not create connection because: " << ec.message() << std::endl;
    }

    // request connection to lobby server
    c.connect(con);
}

void game_client::on_message(client* c, connection_hdl hdl, message_ptr msg) {
    c->get_alog().write(websocketpp::log::alevel::app, "Received Reply: "+msg->get_payload());

    if (msg->get_payload() == "get connections") {
        json port_con_info = {
            {"port", networking_system_ptr->get_port()},
            {"connections", networking_system_ptr->get_connections()}
        };

        std::cout << "Sending game server info from port " << networking_system_ptr->get_port() << std::endl;
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

void game_client::poll() {
    c.poll();
}