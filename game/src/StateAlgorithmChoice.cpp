#include "../inc/StateAlgorithmChoice.hpp"

namespace jp::game
{
   StateAlgorithmChoice::StateAlgorithmChoice(StateStack* stack, Context& context) : StateMenu(stack, context)
   {
      mMenu.addItem(context.language.getString("greedy"), context.resources.getFont(graphic::FontID::Pixeled), sf::Color::White, sf::Color::Magenta);
      mMenu.addItem(context.language.getString("back"), context.resources.getFont(graphic::FontID::Pixeled));
   }

   void StateAlgorithmChoice::update(float dt)
   {
      if (mMenu.getItems().at(0)->getTextString() != mContext.language.getString("greedy"))
      {
         mMenu.setItemText(0, mContext.language.getString("greedy"));
         mMenu.setItemText(1, mContext.language.getString("back"));
      }
   }

   void StateAlgorithmChoice::performSelected()
   {
      if (mMenu.getSelectedTextString() == mContext.language.getString("back"))
      {
         popState();
      }
   }

   void StateAlgorithmChoice::close()
   {
      popState();
   }
}