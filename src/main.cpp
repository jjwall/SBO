#include "base_state.hpp"
#include "game.hpp"
#include "game_server.hpp"
#include "game_client.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std::literals;

int main(int argc, char* argv[]) {
    // initialize game state
    game g_state;
    // initialize game server
    game_server g_server(std::atoi(argv[1]));
    // set game state pointer prop on game server obj
    g_server.set_game_state_ptr(&g_state);
    // set game server pointer prop on game state obj
    g_state.set_game_server_ptr(&g_server);
    // vector of all possible states (just game state for now)
    std::vector<base_state*> states_vec;
    // push game state obj on top of states vec
    states_vec.push_back(&g_state);

    std::cout << "Listening for connections on port " << g_server.get_port() << std::endl;

    try {
        // url of lobby server
        std::string uri = "ws://localhost:8080";
        // initialize game client
        game_client g_client(uri, &g_server);

        // start polling both client and server
        while (true) {
            g_server.poll();
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