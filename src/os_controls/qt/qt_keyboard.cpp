#include "qt_keyboard.hpp"

#include <Qt>

using biv::QtKeyboard;
using biv::UserInput;

void QtKeyboard::press(const int key) {
	pressed_keys.insert(key);
}

void QtKeyboard::release(const int key) {
	pressed_keys.erase(key);
}

UserInput QtKeyboard::get_user_input() {
	if (is_pressed(Qt::Key_A) || is_pressed(Qt::Key_Left)) {
		return UserInput::MAP_RIGHT;
	} else if (is_pressed(Qt::Key_D) || is_pressed(Qt::Key_Right)) {
		return UserInput::MAP_LEFT;
	} else if (is_pressed(Qt::Key_Space)) {
		return UserInput::MARIO_JUMP;
	} else if (is_pressed(Qt::Key_Q)) {
		return UserInput::EXIT;
	} else {
		return UserInput::NO_INPUT;
	}
}

void QtKeyboard::on() {}
void QtKeyboard::off() {}

// ----------------------------------------------------------------------------
// 									PRIVATE
// ----------------------------------------------------------------------------
bool QtKeyboard::is_pressed(const int key) const noexcept {
	return pressed_keys.count(key) > 0;
}
