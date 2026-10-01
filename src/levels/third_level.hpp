#pragma once

#include "game_level.hpp"

namespace biv {
    class ThirdLevel : public GameLevel {
        public:
            ThirdLevel(UIFactory* ui_factory);

            bool is_final() const noexcept override;
            GameLevel* get_next() override;

        protected:
            void init_data() override;

        private:
            GameLevel* next = nullptr;
    };
}