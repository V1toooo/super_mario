/**
	Окно Qt лишь отображает символьную карту ConsoleGameMap
	и передаёт нажатия клавиш в QtKeyboard. Логика игры не меняется.
*/

#pragma once

#include <functional>

#include <QTimer>
#include <QWidget>

#include "console_game_map.hpp"
#include "qt_keyboard.hpp"

namespace biv {
	class QtGameWindow : public QWidget {
		private:
			ConsoleGameMap* game_map;
			QtKeyboard* keyboard;
			QTimer timer;

		public:
			QtGameWindow(
				ConsoleGameMap* game_map,
				QtKeyboard* keyboard,
				const int frame_delay_ms,
				// Один шаг игрового цикла. Возвращает false, если игра окончена.
				std::function<bool()> game_step
			);

		protected:
			void keyPressEvent(QKeyEvent* event) override;
			void keyReleaseEvent(QKeyEvent* event) override;
			void paintEvent(QPaintEvent* event) override;
	};
}
