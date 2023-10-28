#include "../inc/Game.hpp"

#include <chrono>
#include <thread>

namespace jp::game::view
{
    Game::Game() : mWindow(sf::VideoMode(480, 360), "Jumputra"),
        engine::GameEngine(), mWindView(mPhysicsEngine->getWind())
    {
        sf::View view(sf::FloatRect(0.f, 15120.f, 480.f, 360.f));
        mWindow.setView(view);
        //mWindow.setVerticalSyncEnabled(true);
        //to do, now code is for testing
        addCharacter({ 150.f, 15300.f });
        for (int i = 0; i < 50; ++i)
        {
            addCharacter({ 150.f, 15300.f });
        }
    }

    void Game::run()
    {
        //to do, now for testing
        auto begin = std::chrono::steady_clock::now();
        auto end = std::chrono::steady_clock::now();
        float time = 0.f;
        float botsTime = 0.f;
        //60 frames per second
        float UPDATE_NANOSECONDS = 16666666;
        while(mWindow.isOpen())
        {
            event();
            end = std::chrono::steady_clock::now();
            time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
            botsTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
            begin = std::move(end);
            while (time > UPDATE_NANOSECONDS)
            {
                time -= UPDATE_NANOSECONDS;
                mWindView.update(UPDATE_NANOSECONDS / 1000000000.f);
                engine::GameEngine::update(UPDATE_NANOSECONDS / 1000000000.f);
                for (auto& character : mCharacters)
                {
                    character.update(UPDATE_NANOSECONDS / 1000000000.f);
                }
                if (mCharacters.size() > 0)
                {
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
            if (botsTime >= 8000000.f)
            {
                botsTime = 0.f;
                for (size_t i = 1; i < mCharacters.size(); ++i)
                {
                    auto& character = mCharacters[i];
                    int dir = std::rand() % 2 + 1;
                    character.setDirection((engine::CharacterDirection)dir);
                    int action = std::rand() % 1000 + 0;

                    if (i % 2 == 0)
                    {
                        if (action >= 200)
                        {
                            character.squat();
                        }
                        else if (action >= 100)
                        {
                            character.jump();
                        }
                        else if (action >= 25)
                        {
                            character.run(engine::CharacterDirection::Left);
                        }
                        else
                        {
                            character.run(engine::CharacterDirection::Right);
                        }
                    }
                    else
                    {
                        if (action >= 150)
                        {
                            character.squat();
                        }
                        else if (action >= 100)
                        {
                            character.jump();
                        }
                        else if (action >= 2)
                        {
                            character.run(engine::CharacterDirection::Left);
                        }
                        else
                        {
                            character.run(engine::CharacterDirection::Right);
                        }
                    }
                }
            }

        }
    }

    void Game::draw()
    {
        mWindow.clear();
        for (const auto& platform : mPhysicsEngine->getPlatforms())
        {
            sf::Color color = sf::Color::White;
            if (platform->getSurface() == physics::PlatformSurface::Slippery)
            {
                color = sf::Color::Cyan;
            }
            else if (platform->getSurface() == physics::PlatformSurface::Sticky)
            {
                color = sf::Color::Blue;
            }
            sf::Vertex line[] = 
            {
                sf::Vertex(sf::Vector2f(platform->getSegment().a.x, platform->getSegment().a.y), color),
                sf::Vertex(sf::Vector2f(platform->getSegment().b.x, platform->getSegment().b.y), color)
            };
            mWindow.draw(line, 2, sf::Lines);
        }
        
        for (int i = mCharacters.size() - 1; i >= 0; --i)
        {
            auto& character = mCharacters[i];
            sf::Color color = sf::Color::Red;
            if (i != 0)
            {
                if (i % 2 == 0)
                {
                    color = sf::Color::Yellow;
                }
                else
                {
                    color = sf::Color::Green;
                }
            }
            sf::VertexArray rect(sf::Quads, 4);
            rect[0] = sf::Vertex({ character.getRect().left, character.getRect().top }, color);
            rect[1] = sf::Vertex({ character.getRect().getRight(), character.getRect().top }, color);
            rect[2] = sf::Vertex({ character.getRect().getRight(), character.getRect().getBottom() }, color);
            rect[3] = sf::Vertex({ character.getRect().left, character.getRect().getBottom() }, color);
            if (character.isSquatting())
            {
                rect[0].position.y += character.getRect().height / 4.f;
                rect[1].position.y += character.getRect().height / 4.f;
            }
            else if (character.isDying())
            {
                rect[0].position.y += character.getRect().height * 0.75f;
                rect[1].position.y += character.getRect().height * 0.75f;
            }
            mWindow.draw(rect);
        }
        mWindow.draw(mWindView);
        mWindow.display();
    }

    void Game::event()
    {
        sf::Event event;
        bool jumped = false;
        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mWindow.close();
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

                if ((event.key.code == sf::Keyboard::Left &&
                    mCharacters[0].getDirection() == engine::CharacterDirection::Left) ||
                    (event.key.code == sf::Keyboard::Right &&
                        mCharacters[0].getDirection() == engine::CharacterDirection::Right))
                {
                    mCharacters[0].setDirection(engine::CharacterDirection::Up);
                    mCharacters[0].stop();
                }

                if (event.key.code >= sf::Keyboard::Num0 &&
                    event.key.code <= sf::Keyboard::Num9)
                {
                    removeCharacter(event.key.code - sf::Keyboard::Num0);
                }

                if (event.key.code == sf::Keyboard::Q)
                {
                    removeAllCharacters();
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

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                     mCharacters[0].squat();
                }

                if (event.key.code == sf::Keyboard::Left)
                {
                    mCharacters[0].run(engine::CharacterDirection::Left);
                }

                if (event.key.code == sf::Keyboard::Right)
                {
                    mCharacters[0].run(engine::CharacterDirection::Right);
                }
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
        }
        return;
    }
}