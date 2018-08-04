#include "entity.hpp"
#include "position_component.hpp"
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;

entity::entity(server::connection_ptr con, position_component pos) {
    // handle = hdl;
    connection = con;
    
    position = std::make_unique<position_component>(pos);
}