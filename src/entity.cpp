#include "entity.hpp"

entity::entity(connection_hdl hdl) {
    handle = hdl;
    pos.x = 100;
    pos.y = 0;
    pos.w = 32;
    pos.h = 64;
}