#include "../inc/StateGame.h"
#include <iostream>
namespace jp::state
{
   StateGame::StateGame(StateStack* stack, const Context& context) : State(stack, context)
   {
      player.setPosition({ 310.f, 400.f });
      player.setSize({ 30.f, 60.f });
      player.dyn.setVelocity({ 0.f, 0.f });
      player.dyn.setAcceleration({ 0.0f, 0.001f });
      StaObject obj;
      obj.setPosition({ 400.f, 350.f });
      obj.setSize({ 100.f, 30.f });
      objects.push_back(obj);
      obj.setPosition({ 320.f, 500.f });
      obj.setSize({ 800.f, 30.f });
      objects.push_back(obj);
      obj.setPosition({ 0.f, 200.f });
      obj.setSize({ 300.f, 300.f });
      objects.push_back(obj);
   }

   void StateGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(player.shape);
      for (const auto& obj : objects)
      {
         target.draw(obj.shape);
      }
   }

   bool StateGame::event(const sf::Event& event)
   {
      if (event.type == sf::Event::KeyReleased)
      {
         switch (event.key.code)
         {
         case sf::Keyboard::Escape:
            popState();
            pushState(StateID::Menu);
            break;
         case sf::Keyboard::Left:
         case sf::Keyboard::Right:
            if (!player.jumping)
            {
               player.dyn.setVelocity({ 0.f, player.dyn.getVelocity().y });
               player.jumpSpeed = 0.f;
            }
            break;
         case sf::Keyboard::Space:
            if (player.duringSpace)
            {
               std::cout << "duringSpace: " << player.duringSpace << std::endl;
               std::cout << "jumping: " << player.jumping << std::endl;
               player.setSize({ 30.f, 60.f });
               player.setPosition({ player.dyn.getPosition().x, player.dyn.getPosition().y - 30.f });
               player.duringSpace = false;
               player.jumping = true;
               player.dyn.setVelocity({ player.jumpSpeed, -0.8f });
            }
            break;
         }
      }
      if (event.type == sf::Event::KeyPressed)
      {
         switch (event.key.code)
         {
         case sf::Keyboard::Space:
            if (!player.duringSpace && !player.jumping)
            {
               player.setSize({ 30.f, 30.f });
               player.setPosition({ player.dyn.getPosition().x, player.dyn.getPosition().y + 30.f });
               player.duringSpace = true;
            }
            break;
         case sf::Keyboard::Left:
            if (!player.duringSpace && !player.jumping)
            {
               std::cout << "ustawiam lewo" << std::endl;
               player.dyn.setVelocity({ -0.12f, player.dyn.getVelocity().y });
            }
            else
            {
               std::cout << "jumpSpeed" << std::endl;
               player.jumpSpeed = -0.12f;
            }
            break;
         case sf::Keyboard::Right:
            if (!player.duringSpace && !player.jumping)
            {
               std::cout << "ustawiam prawo" << std::endl;
               player.dyn.setVelocity({ 0.12f, player.dyn.getVelocity().y });
            }
            else
            {
               std::cout << "jumpSpeed" << std::endl;
               player.jumpSpeed = 0.12f;
            }
            break;
         }
      }
      return true;
   }

   bool StateGame::update(const sf::Time& dt)
   {
      std::vector<jp::game::physics::StaticObject> obj;
      for (const auto& object : objects)
      {
         obj.push_back(object.sta);
      }
      if (!player.dyn.update(dt, obj))
      {
         if (player.jumping)
         {
            player.jumpSpeed = 0.f;
            player.dyn.setVelocity({ 0.f, 0.f });
         }
         player.jumping = false;
      }
      player.shape.setPosition(player.dyn.getPosition());
      return true;
   }
}