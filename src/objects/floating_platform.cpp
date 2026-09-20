#include <cmath>

#include "floating_platform.hpp"

using biv::FloatingPlatform;

FloatingPlatform::FloatingPlatform(
	const Coord& top_left,
	const int width,
	const int height,
	Mario* mario
)
	: RectMapMovableAdapter(top_left, width, height),
	  start_x(top_left.x),
	  mario(mario) {
	hspeed = 0.3f;
	vspeed = 0;
}

biv::Rect FloatingPlatform::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed FloatingPlatform::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void FloatingPlatform::move_horizontally() noexcept {
	if (std::abs(start_x - top_left.x) >= FLOATING_RANGE) {
		hspeed = -hspeed;
	}

	bool mario_on_platform =
		mario->get_bottom() == get_top() &&
		mario->get_right() > get_left() &&
		mario->get_left() < get_right();

	top_left.x += hspeed;

	if (mario_on_platform) {
		mario->move_horizontal_offset(hspeed);
	} else if (has_collision(mario)) {
		top_left.x -= hspeed;
		hspeed = -hspeed;
	}
}

void FloatingPlatform::move_vertically() noexcept {
}

void FloatingPlatform::move_map_left() noexcept {
	RectMapMovableAdapter::move_map_left();
	start_x -= MapMovable::MAP_STEP;
}

void FloatingPlatform::move_map_right() noexcept {
	RectMapMovableAdapter::move_map_right();
	start_x += MapMovable::MAP_STEP;
}

void FloatingPlatform::process_horizontal_static_collision(Rect*) noexcept {
}

void FloatingPlatform::process_mario_collision(Collisionable*) noexcept {
}

void FloatingPlatform::process_vertical_static_collision(Rect*) noexcept {
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}
}