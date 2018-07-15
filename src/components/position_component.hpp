#ifndef POSITION_COMPONENT_HPP
#define POSITION_COMPONENT_HPP

class position_component {
public:
    position_component(float x, float y, float xv, float yv, float w, float h);

    float x_pos;

    float y_pos;

    float x_vel;

    float y_vel;

    float width; // -> maybe move to rendering_system

    float height; // -> maybe move to rendering_system

    bool left;

    bool right;

    bool jump;
};

#endif // POSITION_COMPONENT_HPP