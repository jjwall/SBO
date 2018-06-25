#include "game_server.hpp"
#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <vector>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <nlohmann/json.hpp>

using namespace std::literals;
using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
using json = nlohmann::json;

typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::server<websocketpp::config::asio> server;

class game_client {
public:
    static void on_message(client* c, connection_hdl hdl, message_ptr msg) {
        c->get_alog().write(websocketpp::log::alevel::app, "Received Reply: "+msg->get_payload());
        if (msg->get_payload() == "get connections") {
            json j;
            j[std::to_string(game_server::get_port())] = game_server::get_connections();
            std::cout << "get those DANG connections!!" << std::endl;
            // std::cout << j << std::endl;
            std::string sendMsg = j.dump();
            c->send(hdl,sendMsg,websocketpp::frame::opcode::text);
        }
        // c->close(hdl,websocketpp::close::status::normal,"");
    }

    static void on_open(client* c, connection_hdl hdl) {
        // std::string msg = "Hi from the C++!";
        // c->send(hdl,msg,websocketpp::frame::opcode::text);
        //c->close(hdl, websocketpp::close::status::normal,"");
        //c->get_alog().write(websocketpp::log::alevel::app, "Sent Message: "+msg);
    }
};

bool game_server::initialized = false;
int game_server::port;
std::vector<server::connection_ptr> game_server::connection_list;
server game_server::websocket;

int main(int argc, char* argv[]) {
    client c; // -> combine c with game_client

    game_server::init(std::atoi(argv[1]));

    game_server::websocket.set_message_handler(&game_server::on_message);
    game_server::websocket.set_open_handler(&game_server::on_open);
    game_server::websocket.set_close_handler(&game_server::on_close);
    game_server::websocket.set_access_channels(websocketpp::log::alevel::all);
    game_server::websocket.set_error_channels(websocketpp::log::elevel::all);

    game_server::websocket.init_asio();
    game_server::websocket.listen(game_server::get_port());
    game_server::websocket.start_accept();

    std::cout << "Listening for connections on port " << game_server::get_port() << std::endl;

    // attempt connection to lobby server
    std::string uri = "ws://localhost:8080";

    try {
        // Set logging to be pretty verbose (everything except message payloads)
        //c.set_access_channels(websocketpp::log::alevel::all);
        //c.clear_access_channels(websocketpp::log::alevel::frame_payload);
        //c.set_open_handler(bind(&game_client::on_open,&c,::_1));
        c.set_open_handler([&](auto hdl){ game_client::on_open(&c, hdl);});
        // Initialize ASIO
        c.init_asio();

        // Register our message handler
        c.set_message_handler(bind(&game_client::on_message,&c,::_1,::_2));

        websocketpp::lib::error_code ec;
        client::connection_ptr con = c.get_connection(uri, ec);

        if (ec) {
            std::cout << "could not create connection because: " << ec.message() << std::endl;
            return 0;
        }

        // Note that connect here only requests a connection. No network messages are
        // exchanged until the event loop starts running in the next line.
        c.connect(con);

        // con->send("hey from c++", websocketpp::frame::opcode::text);

        json test_blob;
        test_blob["eventType"] = "eventTypeTest";
        test_blob["eventSubType"] = "eventSpecifics";
        test_blob["eventData"] = {{"player", 1}, {"posX", 5}, {"posY", 3}};

        // start polling both client and server
        while (true) {
            // game_server::broadcast(&game_server::websocket, test_blob);

            game_server::websocket.poll();
            c.poll();
            std::this_thread::sleep_for(20ms);
        }
    }
    catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    }
}