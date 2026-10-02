#pragma once

#include "movable.hpp"
#include "collisionable.hpp"

namespace biv {

class MovingCollisionable :
    public Movable,
    public Collisionable {
public:
    MovingCollisionable(
        const Coord& top_left,
        int width,
        int height,
        float vspeed,
        float hspeed
    );

    virtual ~MovingCollisionable();
};

}