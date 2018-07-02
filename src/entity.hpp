#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <websocketpp/config/asio_no_tls.hpp>

using websocketpp::connection_hdl;

class entity {
public:
    entity(connection_hdl hdl);

    struct position {
        float x;
        float y;
        float w;
        float h;
    };

    position pos;

    connection_hdl handle;
};

#endif // ENTITY_HPP