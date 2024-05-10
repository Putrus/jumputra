#include "../inc/StateMainMenu.hpp"

namespace jp::game
{
   StateMainMenu::StateMainMenu(StateStack* stack, Context& context) : StateMenu(stack, context)
   { 
      mMenu.addItem(context.language.getString("play"), context.resources.getFont(graphic::FontID::Pixeled));

      mMenu.addItem(context.language.getString("language"), context.resources.getFont(graphic::FontID::Pixeled));

      mMenu.addItem(context.language.getString("quit"), context.resources.getFont(graphic::FontID::Pixeled));
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