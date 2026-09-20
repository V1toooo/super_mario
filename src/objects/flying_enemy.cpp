#include <cmath>

#include "flying_enemy.hpp"

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(
    const Coord& top_left,
    const int width,
    const int height
)
    : RectMapMovableAdapter(top_left, width, height),
      start_x(top_left.x) {

    vspeed = 0;
    hspeed = 0.2;

}

biv::Rect FlyingEnemy::get_rect() const noexcept {
    return {top_left, width, height};
}

biv::Speed FlyingEnemy::get_speed() const noexcept {
    return {vspeed, hspeed};
}

void FlyingEnemy::move_horizontally() noexcept {
    if (std::abs(top_left.x - start_x) > 10) {
        hspeed = -hspeed;
    }

    top_left.x += hspeed;
}

void FlyingEnemy::move_vertically() noexcept {
    if (is_active()) {
        return;
    }

    if (vspeed < MAX_V_SPEED) {
        vspeed += V_ACCELERATION;
    }

    top_left.y += vspeed;
}

void FlyingEnemy::process_horizontal_static_collision(
    Rect* obj
) noexcept {
    hspeed = -hspeed;
    move_horizontally();
}

void FlyingEnemy::process_vertical_static_collision(
    Rect* obj
) noexcept {
}

void FlyingEnemy::process_mario_collision(
    Collisionable* mario
) noexcept {
    if (mario->get_speed().v > 0 &&
        mario->get_speed().v != V_ACCELERATION) {

        kill();

    } else {
        mario->kill();
    }
}

void FlyingEnemy::move_map_left() noexcept {
    RectMapMovableAdapter::move_map_left();
    start_x -= MapMovable::MAP_STEP;
}

void FlyingEnemy::move_map_right() noexcept {
    RectMapMovableAdapter::move_map_right();
    start_x += MapMovable::MAP_STEP;
}