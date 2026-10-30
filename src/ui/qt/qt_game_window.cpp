#include "qt_game_window.hpp"

#include <map>
#include <vector>

#include <QImage>
#include <QKeyEvent>
#include <QPainter>

using biv::QtGameWindow;

namespace {
	// Размер одной клетки карты в пикселях
	const int CELL_W = 6;
	const int CELL_H = 12;

	struct Sprite {
		QImage image;
		// true - картинка повторяется в каждой клетке объекта (земля, блоки),
		// false - одна картинка растягивается на весь объект (персонажи)
		bool tiled;
	};

	// Пиксельная картинка из строк: каждый символ - цвет одного пикселя
	QImage make_image(const std::vector<const char*>& rows) {
		static const std::map<char, QColor> palette = {
			{'R', QColor(216, 40, 0)},    {'S', QColor(252, 188, 116)},
			{'B', QColor(136, 76, 0)},    {'D', QColor(96, 48, 16)},
			{'Y', QColor(252, 216, 0)},   {'O', QColor(200, 120, 40)},
			{'G', QColor(40, 170, 40)},   {'A', QColor(160, 160, 170)},
			{'W', QColor(255, 255, 255)}, {'K', QColor(0, 0, 0)},
		};
		const int w = static_cast<int>(std::char_traits<char>::length(rows[0]));
		QImage image(w, static_cast<int>(rows.size()), QImage::Format_ARGB32);
		image.fill(Qt::transparent);
		for (int y = 0; y < image.height(); y++) {
			for (int x = 0; x < w; x++) {
				auto it = palette.find(rows[y][x]);
				if (it != palette.end()) {
					image.setPixelColor(x, y, it->second);
				}
			}
		}
		return image;
	}

	const std::map<char, Sprite>& sprites() {
		static const std::map<char, Sprite> sprites = {
			{'@', {make_image({
				"..RRRR..",
				".RRRRRR.",
				".BBSSK..",
				"BSSSSSS.",
				"..SSSS..",
				".RBRRBR.",
				"RRYRRYRR",
				".BB..BB.",
			}), false}},
			{'e', {make_image({
				"..DDDD..",
				".DDDDDD.",
				"DWKDDKWD",
				"DDDDDDDD",
				".DDDDDD.",
				"..SSSS..",
				".KK..KK.",
				"KKK..KKK",
			}), false}},
			{'f', {make_image({
				"W.DDDD.W",
				"WWDDDDWW",
				"DWKDDKWD",
				"DDDDDDDD",
				".DDDDDD.",
				"..SSSS..",
				"........",
				"........",
			}), false}},
			{'j', {make_image({
				"..GGGG..",
				".GWGGWG.",
				".GKGGKG.",
				"GGGGGGGG",
				"GGKKKKGG",
				".GGGGGG.",
				"G.G..G.G",
				"GG....GG",
			}), false}},
			{'$', {make_image({
				"..YYYY..",
				".YYOYYY.",
				"YYOYYYYY",
				"YYOYYYYY",
				"YYOYYYYY",
				"YYOYYYYY",
				".YYOYYY.",
				"..YYYY..",
			}), false}},
			{'?', {make_image({
				"KKKKKKKK",
				"KYYYYYYK",
				"KYYKKYYK",
				"KYYYYKYK",
				"KYYYKYYK",
				"KYYYYYYK",
				"KYYYKYYK",
				"KKKKKKKK",
			}), false}},
			{'#', {make_image({
				"GGGG",
				"OOOD",
				"OOOD",
				"DDDD",
			}), true}},
			{'-', {make_image({
				"OOOK",
				"OOOK",
				"KKKK",
				"OKOO",
			}), true}},
			{'*', {make_image({
				"WAAA",
				"AAAA",
				"AAAA",
				"KKKK",
			}), true}},
		};
		return sprites;
	}
}

QtGameWindow::QtGameWindow(
	ConsoleGameMap* game_map,
	QtKeyboard* keyboard,
	const int frame_delay_ms,
	std::function<bool()> game_step
) : game_map(game_map), keyboard(keyboard) {
	setWindowTitle("Super Mario");
	setFixedSize(
		game_map->get_width() * CELL_W, game_map->get_height() * CELL_H
	);

	connect(&timer, &QTimer::timeout, this, [this, game_step]() {
		if (!game_step()) {
			timer.stop();
			close();
			return;
		}
		update();
	});
	timer.start(frame_delay_ms);
}

void QtGameWindow::keyPressEvent(QKeyEvent* event) {
	if (!event->isAutoRepeat()) {
		keyboard->press(event->key());
	}
}

void QtGameWindow::keyReleaseEvent(QKeyEvent* event) {
	if (!event->isAutoRepeat()) {
		keyboard->release(event->key());
	}
}

void QtGameWindow::paintEvent(QPaintEvent*) {
	QPainter painter(this);

	// Небо и вода
	painter.fillRect(rect(), QColor(92, 148, 252));
	for (int y = 0; y < game_map->get_height(); y++) {
		for (int x = 0; x < game_map->get_width(); x++) {
			if (game_map->get_cell(x, y) == '~') {
				painter.fillRect(
					x * CELL_W, y * CELL_H, CELL_W, CELL_H, QColor(32, 56, 236)
				);
			}
		}
	}

	// Объекты
	for (ConsoleUIObject* obj: game_map->get_objs()) {
		auto it = sprites().find(obj->get_brush());
		if (it == sprites().end()) {
			continue;
		}
		const Sprite& sprite = it->second;

		if (sprite.tiled) {
			for (int x = obj->get_left(); x < obj->get_right(); x++) {
				for (int y = obj->get_top(); y < obj->get_bottom(); y++) {
					painter.drawImage(
						QRect(x * CELL_W, y * CELL_H, CELL_W, CELL_H),
						sprite.image
					);
				}
			}
		} else {
			painter.drawImage(
				QRect(
					obj->get_left() * CELL_W,
					obj->get_top() * CELL_H,
					(obj->get_right() - obj->get_left()) * CELL_W,
					(obj->get_bottom() - obj->get_top()) * CELL_H
				),
				sprite.image
			);
		}
	}
}
