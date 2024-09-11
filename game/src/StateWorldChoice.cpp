#include "../inc/StateWorldChoice.hpp"

namespace jp::game
{
   StateWorldChoice::StateWorldChoice(StateStack* stack, Context& context) : StateMenu(stack, context)
   {
      context.loadWorlds();
      for (const auto& world : context.worlds)
      {
         mMenu.addItem(context.language.getString(world), context.resources.getFont(graphic::FontID::Pixeled));
      }
      
      mMenu.addItem(context.language.getString("back"), context.resources.getFont(graphic::FontID::Pixeled));
   }

   void StateWorldChoice::update(float dt)
   {
      if (mMenu.getItems().back()->getTextString() != mContext.language.getString("back"))
      {
         for (size_t i = 0; i < mContext.worlds.size(); ++i)
         {
            mMenu.setItemText(i, mContext.worlds[i]);
         }
         mMenu.setItemText(mContext.worlds.size(), mContext.language.getString("back"));
      }
   }

   void StateWorldChoice::performSelected()
   {
      popState();
      if (mMenu.getSelectedTextString() != mContext.language.getString("back"))
      {
         for (const auto& world : mContext.worlds)
         {
            if (mMenu.getSelectedTextString() == mContext.language.getString(world))
            {
               mContext.world = world;
               break;
            }
         }
         
         if (mContext.algorithm != algorithm::AlgorithmName::Human)
         {
            popState();
         }
         pushState(StateID::Game);
      }
   }

   void StateWorldChoice::close()
   {
      popState();
   }
}