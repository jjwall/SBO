#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "position_component.hpp"
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

// using websocketpp::connection_hdl;

typedef websocketpp::server<websocketpp::config::asio> server;

class entity {
public:
    entity(server::connection_ptr con, position_component pos); // -> one of many constructors

    // connection_hdl handle;

    server::connection_ptr connection;

    std::unique_ptr<position_component> position;

    //~entity();
};

#endif // ENTITY_HPP