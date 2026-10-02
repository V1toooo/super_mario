#pragma once

#include "moving_collisionable.hpp"
#include "rect_map_movable_adapter.hpp"

namespace biv {

class FloatingPlatform :
    public RectMapMovableAdapter,
    public MovingCollisionable {
private:
    static constexpr float FLOATING_RANGE = 5.0f;

    float start_x;

public:
    FloatingPlatform(
        const Coord& top_left,
        const int width,
        const int height
    );

    Rect get_rect() const noexcept override;
    Speed get_speed() const noexcept override;

    void move_horizontally() noexcept override;
    void move_vertically() noexcept override;

    void move_map_left() noexcept override;
    void move_map_right() noexcept override;

    void process_horizontal_static_collision(Rect*) noexcept override;
    void process_mario_collision(Collisionable*) noexcept override;
    void process_vertical_static_collision(Rect*) noexcept override;
};

}