#include "../inc/StateMainMenu.hpp"

#include <algorithm>

namespace jp::game
{
   StateMainMenu::StateMainMenu(StateStack* stack, Context& context) : StateMenu(stack, context)
   { 
      mMenu.addItem(context.language.getString("play"), context.resources.getFont(graphic::FontID::Pixeled));
      mMenu.addItem(context.language.getString("language"), context.resources.getFont(graphic::FontID::Pixeled));
      mMenu.addItem(context.language.getString("quit"), context.resources.getFont(graphic::FontID::Pixeled));
   }

   void StateMainMenu::update(float dt)
   {
      if (mMenu.getItems().at(0)->getTextString() != mContext.language.getString("play"))
      {
         mMenu.setItemText(0, mContext.language.getString("play"));
         mMenu.setItemText(1, mContext.language.getString("language"));
         mMenu.setItemText(2, mContext.language.getString("quit"));
      }
   }

   void StateMainMenu::performSelected()
   {
      if (mMenu.getSelectedTextString() == mContext.language.getString("play"))
      {
         pushState(StateID::WorldChoice);
      }

      if (mMenu.getSelectedTextString() == mContext.language.getString("language"))
      {
         pushState(StateID::Language);
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