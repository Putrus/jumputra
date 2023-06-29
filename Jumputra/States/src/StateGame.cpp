#include "../inc/StateGame.h"

namespace jp::state
{
   StateGame::StateGame(StateStack* stack, const Context& context) : State(stack, context)
   {
      player.dyn.setRect(sf::FloatRect(0, 0, 30, 60));
      player.shape.setSize(sf::Vector2f(30, 60));
      player.shape.setPosition(0.f, 0.f);
   }

   void StateGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(player.shape);
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
            /*speed = { 0.f, 0.f };*/
            //view.zoom(0.1);
            break;
         }
      }
      else if (event.type == sf::Event::KeyPressed)
      {
         float v = 1.f;
         switch (event.key.code)
         {
         
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
      player.dyn.update(dt, obj);
      player.shape.setPosition(player.dyn.getPosition());
      return true;
   }
}