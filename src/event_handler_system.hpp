#include "game.hpp"
#include "entity.hpp"
#include <vector>
#include <nlohmann/json.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;

void handle_player_creation_event(const game::message &msg, std::vector<entity> &ents);
// void handle_player_creation_event(const server::connection_ptr &con);

void handle_position_event(const json &event, entity &ent);

void event_handler_system(std::vector<game::message> &msgs, std::vector<entity> &ents);