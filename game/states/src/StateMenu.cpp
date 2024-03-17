#include "../inc/StateMenu.hpp"

#include "../../inc/Context.hpp"

namespace jp::game::states
{
   StateMenu::StateMenu(StateStack* stack) : State(stack)
   {
      mItems.push_back(std::make_unique<menu::SelectableItem>(sf::Vector2f(160.f, 64.f), "Start",
         Context::get()->resources.getFont(res::FontID::Alkhemikal)));
      
      mItems.push_back(std::make_unique<menu::SelectableItem>(sf::Vector2f(160.f, 128.f), "Quit",
         Context::get()->resources.getFont(res::FontID::Alkhemikal)));
   }

   void StateMenu::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
   {
      for (const auto& item : mItems)
      {
         target.draw(*item);
      }
   }

   void StateMenu::event(const sf::Event& event)
   {
      if (event.type == sf::Event::KeyReleased)
      {
         switch (event.key.code)
         {
         case sf::Keyboard::Key::Up:
         case sf::Keyboard::Key::W:
            changeSelected(-1);
            break;
         case sf::Keyboard::Key::Down:
         case sf::Keyboard::Key::S:
            changeSelected(1);
            break;
         case sf::Keyboard::Key::Space:
         case sf::Keyboard::Key::Enter:
            performSelected();
            break;
         default:
            break;
         }
      }
   }

   void StateMenu::update(float dt) {}

   void StateMenu::changeSelected(int direction)
   {
      int newSelected = mSelected + direction;
      if (newSelected < 0)
      {
         newSelected = static_cast<int>(mItems.size()) - 1;
      }
      else if (newSelected >= mItems.size())
      {
         newSelected = 0;
      }
      mItems[mSelected]->deselect();
      mItems[newSelected]->select();
      mSelected = newSelected;
   }

   void StateMenu::performSelected()
   {
      if (mItems[mSelected]->getTextString() == "Quit")
      {
         Context::get()->window.close();
      }
   }
}