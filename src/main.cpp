#include <iostream>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::server<websocketpp::config::asio> server;

void on_message(websocketpp::connection_hdl, server::message_ptr msg) {
        std::cout << msg->get_payload() << std::endl;
}

void on_open(client* c, websocketpp::connection_hdl hdl) {
    std::string msg = "Hi from the C++!";
    c->send(hdl,msg,websocketpp::frame::opcode::text);
    //c->close(hdl, websocketpp::close::status::normal,"");
    //c->get_alog().write(websocketpp::log::alevel::app, "Sent Message: "+msg);
}

int main(int argc, char* argv[]) {
    server websocket_server;
    client c;
    
    int PORT = std::atoi(argv[1]);

    websocket_server.set_message_handler(&on_message);
    websocket_server.set_access_channels(websocketpp::log::alevel::all);
    websocket_server.set_error_channels(websocketpp::log::elevel::all);

    websocket_server.init_asio();
    websocket_server.listen(PORT);
    websocket_server.start_accept();

    std::cout << "Listening for connections on port " << PORT << std::endl;

    // attempt connection to lobby server
    std::string uri = "ws://localhost:8080";

    try {
        // Set logging to be pretty verbose (everything except message payloads)
        //c.set_access_channels(websocketpp::log::alevel::all);
        //c.clear_access_channels(websocketpp::log::alevel::frame_payload);
        c.set_open_handler(bind(&on_open,&c,::_1));

        // Initialize ASIO
        c.init_asio();

        // Register our message handler
        //c.set_message_handler(bind(&on_message,&c,::_1,::_2));

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

        // start polling both client and server
        while (true) {
            c.poll();
            websocket_server.poll();
        }
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    }
}