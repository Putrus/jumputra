#pragma once

#include "Wind.hpp"

#include "../../engine/inc/GameEngine.hpp"

namespace jp::game::view
{
    class Game : public engine::GameEngine
    {
    public:
        Game();
        void run() override;
        void draw();
        void event();
    private:
        sf::RenderWindow mWindow;
        Wind mWindView;
    };
}