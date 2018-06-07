#include <iostream>
#include <string>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_client> client;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

typedef websocketpp::server<websocketpp::config::asio> server;

void on_message(websocketpp::connection_hdl, server::message_ptr msg) {
        std::cout << msg->get_payload() << std::endl;
}

template <class T>
T parse(const std::string& s){
    T out;
    std::stringstream ss(s);
    ss >> out;
    return out;
}

int main(int argc, char* argv[]) {
    server print_server;
    
    int PORT = parse<int>(argv[1]);
    if (PORT == 0) {
        PORT = 9000;
    }

    print_server.set_message_handler(&on_message);
    print_server.set_access_channels(websocketpp::log::alevel::all);
    print_server.set_error_channels(websocketpp::log::elevel::all);

    print_server.init_asio();
    print_server.listen(PORT);
    print_server.start_accept();

    std::cout << "Listening for connections on port " << PORT << std::endl;
    // print_server.run();

    // attempt connection to lobby server
    client c;

    std::string uri = "ws://localhost:8080";

    // if (argc == 2) {
    //     uri = argv[1];
    // }

    try {
        // Set logging to be pretty verbose (everything except message payloads)
        c.set_access_channels(websocketpp::log::alevel::all);
        c.clear_access_channels(websocketpp::log::alevel::frame_payload);

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

        // Start the ASIO io_service run loop
        // this will cause a single connection to be made to the server. c.run()
        // will exit when this connection is closed.
        c.run();
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    }

    print_server.run();
}