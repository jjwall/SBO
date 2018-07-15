#include "../game.hpp"
#include "../entity.hpp"
#include <vector>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;

void event_handler_system(std::vector<game::message> &msgs, std::vector<entity> &ents);