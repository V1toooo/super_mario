/**
	Игровой цикл - это обощённое представление потока событий, происходящих в игре.

	Игровой цикл:
		1. Установка параметров игры
		2. Получение пользовательского ввода
		3. Обновление внутреннего состояния игры
		4. Обновление изображения на экране
		5. Проверка того, не окончена ли игра

		*** Если игра не окончена, то возвращаемся в пункт № 2.

		6. Завершение
		
	- Какие архитектурные принципы применены при реализации игры?
	
	- На основе какого приципа ООП построен алгоритм игры?
	- Какими элементами языка С++ реализуется этот принцип?
	- Приведите примеры кода, отображающие этот прицип.
*/
#include <thread>

#include "console_ui_factory.hpp"
#include "first_level.hpp"
#include "game.hpp"
#include "game_level.hpp"
#include "game_map.hpp"
#include "keyboard.hpp"
#include "mario.hpp"
#include "os_control_settings.hpp"
#include "ui_factory.hpp"

#ifdef QT_GAME
	#include <QApplication>

	#include "console_game_map.hpp"
	#include "qt_game_window.hpp"
	#include "qt_keyboard.hpp"
#elif defined(WINDOWS_CONSOLE)
	#include "windows_control_settings.hpp"
	#include "windows_keyboard.hpp"
#elif defined(LINUX_CONSOLE)
	#include "linux_control_settings.hpp"
	#include "linux_keyboard.hpp"
	#include "ncurses.h"
#endif

#ifdef QT_GAME
/**
	В Qt игровой цикл крутит не do-while, а таймер окна:
	каждый тик таймера - это одна итерация цикла (пункты 2-5).
*/
int main(int argc, char* argv[]) {
	// 1. Установка параметров игры
	using namespace std::chrono_literals;

	QApplication app(argc, argv);

	const int map_height = 30;
	const int map_weight = 200;
	const int frame_delay_ms = 20;

	biv::QtKeyboard* keyboard = new biv::QtKeyboard();
	keyboard->on();

	biv::Game game;
	biv::UIFactory* ui_factory = new biv::ConsoleUIFactory(&game);
	biv::GameMap* game_map = ui_factory->get_game_map(map_height, map_weight);
	biv::GameLevel* game_level = new biv::FirstLevel(ui_factory);
	biv::Mario* mario = ui_factory->get_mario();

	auto game_step = [&]() {
		// 2. Получение пользовательского ввода
		switch (keyboard->get_user_input()) {
			case biv::UserInput::MAP_LEFT:
				mario->move_map_left();
				if (!game.check_static_collisions(mario)) {
					game.move_map_left();
				}
				mario->move_map_right();
				break;
			case biv::UserInput::MAP_RIGHT:
				mario->move_map_right();
				if (!game.check_static_collisions(mario)) {
					game.move_map_right();
				}
				mario->move_map_left();
				break;
			case biv::UserInput::MARIO_JUMP:
				mario->jump();
				break;
			case biv::UserInput::EXIT:
				game.finish();
				break;
		}

		// 3. Обновление внутреннего состояния игры
		game.move_objs_horizontally();
		game.check_horizontally_static_collisions();

		game.move_objs_vertically();

		game.check_mario_collision();
		game.check_vertically_static_collisions();
		game.check_moving_collisions();

		if (
			game_map->is_below_map(mario->get_top())
			|| !mario->is_active()
		) {
			game_level->restart();
			mario = ui_factory->get_mario();
			std::this_thread::sleep_for(1000ms);
		}

		if (game.is_level_end()) {
			if (!game_level->is_final()) {
				game_level = game_level->get_next();
				mario = ui_factory->get_mario();
				std::this_thread::sleep_for(1000ms);
				game.start_level();
			} else {
				game.finish();
			}
		}

		// 4. Обновление изображения на экране (перерисовку делает окно)
		game_map->refresh();

		// 5. Проверка того, не окончена ли игра
		return !game.is_finished();
	};

	biv::QtGameWindow window(
		static_cast<biv::ConsoleGameMap*>(game_map),
		keyboard,
		frame_delay_ms,
		game_step
	);
	window.show();

	// 6. Завершение - когда окно закрыто
	return app.exec();
}
#else
int main() {
	// 1. Установка параметров игры
	using namespace std::chrono_literals;
	
	const int map_height = 30;
	const int map_weight = 200;
	auto frame_delay = std::chrono::milliseconds(0);
	
	biv::OSControlSettings* control_settings = nullptr;
	biv::KeyBoard* keyboard = nullptr;
	#ifdef WINDOWS_CONSOLE
		control_settings = new biv::WindowsControlSettings();
		keyboard = new biv::WindowsKeyBoard();
		frame_delay = std::chrono::milliseconds(10);
	#elif defined(LINUX_CONSOLE)
		control_settings = new biv::LinuxControlSettings(map_height, map_weight);
		keyboard = new biv::LinuxKeyboard();
		frame_delay = std::chrono::milliseconds(50);
	#endif
	
	control_settings->init();
	keyboard->on();
	
	biv::Game game;
	biv::UIFactory* ui_factory = new biv::ConsoleUIFactory(&game);
	biv::GameMap* game_map = ui_factory->get_game_map(map_height, map_weight);
	biv::GameLevel* game_level = new biv::FirstLevel(ui_factory);
	biv::Mario* mario = ui_factory->get_mario();
	
	biv::UserInput user_input;
	do {
		// 2. Получение пользовательского ввода	
		user_input = keyboard->get_user_input();
		switch (user_input) {
			case biv::UserInput::MAP_LEFT:
				mario->move_map_left();
				if (!game.check_static_collisions(mario)) {
					game.move_map_left();
				}
				mario->move_map_right();
				break;
			case biv::UserInput::MAP_RIGHT:
				mario->move_map_right();
				if (!game.check_static_collisions(mario)) {
					game.move_map_right();
				}
				mario->move_map_left();
				break;
			case biv::UserInput::MARIO_JUMP:
				mario->jump();
				break;
			case biv::UserInput::EXIT:
				game.finish();
				break;
		}
		
		// 3. Обновление внутреннего состояния игры

		game.move_objs_horizontally();
		game.check_horizontally_static_collisions();

		game.move_objs_vertically();

		game.check_mario_collision();
		game.check_vertically_static_collisions();
		game.check_moving_collisions();
		
		if (
			game_map->is_below_map(mario->get_top())
			|| !mario->is_active()
		) {
			keyboard->off();
			keyboard->on();
			game_level->restart();
			mario = ui_factory->get_mario();
			std::this_thread::sleep_for(1000ms);
		}
		
		if (game.is_level_end()) {
			if (!game_level->is_final()) {
				game_level = game_level->get_next();
				mario = ui_factory->get_mario();
				std::this_thread::sleep_for(1000ms);
				keyboard->off();
				keyboard->on();
				game.start_level();
			} else {
				game.finish();
			}
		}
		
		// 4. Обновление изображения на экране
		game_map->refresh();
		control_settings->set_cursor_start_position();
		game_map->show();
		std::this_thread::sleep_for(frame_delay);
	} while (
		/* 5. Проверка того, не окончена ли игра */ 
		!game.is_finished()
	);
	
	// 6. Завершение
}
#endif
