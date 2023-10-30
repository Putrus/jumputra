#pragma once

#include "Wind.hpp"

#include "../../engine/inc/Engine.hpp"

namespace jp::game::view
{
    class Game : public engine::Engine
    {
    public:
        Game();
        void run() override;
        void draw();
        void event();

        void controller(engine::Character& character,
            sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key jump);
    private:
        sf::RenderWindow mWindow;
        Wind mWindView;
        sf::Event mEvent;
    };
}