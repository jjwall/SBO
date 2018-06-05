#include <iostream>
#include <string>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

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
    print_server.run();
}