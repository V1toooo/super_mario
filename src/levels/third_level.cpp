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

    // ---------- Платформы ----------
    ui_factory->create_ship({20, 25}, 40, 2);    // старт
    ui_factory->create_ship({70, 20}, 15, 7);    // высокий блок
    ui_factory->create_ship({95, 25}, 20, 2);    // земля после провала
    ui_factory->create_ship({125, 20}, 10, 7);   // узкий блок
    ui_factory->create_ship({145, 15}, 10, 12);  // высокая башня
    ui_factory->create_ship({165, 20}, 8, 7);    // спуск
    ui_factory->create_ship({183, 25}, 15, 2);   // короткая земля
    ui_factory->create_ship({208, 20}, 6, 7);    // островок 1
    ui_factory->create_ship({224, 15}, 6, 12);   // островок 2 (выше)
    ui_factory->create_ship({240, 20}, 6, 7);    // островок 3
    ui_factory->create_ship({256, 25}, 30, 2);   // длинная земля
    ui_factory->create_ship({296, 20}, 12, 7);   // блок
    ui_factory->create_ship({318, 15}, 8, 12);   // башня перед финалом
    ui_factory->create_ship({336, 25}, 50, 2);   // финишная площадка

    // ---------- Обычные враги ----------
    ui_factory->create_enemy({30, 5}, 3, 2);
    ui_factory->create_enemy({50, 5}, 3, 2);
    ui_factory->create_enemy({75, 5}, 3, 2);
    ui_factory->create_enemy({102, 5}, 3, 2);
    ui_factory->create_enemy({128, 5}, 3, 2);
    ui_factory->create_enemy({188, 5}, 3, 2);
    ui_factory->create_enemy({262, 5}, 3, 2);
    ui_factory->create_enemy({278, 5}, 3, 2);
    ui_factory->create_enemy({300, 5}, 3, 2);
    ui_factory->create_enemy({345, 5}, 3, 2);
    ui_factory->create_enemy({365, 5}, 3, 2);

    // ---------- Прыгающие враги ----------
    ui_factory->create_jumping_enemy({55, 5}, 3, 2);
    ui_factory->create_jumping_enemy({105, 5}, 3, 2);
    ui_factory->create_jumping_enemy({190, 5}, 3, 2);
    ui_factory->create_jumping_enemy({270, 5}, 3, 2);
    ui_factory->create_jumping_enemy({350, 5}, 3, 2);

    // ---------- Летающие враги ----------
    ui_factory->create_flying_enemy({65, 15}, 3, 2);
    ui_factory->create_flying_enemy({88, 16}, 3, 2);   // над провалом
    ui_factory->create_flying_enemy({120, 15}, 3, 2);
    ui_factory->create_flying_enemy({138, 12}, 3, 2);  // перед башней
    ui_factory->create_flying_enemy({160, 14}, 3, 2);
    ui_factory->create_flying_enemy({200, 15}, 3, 2);  // перед островками
    ui_factory->create_flying_enemy({216, 12}, 3, 2);
    ui_factory->create_flying_enemy({232, 12}, 3, 2);
    ui_factory->create_flying_enemy({248, 15}, 3, 2);
    ui_factory->create_flying_enemy({290, 15}, 3, 2);
    ui_factory->create_flying_enemy({312, 12}, 3, 2);  // у башни
    ui_factory->create_flying_enemy({330, 15}, 3, 2);
    ui_factory->create_flying_enemy({360, 16}, 3, 2);
}