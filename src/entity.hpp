#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "components/position_component.hpp"
#include <websocketpp/config/asio_no_tls.hpp>

using websocketpp::connection_hdl;

class entity {
public:
    entity(connection_hdl hdl, position_component pos);

    connection_hdl handle;

    std::unique_ptr<position_component> position;

    //~entity();
};

#endif // ENTITY_HPP