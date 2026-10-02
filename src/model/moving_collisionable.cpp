#include "moving_collisionable.hpp"

using biv::MovingCollisionable;

MovingCollisionable::MovingCollisionable(
    const Coord& top_left,
    int width,
    int height,
    float vspeed,
    float hspeed
)
    : Movable(top_left, width, height, hspeed, vspeed) {
}

MovingCollisionable::~MovingCollisionable() = default;