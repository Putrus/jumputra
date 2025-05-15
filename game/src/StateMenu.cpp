#include "../inc/StateMenu.hpp"

namespace jp::game
{
   StateMenu::StateMenu(StateStack* stack, Context& context) : State(stack, context) {}

   void StateMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(mMenu);
   }

   void StateMenu::event(const std::optional<sf::Event>& event)
   {
      if (const auto* keyPressed = event->getIf<sf::Event::KeyReleased>())
      {
         switch (keyPressed->scancode)
         {
         case sf::Keyboard::Scancode::Up:
         case sf::Keyboard::Scancode::W:
            mMenu.setSelected(mMenu.getSelected() - 1);
            break;
         case sf::Keyboard::Scancode::Down:
         case sf::Keyboard::Scancode::S:
            mMenu.setSelected(mMenu.getSelected() + 1);
            break;
         case sf::Keyboard::Scancode::Space:
         case sf::Keyboard::Scancode::Enter:
            performSelected();
            break;
         case sf::Keyboard::Scancode::Escape:
            close();
            break;
         default:
            break;
         }
      }
   }
}