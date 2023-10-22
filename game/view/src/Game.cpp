#include "../inc/Game.hpp"

#include <chrono>
#include <thread>

namespace jp::game::view
{
    Game::Game() : mWindow(sf::VideoMode(480, 360), "Jumputra"),
        engine::GameEngine()
    {
        sf::View view(sf::FloatRect(0.f, 15120.f, 480.f, 360.f));
        mWindow.setView(view);
        mWindow.setVerticalSyncEnabled(true);
        //to do, now code is for testing
        addCharacter({ 200.f, 15300.f });
    }

    void Game::run()
    {
        //to do, now for testing
        auto begin = std::chrono::steady_clock::now();
        auto end = std::chrono::steady_clock::now();
        float time = 0.f;
        //60 frames per second
        float UPDATE_NANOSECONDS = 16666666;
        std::thread t(&Game::keyPressed, this);
        t.detach();
        while(mWindow.isOpen())
        {
            event();
            end = std::chrono::steady_clock::now();
            time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
            begin = std::move(end);
            while (time > UPDATE_NANOSECONDS)
            {
                time -= UPDATE_NANOSECONDS;
                engine::GameEngine::update(UPDATE_NANOSECONDS / 1000000000.f);
                if (mCharacters.size() > 0)
                {
                    mCharacters[0].update(UPDATE_NANOSECONDS / 1000000000.f);
                    if (mCharacters[0].getPosition().y < mWindow.getView().getCenter().y - 180.f - mCharacters[0].getRect().height)
                    {
                        sf::View view = mWindow.getView();
                        view.setCenter(sf::Vector2f(view.getCenter().x, view.getCenter().y - 360.f));
                        mWindow.setView(view);
                    }
                    else if (mCharacters[0].getPosition().y > mWindow.getView().getCenter().y + 180.f)
                    {

                        sf::View view = mWindow.getView();
                        view.setCenter(sf::Vector2f(view.getCenter().x, view.getCenter().y + 360.f));
                        mWindow.setView(view);
                    }
                }
                draw();
            }
        }
    }

    void Game::draw()
    {
        mWindow.clear();
        for (const auto& platform : mPhysicsEngine->getPlatforms())
        {
            sf::Color color = platform->getSurface() == physics::PlatformSurface::Slippery ? sf::Color::Cyan : sf::Color::White;
            sf::Vertex line[] = 
            {
                sf::Vertex(sf::Vector2f(platform->getSegment().a.x, platform->getSegment().a.y), color),
                sf::Vertex(sf::Vector2f(platform->getSegment().b.x, platform->getSegment().b.y), color)
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


            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    auto mp = sf::Mouse::getPosition(mWindow);
                    auto pos = math::Vector2<float>(mp.x, mp.y);
                    pos.y += mWindow.getView().getCenter().y - 180.f;
                    std::cout << pos << std::endl;
                    addCharacter(pos);
                }
            }

            if (mCharacters.size() > 0 && event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::L)
                {
                    mCharacters[0].printInfo();
                }

                if (event.key.code == sf::Keyboard::Space)
                {
                    mCharacters[0].jump();
                }

                if ((event.key.code == sf::Keyboard::A &&
                    mCharacters[0].getJumpDirection() == engine::CharacterJumpDirection::Left) ||
                    (event.key.code == sf::Keyboard::D &&
                    mCharacters[0].getJumpDirection() == engine::CharacterJumpDirection::Right))
                {
                    mCharacters[0].setJumpDirection(engine::CharacterJumpDirection::Up);
                    mCharacters[0].stop();
                }

                if (event.key.code == sf::Keyboard::R)
                {
                    mCharacters.erase(mCharacters.begin());
                }

                if (event.key.code == sf::Keyboard::T)
                {
                    float posX = std::rand() % 360 + 10;
                    addCharacter({ posX, 15200.f });
                }

                if (event.key.code == sf::Keyboard::Y)
                {
                    for (auto& character : mCharacters)
                    {
                        float power = std::rand() % 360 + 10;
                    }
                }
            }
        }
        return;
    }

    void Game::keyPressed()
    {
        while (true)
        {
            if (mCharacters.size() == 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space))
            {
                mCharacters[0].squat();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
            {
                mCharacters[0].runLeft();
                mCharacters[0].setJumpDirection(engine::CharacterJumpDirection::Left);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
            {
                mCharacters[0].runRight();
                mCharacters[0].setJumpDirection(engine::CharacterJumpDirection::Right);
            }
        }
    }
}