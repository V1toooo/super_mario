#pragma once

#include "console_ui_obj_rect_adapter.hpp"
#include "floating_platform.hpp"
#include "mario.hpp"

namespace biv {
	class ConsoleFloatingPlatform :
		public FloatingPlatform,
		public ConsoleUIObjectRectAdapter {
		public:
			ConsoleFloatingPlatform(
				const Coord& top_left,
				const int width,
				const int height,
				Mario* mario
			);

			char get_brush() const noexcept override;
	};
}