#pragma once

#include "../../engine/inc/GameEngine.hpp"

#include <SFML/Graphics.hpp>

namespace jp::game::window
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
    };
}