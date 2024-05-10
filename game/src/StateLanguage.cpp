#include "../inc/StateLanguage.hpp"

namespace jp::game
{
   StateLanguage::StateLanguage(StateStack* stack, Context& context) : StateMenu(stack, context)
   { 
      for (const auto& language : context.language.getAvailableLanguages())
      {
         mMenu.addItem(language, context.resources.getFont(graphic::FontID::Pixeled));
      }
      
      mMenu.addItem(context.language.getString("back"), context.resources.getFont(graphic::FontID::Pixeled));
   }

   void StateLanguage::performSelected()
   {
      if (mMenu.getSelectedTextString() == mContext.language.getString("back"))
      {
         popState();
      }
      else
      {
         mContext.language.setLanguage(mMenu.getSelectedTextString());
         mContext.language.loadFromJsonFile("data/jsons/languages.json");
      }
   }

   void StateLanguage::close()
   {
      popState();
   }
}