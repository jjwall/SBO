#include "base_state.hpp"
#include "game.hpp"
#include "game_server.hpp"
#include "game_client.hpp"
#include <iostream>
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
using json = nlohmann::json;

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::server<websocketpp::config::asio> server;

// vector for storing all possible states
std::vector<std::shared_ptr<base_state>> states_vec;

// nothing static!!
bool game_server::initialized = false;
int game_server::port;
std::vector<server::connection_ptr> game_server::connection_list;
std::shared_ptr<game> game_server::game_state_ptr;
server game_server::websocket;
client game_client::c;
// std::vector<entity> game::entity_list;

int main(int argc, char* argv[]) {
    // for now we are going to assume we are only in the game state
    auto game_state = std::make_shared<game>();
    states_vec.push_back(game_state);

    game_server::init(std::atoi(argv[1]), game_state);

    game_server::websocket.set_message_handler(&game_server::on_message);
    game_server::websocket.set_open_handler(&game_server::on_open);
    game_server::websocket.set_close_handler(&game_server::on_close);
    game_server::websocket.set_access_channels(websocketpp::log::alevel::all);
    game_server::websocket.set_error_channels(websocketpp::log::elevel::all);

    game_server::websocket.init_asio();
    game_server::websocket.listen(game_server::get_port());
    game_server::websocket.start_accept();

    std::cout << "Listening for connections on port " << game_server::get_port() << std::endl;

    std::string uri = "ws://localhost:8080";

    try {
        // Set logging to be pretty verbose (everything except message payloads)
        //c.set_access_channels(websocketpp::log::alevel::all);
        //c.clear_access_channels(websocketpp::log::alevel::frame_payload);
        game_client::c.set_open_handler([&](auto hdl){ game_client::on_open(&game_client::c, hdl);});
        // Initialize ASIO
        game_client::c.init_asio();

        // Register our message handler
        game_client::c.set_message_handler([&](auto hdl, auto msg){ game_client::on_message(&game_client::c, hdl, msg);});

        websocketpp::lib::error_code ec;
        client::connection_ptr con = game_client::c.get_connection(uri, ec);

        if (ec) {
            std::cout << "could not create connection because: " << ec.message() << std::endl;
            return 0;
        }

        // request connection to lobby server
        game_client::c.connect(con);

        json test_blob;
        test_blob["eventType"] = "eventTypeTest";
        test_blob["eventSubType"] = "eventSpecifics";
        test_blob["eventData"] = {{"player", 1}, {"posX", 5}, {"posY", 3}};

        // start polling both client and server
        while (true) {
            // game_server::broadcast(&game_server::websocket, test_blob);

            game_server::websocket.poll();
            game_client::c.poll();

            // call update on most recently added state
            if (!states_vec.empty()) {
                states_vec.back()->update();
            }

            std::this_thread::sleep_for(20ms);
        }
    }
    catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    }
}