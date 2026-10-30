#pragma once

#include <set>

#include "keyboard.hpp"

namespace biv {
	class QtKeyboard : public KeyBoard {
		private:
			std::set<int> pressed_keys;

		public:
			void press(const int key);
			void release(const int key);

			UserInput get_user_input() override;
			void on() override;
			void off() override;

		private:
			bool is_pressed(const int key) const noexcept;
	};
}
