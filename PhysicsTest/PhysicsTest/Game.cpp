#include "Game.h"

#include <iostream>

Game::Game() :
   mWindow(sf::VideoMode(640, 360), "Game"), mTimePerFrame(sf::seconds(1.f / 120.f))
{
   mPlatforms.push_back(
      jp::physics::Platform({ { 1.f, 100.f }, { 50.f, 100.f },
         { 50.f, 200.f }, { 150.f, 300.f }, { 150.f, 350.f }, { 1.f, 350.f } }));
   mPlatforms.push_back(
      jp::physics::Platform({ { 100.f, 50.f }, { 132.f, 50.f }, { 132.f, 132.f }, { 100.f, 132.f } }));
   mPlatforms.push_back(
      jp::physics::Platform({ { 200.f, 100.f }, { 432.f, 100.f }, { 432.f, 132.f }, { 200.f, 132.f } }));

   mPlatforms.push_back(jp::physics::Platform({ { 500.f, 200.f }, { 640.f, 60.f } }));

   mPlatforms.push_back(jp::physics::Platform({ { 400.f, 240.f }, { 500.f, 240.f } }/*, jp::physics::SurfaceType::Slippery*/));
   
   mPlatforms.push_back(
      jp::physics::Platform({ { 150.f, 350.f }, { 400.f, 350.f } }/*, jp::physics::SurfaceType::Slippery*/));

   mPlatforms.push_back(jp::physics::Platform({ { 400.f, 240.f }, { 400.f, 350.f } }/*, jp::physics::SurfaceType::Slippery*/));
   //std::cout << "line size: " << sizeof(mLines[0]) << std::endl;
   mObjects.push_back(Object(jp::math::Rect<float>(5.f, 5.f, 24.f, 24.f), jp::math::Vector2<float>(0.f, 0.f), jp::math::Vector2<float>(0.f, 0.f)));
   jp::math::Vector2<float> v(5.f, 5.f);
   jp::math::Vector2<float> v1 = v + v;
}

void Game::run()
{
   sf::Clock clock;
   sf::Time timeSinceLastUpdate = sf::Time::Zero;
   while (mWindow.isOpen())
   {
      processEvents();
      timeSinceLastUpdate += clock.restart();
      update(timeSinceLastUpdate);
      render();
   }
}

void Game::processEvents()
{
   sf::Event event;
   while (mWindow.pollEvent(event))
   {
      if (event.type == sf::Event::Closed)
      {
         mWindow.close();
      }
      if (event.type == sf::Event::KeyPressed)
      {
         if (event.key.code == sf::Keyboard::Left)
         {
            mObjects[0].mVelocity.x = -200.f;
         }
         if (event.key.code == sf::Keyboard::Right)
         {
            mObjects[0].mVelocity.x = 200.f;
         }
      }

      if (event.type == sf::Event::KeyReleased)
      {
         if (event.key.code == sf::Keyboard::Space)
         {
            //std::cout << intersects(mPlatforms[0].mPoints[2], mPlatforms[0].mPoints[3], mObjects[0].getRect()) << std::endl;
            mObjects[0].mVelocity.y = -400.f;
         }
         if (event.key.code == sf::Keyboard::L)
         {
            for (size_t i = 0; i < mObjects.size(); ++i)
            {
               std::cout << "---------- Object " << i << " ------------" << std::endl;
               mObjects[i].log();
            }
         }

         /*if (event.key.code == sf::Keyboard::Left)
         {
            mObjects[0].mVelocity.x = 0.f;
         }
         if (event.key.code == sf::Keyboard::Right)
         {
            mObjects[0].mVelocity.x = 0.f;
         }*/
      }

      

      if (event.type == sf::Event::MouseButtonReleased)
      {
         if (event.key.code == sf::Mouse::Left)
         {
            sf::Vector2i mp = sf::Mouse::getPosition(mWindow);
            mObjects.push_back(Object(jp::math::Rect<float>(mp.x, mp.y, 24.f, 24.f), jp::math::Vector2<float>(0.f, 0.f), jp::math::Vector2<float>(0.f, 0.f)));
         }
         if (event.key.code == sf::Mouse::Right)
         {
            sf::Vector2i mp = sf::Mouse::getPosition(mWindow);
            mObjects.push_back(Object(jp::math::Rect<float>(mp.x, mp.y, 24.f, 24.f), jp::math::Vector2<float>(0.f, 0.f), jp::math::Vector2<float>(0.f, 0.f)));
         }
      }
   }
}

void Game::render()
{
   mWindow.clear();
   for (const auto& platform : mPlatforms)
   {
      std::vector<sf::Vertex> vertices;
      sf::Color color = platform.mType == jp::physics::SurfaceType::Normal ? sf::Color::White : sf::Color::Cyan;
      for (const auto& point : platform.mPoints)
      {
         sf::Vertex vertex;
         vertex.position = { point.x, point.y };
         vertex.color = color;
         vertices.push_back(vertex);
      }
      sf::Vertex vertex;
      vertex.position = { platform.mPoints[0].x, platform.mPoints[0].y };
      vertex.color = color;
      vertices.push_back(vertex);
      mWindow.draw(vertices.data(), vertices.size(), sf::LinesStrip);
   }

   for (const auto& object : mObjects)
   {
      mWindow.draw(object);
   }
   mWindow.display();
}

void Game::update(sf::Time& dt)
{
   while (dt > mTimePerFrame)
   {
      for (auto& object : mObjects)
      {
         object.update(dt.asSeconds(), mPlatforms);
      }
      dt -= mTimePerFrame;
   }
}