#include "console_floating_platform.hpp"

using biv::ConsoleFloatingPlatform;

ConsoleFloatingPlatform::ConsoleFloatingPlatform(
	const Coord& top_left,
	const int width,
	const int height,
	Mario* mario
)
	: FloatingPlatform(top_left, width, height, mario) {
}

char ConsoleFloatingPlatform::get_brush() const noexcept {
	return '*';
}