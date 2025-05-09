#include "../inc/StateLanguage.hpp"

#include "../../core/inc/String.hpp"

#include <algorithm>
#include <string>

namespace jp::game
{
   StateLanguage::StateLanguage(StateStack* stack, Context& context) : StateMenu(stack, context)
   {
      for (const auto& language : context.language.getAvailableLanguages())
      {
         mMenu.addItem(core::String::toUpper(language), context.resources.getFont(graphics::FontID::Pixeled));
      }
      
      mMenu.addItem(context.language.getString("back"), context.resources.getFont(graphics::FontID::Pixeled));
   }

   void StateLanguage::update(float dt)
   {
      if (mMenu.getItems().at(mMenu.getItems().size() - 1)->getTextString() != mContext.language.getString("back"))
      {
         mMenu.getItems().at(mMenu.getItems().size() - 1)->setTextString(mContext.language.getString("back"));
      }
   }

   void StateLanguage::performSelected()
   {
      if (mMenu.getSelectedTextString() == mContext.language.getString("back"))
      {
         popState();
      }
      else
      {
         mContext.setLanguage(core::String::toLower(mMenu.getSelectedTextString()));
      }
   }

   void StateLanguage::close()
   {
      popState();
   }
}