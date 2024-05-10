#include "../inc/StateMainMenu.hpp"

namespace jp::game
{
   StateMainMenu::StateMainMenu(StateStack* stack, Context& context) : StateMenu(stack, context)
   { 
      mMenu.addItem(std::make_unique<MenuItem>(sf::Vector2f(160.f, 64.f), context.language.getString("play"),
         context.resources.getFont(graphic::FontID::Pixeled)));

      mMenu.addItem(std::make_unique<MenuItem>(sf::Vector2f(160.f, 128.f), context.language.getString("quit"),
         context.resources.getFont(graphic::FontID::Pixeled)));
   }

   void StateMainMenu::update(float dt) {}

   void StateMainMenu::performSelected()
   {
      if (mMenu.getSelectedTextString() == mContext.language.getString("play"))
      {
         pushState(StateID::WorldChoice);
      }

      if (mMenu.getSelectedTextString() == mContext.language.getString("quit"))
      {
         mContext.window.close();
      }
   }

   void StateMainMenu::close()
   {
      mContext.window.close();
   }
}