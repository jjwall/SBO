#include "entity.hpp"
#include "components/position_component.hpp"

entity::entity(connection_hdl hdl, position_component pos) {
    handle = hdl;
    // position = std::make_unique<position_component>(pos.x_pos, pos.y_pos, pos.x_vel, pos.y_vel, pos.width, pos.height);
    position = std::make_unique<position_component>(pos);
    // pos.x = 100;
    // pos.y = 0;
    // pos.w = 32;
    // pos.h = 64;
}

//entity::~entity() {
    //position.reset();
    //delete pos;
//}