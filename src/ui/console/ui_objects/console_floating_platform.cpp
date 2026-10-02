#include "console_floating_platform.hpp"

using biv::ConsoleFloatingPlatform;

ConsoleFloatingPlatform::ConsoleFloatingPlatform(
	const Coord& top_left,
	const int width,
	const int height
)
	: FloatingPlatform(top_left, width, height) {
}

char ConsoleFloatingPlatform::get_brush() const noexcept {
	return '*';
}