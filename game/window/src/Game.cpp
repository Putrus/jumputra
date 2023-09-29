#include "../inc/Game.hpp"

#include <chrono>

namespace jp::game::window
{
    Game::Game() : mWindow(sf::VideoMode(480, 360), "Game"), engine::GameEngine()
    {}

    void Game::run()
    {
        //to do, now for testing
        auto begin = std::chrono::steady_clock::now();
        auto end = std::chrono::steady_clock::now();
        float time = 0.f;
        //60 frames per second
        float UPDATE_NANOSECONDS = 16666666;
        while(mWindow.isOpen())
        {
            end = std::chrono::steady_clock::now();
            time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
            begin = std::move(end);
            while (time > UPDATE_NANOSECONDS)
            {
                time -= UPDATE_NANOSECONDS;
                engine::GameEngine::update(time);
                draw();
            }
            event();
        }
    }

    void Game::draw()
    {
        mWindow.clear();
        for (const auto& platform : mPhysicsEngine->getPlatforms())
        {
            sf::Vertex line[] = 
            {
                sf::Vertex(sf::Vector2f(platform->getSegment().a.x, platform->getSegment().a.y)),
                sf::Vertex(sf::Vector2f(platform->getSegment().b.x, platform->getSegment().b.y))
            };
            mWindow.draw(line, 2, sf::Lines);
        }
        
        for (const auto& character : mCharacters)
        {
            sf::Color color = sf::Color::Red;
            sf::VertexArray rect(sf::Quads, 4);
            rect[0] = sf::Vertex({ character.getRect().left, character.getRect().top}, color);
            rect[1] = sf::Vertex({ character.getRect().getRight(), character.getRect().top}, color);
            rect[2] = sf::Vertex({ character.getRect().getRight(), character.getRect().getBottom()}, color);
            rect[3] = sf::Vertex({ character.getRect().left, character.getRect().getBottom()}, color);
            mWindow.draw(rect);
        }
        mWindow.display();
    }

    void Game::event()
    {
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mWindow.close();
            }
        }
        return;
    }
}