#include "../inc/StateMenu.hpp"

namespace jp::game
{
   StateMenu::StateMenu(StateStack* stack) : State(stack)
   {
      // mItems.push_back(std::make_unique<menu::SelectableItem>(sf::Vector2f(160.f, 64.f), "Play",
      //    Context::get()->resources.getFont(res::FontID::Alkhemikal)));
      
      // mItems.push_back(std::make_unique<menu::SelectableItem>(sf::Vector2f(160.f, 128.f), "Quit",
      //    Context::get()->resources.getFont(res::FontID::Alkhemikal)));
      
      //changeSelected(0);
   }

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
            //Context::get()->window.close();
            break;
         default:
            break;
         }
      }
   }

   void StateMenu::update(float dt) {}

   void StateMenu::performSelected()
   {
      if (mMenu.getSelectedTextString() == "Play")
      {
         pushState(StateID::Game);
      }

      if (mMenu.getSelectedTextString() == "Quit")
      {
         //Context::get()->window.close();
      }
   }
}