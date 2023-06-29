#include "../inc/StateGame.h"

namespace jp::state
{
   StateGame::StateGame(StateStack* stack, const Context& context) : State(stack, context)
   {
      shape.setRadius(50.f);
      shape.setFillColor(sf::Color::Green);
      shape.setPosition(50.f, 50.f);
   }

   void StateGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(shape);
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
         case sf::Keyboard::Up:
         case sf::Keyboard::Down:
         case sf::Keyboard::Left:
         case sf::Keyboard::Right:
            speed = { 0.f, 0.f };
            break;
         }
      }
      else if (event.type == sf::Event::KeyPressed)
      {
         float v = 1.f;
         switch (event.key.code)
         {
         case sf::Keyboard::Up:
            speed.y = -v;
            break;
         case sf::Keyboard::Down:
            speed.y = v;
            break;
         case sf::Keyboard::Left:
            speed.x = -v;
            break;
         case sf::Keyboard::Right:
            speed.x = v;
            break;
         }
      }
      return true;
   }

   bool StateGame::update(const sf::Time& dt)
   {
      shape.move({ speed.x * dt.asMilliseconds(), speed.y * dt.asMilliseconds() });
      return true;
   }
}