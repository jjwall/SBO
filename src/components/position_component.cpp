#include "position_component.hpp"

position_component::position_component(float x, float y, float xv, float yv, float w, float h) {
    x_pos = x;
    
    y_pos = y;

    x_vel = xv;

    y_vel = yv;

    width = w;

    height = h;

    left = false;

    right = false;

    jump = false;
}