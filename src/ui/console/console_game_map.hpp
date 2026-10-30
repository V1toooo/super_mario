#pragma once

#include <vector>

#include "game_map.hpp"
#include "console_ui_obj.hpp"

namespace biv {
	class ConsoleGameMap : public GameMap {
		private:
			char** map;
			
			std::vector<ConsoleUIObject*> objs;
			
		public:
			ConsoleGameMap(const int height, const int width);
			~ConsoleGameMap();
			
			void add_obj(ConsoleUIObject*);
			void clear() noexcept override;
			char get_cell(const int x, const int y) const noexcept;
			int get_height() const noexcept;
			const std::vector<ConsoleUIObject*>& get_objs() const noexcept;
			int get_width() const noexcept;
			void refresh() noexcept override;
			void remove_obj(ConsoleUIObject*);
			void remove_objs() override;
			void show() const noexcept override;
	};
}
