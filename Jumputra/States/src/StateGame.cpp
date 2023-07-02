#include "../inc/StateGame.h"

#include <json/json.h>

#include <iostream>

namespace jp::state
{
   StateGame::StateGame(StateStack* stack, const Context& context) : State(stack, context)
   {
      objects.push_back(game::physics::StaticObject({ 0.f, -100.f }, { 30.f, 1000.f }));
      objects.push_back(game::physics::StaticObject({ 930.f, -100.f }, { 30.f, 1000.f }));
      objects.push_back(game::physics::StaticObject({ 100.f, -200.f }, { 100.f, 50.f }));
      objects.push_back(game::physics::StaticObject({ 300.f, 100.f }, { 100.f, 50.f }));
      context.window.setView(view);
   }

   void StateGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      for (const auto& object : objects)
      {
         target.draw(object, states);
      }
   }

   bool StateGame::event(const sf::Event& event)
   {
      if (event.type == sf::Event::KeyReleased)
      {
         float height = static_cast<float>(mContext.window.getSize().y);
         switch (event.key.code)
         {
         case sf::Keyboard::Escape:
            popState();
            pushState(StateID::Menu);
            break;
         case sf::Keyboard::Up:
            view.move(sf::Vector2f(0.f, -height));
            mContext.window.setView(view);
            break;
         case sf::Keyboard::Down:
            std::cout << "sizeY = " << mContext.window.getSize().y << std::endl;
            view.move(sf::Vector2f(0.f, height));
            mContext.window.setView(view);
            break;
         }
      }
      if (event.type == sf::Event::MouseButtonReleased)
      {
         if (event.key.code == sf::Mouse::Left)
         {

         }
      }

      if (event.type == sf::Event::KeyPressed)
      {
         switch (event.key.code)
         {
            //to do
         }
      }
      return true;
   }

   bool StateGame::update(const sf::Time& dt)
   {
      return true;
   }
}