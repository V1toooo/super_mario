#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect_map_movable_adapter.hpp"

namespace biv {

class JumpingEnemy :
    public RectMapMovableAdapter,
    public Movable,
    public Collisionable {

private:
    static constexpr float JUMP_STRENGTH = 1.0f;

public:
    JumpingEnemy(
        const Coord& top_left,
        const int width,
        const int height
    );

    Rect get_rect() const noexcept override;
    Speed get_speed() const noexcept override;

    void move_horizontally() noexcept override;
    void process_horizontal_static_collision(Rect*) noexcept override;
    void process_vertical_static_collision(Rect*) noexcept override;
    void process_mario_collision(Collisionable*) noexcept override;
};

}