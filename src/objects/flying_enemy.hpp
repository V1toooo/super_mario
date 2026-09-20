#pragma once

#include <cmath>

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect_map_movable_adapter.hpp"

namespace biv {

class FlyingEnemy :
    public RectMapMovableAdapter,
    public Movable,
    public Collisionable {

private:
    float start_x;

public:
    FlyingEnemy(
        const Coord& top_left,
        const int width,
        const int height
    );

    Rect get_rect() const noexcept override;
    Speed get_speed() const noexcept override;

    void move_horizontally() noexcept override;
    void move_vertically() noexcept override;

    void process_horizontal_static_collision(Rect*) noexcept override;
    void process_vertical_static_collision(Rect*) noexcept override;
    void process_mario_collision(Collisionable*) noexcept override;

    void move_map_left() noexcept override;
    void move_map_right() noexcept override;
};

}