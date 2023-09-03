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
      jp::physics::Platform({ { 360.f, 150.f }, { 480.f, 150.f }, { 480.f, 166.f }, { 360.f, 166.f } }));

   mPlatforms.push_back(
      jp::physics::Platform({ { 300.f, 150.f }, { 300.f, 250.f } }));

   /*mPlatforms.push_back(
      jp::physics::Platform({ { 200.f, 100.f }, { 432.f, 100.f }, { 432.f, 132.f }, { 200.f, 132.f } }));*/

   mPlatforms.push_back(jp::physics::Platform({ { 640.f, 60.f }, { 500.f, 200.f } }));

   mPlatforms.push_back(jp::physics::Platform({ { 640.f, -200.f }, { 500.f, -60.f } }));

   mPlatforms.push_back(jp::physics::Platform({ { 400.f, 240.f }, { 500.f, 240.f } }/*, jp::physics::PlatformType::Slippery*/));
   
   mPlatforms.push_back(
      jp::physics::Platform({ { 150.f, 350.f }, { 400.f, 350.f } }, jp::physics::PlatformType::Slippery));

   mPlatforms.push_back(jp::physics::Platform({ { 400.f, 240.f }, { 400.f, 350.f } }/*, jp::physics::PlatformType::Slippery*/));

   for (auto& platform : mPlatforms)
   {
      auto segments = platform.getSegments();
      mSegments.insert(mSegments.end(), segments.begin(), segments.end());
   }

   std::sort(mSegments.begin(), mSegments.end(), [](const auto& lhs, const auto& rhs)
      {
         if (lhs.segment.isDiagonal() && !rhs.segment.isDiagonal())
         {
            return false;
         }
         if (!lhs.segment.isDiagonal() && rhs.segment.isDiagonal())
         {
            return true;
         }

         if ((lhs.segment.isHorizontal() && rhs.segment.isHorizontal()) || (lhs.segment.isVertical() && rhs.segment.isVertical()))
         {
            return false;
         }

         if (lhs.segment.isHorizontal() && rhs.segment.isVertical())
         {
            return true;
         }

         return false;
      });

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

      if (event.type == sf::Event::KeyReleased)
      {
         if (event.key.code == sf::Keyboard::Space)
         {
            //std::cout << intersects(mPlatforms[0].getPoints()[2], mPlatforms[0].getPoints()[3], mObjects[0].getRect()) << std::endl;
            mObjects[0].mAttributes.velocity.y = -570.f;
         }

         if (event.key.code == sf::Keyboard::S)
         {
            //std::cout << intersects(mPlatforms[0].getPoints()[2], mPlatforms[0].getPoints()[3], mObjects[0].getRect()) << std::endl;
            mObjects[0].mAttributes.velocity.y = 0.f;
            mObjects[0].GRAVITY = 0.f;
         }

         if (event.key.code == sf::Keyboard::R)
         {
            mObjects[0].GRAVITY = 1000.f;
         }

         if (event.key.code == sf::Keyboard::L)
         {
            for (size_t i = 0; i < mObjects.size(); ++i)
            {
               std::cout << "---------- Object " << i << " ------------" << std::endl;
               mObjects[i].log();
               mObjects[i].logging = mObjects[i].logging ? false : true;
            }
         }

         if (event.key.code == sf::Keyboard::Left)
         {
            mObjects[0].mAttributes.velocity.x = 0.f;
         }
         if (event.key.code == sf::Keyboard::Right)
         {
            mObjects[0].mAttributes.velocity.x = 0.f;
         }
      }

      if (event.type == sf::Event::KeyPressed)
      {
         if (event.key.code == sf::Keyboard::Left)
         {
            mObjects[0].mAttributes.velocity.x = -200.f;
         }
         if (event.key.code == sf::Keyboard::Right)
         {
            mObjects[0].mAttributes.velocity.x = 200.f;
         }
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
      sf::Color color = platform.getType() == jp::physics::PlatformType::Ordinary ? sf::Color::White : sf::Color::Cyan;
      for (const auto& point : platform.getPoints())
      {
         sf::Vertex vertex;
         vertex.position = { point.x, point.y };
         vertex.color = color;
         vertices.push_back(vertex);
      }
      sf::Vertex vertex;
      vertex.position = { platform.getPoints()[0].x, platform.getPoints()[0].y };
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
         object.update(dt.asSeconds(), mSegments);
      }
      dt -= mTimePerFrame;
   }
}