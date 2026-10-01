#include "third_level.hpp"

using biv::ThirdLevel;

ThirdLevel::ThirdLevel(UIFactory* ui_factory)
    : GameLevel(ui_factory) {
    init_data();
}

bool ThirdLevel::is_final() const noexcept {
    return true;
}

biv::GameLevel* ThirdLevel::get_next() {
    return next;
}

// --------------------------------------------------
//                    PROTECTED
// --------------------------------------------------

void ThirdLevel::init_data() {
    ui_factory->create_mario({39, 10}, 3, 3);

    ui_factory->create_ship({20, 25}, 40, 2);
    ui_factory->create_ship({70, 20}, 15, 7);
    ui_factory->create_ship({100, 25}, 30, 2);
    ui_factory->create_ship({150, 20}, 15, 7);
    ui_factory->create_ship({190, 25}, 30, 2);

    ui_factory->create_enemy({30, 5}, 3, 2);
    ui_factory->create_enemy({80, 5}, 3, 2);
    ui_factory->create_enemy({150, 5}, 3, 2);
    ui_factory->create_enemy({170, 5}, 3, 2);

    ui_factory->create_jumping_enemy({50, 5}, 3, 2);

    ui_factory->create_flying_enemy({70, 15}, 3, 2);

    ui_factory->create_flying_enemy({90, 15}, 3, 2);
}