#pragma once

#include "flying_enemy.hpp"
#include "console_ui_obj_rect_adapter.hpp"

namespace biv {

class ConsoleFlyingEnemy :
	public FlyingEnemy,
	public ConsoleUIObjectRectAdapter {

public:
	ConsoleFlyingEnemy(
		const Coord& top_left,
		const int width,
		const int height
	);

	char get_brush() const noexcept override;
};

}