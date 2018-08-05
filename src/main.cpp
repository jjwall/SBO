#include "base_state.hpp"
#include "game.hpp"
#include "game_server.hpp"
#include "game_client.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std::literals;

// vector for storing all possible states
std::vector<std::shared_ptr<base_state>> states_vec;

int main(int argc, char* argv[]) {
    // for now we are going to assume we are only in the game state
    auto game_state_ptr = std::make_shared<game>();

    states_vec.push_back(game_state_ptr);

    auto g_server_ptr = std::make_shared<game_server>(std::atoi(argv[1]), game_state_ptr);

    std::cout << "Listening for connections on port " << g_server_ptr->get_port() << std::endl;

    try {
        std::string uri = "ws://localhost:8080";

        game_client g_client(uri, g_server_ptr);

        // start polling both client and server
        while (true) {
            g_server_ptr->poll();
            g_client.poll();

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