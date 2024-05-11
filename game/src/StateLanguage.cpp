#include "../inc/StateLanguage.hpp"

#include <algorithm>
#include <string>

namespace jp::game
{
   StateLanguage::StateLanguage(StateStack* stack, Context& context) : StateMenu(stack, context)
   {
      for (const auto& language : context.language.getAvailableLanguages())
      {
         std::string strLanguage = language;
         std::transform(strLanguage.begin(), strLanguage.end(), strLanguage.begin(), toupper);
         mMenu.addItem(strLanguage, context.resources.getFont(graphic::FontID::Pixeled));
      }
      
      mMenu.addItem(context.language.getString("back"), context.resources.getFont(graphic::FontID::Pixeled));
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
         std::string strLanguage = mMenu.getSelectedTextString();
         std::transform(strLanguage.begin(), strLanguage.end(), strLanguage.begin(), tolower);
         mContext.setLanguage(strLanguage);
      }
   }

   void StateLanguage::close()
   {
      popState();
   }
}