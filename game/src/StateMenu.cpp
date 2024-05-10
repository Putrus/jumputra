#include "../inc/StateMenu.hpp"

namespace jp::game
{
   StateMenu::StateMenu(StateStack* stack, Context& context) : State(stack, context) {}

   void StateMenu::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
   {
      target.draw(mMenu);
   }

   void StateMenu::event(const sf::Event& event)
   {
      if (event.type == sf::Event::KeyReleased)
      {
         switch (event.key.code)
         {
         case sf::Keyboard::Key::Up:
         case sf::Keyboard::Key::W:
            mMenu.setSelected(mMenu.getSelected() - 1);
            break;
         case sf::Keyboard::Key::Down:
         case sf::Keyboard::Key::S:
            mMenu.setSelected(mMenu.getSelected() + 1);
            break;
         case sf::Keyboard::Key::Space:
         case sf::Keyboard::Key::Enter:
            performSelected();
            break;
         case sf::Keyboard::Key::Escape:
            close();
            break;
         default:
            break;
         }
      }
   }

   void StateMenu::update(float dt) {}
}