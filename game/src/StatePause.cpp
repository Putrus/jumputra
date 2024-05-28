#include "../inc/StatePause.hpp"

namespace jp::game
{
   StatePause::StatePause(StateStack* stack, Context& context) : StateMenu(stack, context)
   {
      mMenu.addItem(mContext.language.getString("pause"),
         mContext.resources.getFont(graphic::FontID::Pixeled));
      mMenu.addItem(mContext.language.getString("statistics"),
         mContext.resources.getFont(graphic::FontID::Pixeled));
      mMenu.addItem(mContext.language.getString("jumps") + ": " + std::to_string(mContext.statistics.jumps),
         mContext.resources.getFont(graphic::FontID::Pixeled));
      mMenu.addItem(mContext.language.getString("falls") + ": " + std::to_string(mContext.statistics.falls),
         mContext.resources.getFont(graphic::FontID::Pixeled));
      mMenu.addItem(mContext.language.getString("time") + ": " + std::to_string((int)mContext.statistics.time) + " s",
         mContext.resources.getFont(graphic::FontID::Pixeled));
      mMenu.addItem(mContext.language.getString("continue"),
         mContext.resources.getFont(graphic::FontID::Pixeled));
      mMenu.addItem(mContext.language.getString("back"),
         mContext.resources.getFont(graphic::FontID::Pixeled));
   }

   void StatePause::update(float dt)
   {
      if (mMenu.getItems().at(mMenu.getItems().size() - 1)->getTextString() != mContext.language.getString("back"))
      {
         mMenu.setItemText(0, mContext.language.getString("pause"));
         mMenu.setItemText(1, mContext.language.getString("statistics"));
         mMenu.setItemText(2, mContext.language.getString("jumps") + ": " + std::to_string(mContext.statistics.jumps));
         mMenu.setItemText(3, mContext.language.getString("falls") + ": " + std::to_string(mContext.statistics.falls));
         mMenu.setItemText(4, mContext.language.getString("time") + ": " + std::to_string((int)mContext.statistics.time) + " s");
         mMenu.setItemText(5, mContext.language.getString("continue"));
         mMenu.setItemText(6, mContext.language.getString("back"));
      }
   }

   void StatePause::performSelected()
   {
      if (mMenu.getSelectedTextString() == mContext.language.getString("continue"))
      {
         close();
      }

      if (mMenu.getSelectedTextString() == mContext.language.getString("back"))
      {
         popState();
      }
   }

   void StatePause::close()
   {
      popState();
      mContext.newGame = false;
      pushState(StateID::Game);
   }
}