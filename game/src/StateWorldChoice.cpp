#include "../inc/StateWorldChoice.hpp"

namespace jp::game
{
   StateWorldChoice::StateWorldChoice(StateStack* stack, Context& context) : StateMenu(stack, context)
   { 
      mMenu.addItem(context.language.getString("babiac"), context.resources.getFont(graphic::FontID::Pixeled), sf::Color::White, sf::Color::Red);
      mMenu.addItem(context.language.getString("sudovia"), context.resources.getFont(graphic::FontID::Pixeled), sf::Color::White, sf::Color::Cyan);     
      mMenu.addItem(context.language.getString("tarnovia"), context.resources.getFont(graphic::FontID::Pixeled), sf::Color::White, sf::Color::Blue);
      mMenu.addItem(context.language.getString("back"), context.resources.getFont(graphic::FontID::Pixeled));
   }

   void StateWorldChoice::update(float dt)
   {
      if (mMenu.getItems().at(0)->getTextString() != mContext.language.getString("babiac"))
      {
         mMenu.setItemText(0, mContext.language.getString("babiac"));
         mMenu.setItemText(1, mContext.language.getString("sudovia"));
         mMenu.setItemText(2, mContext.language.getString("tarnovia"));
         mMenu.setItemText(3, mContext.language.getString("back"));
      }
   }

   void StateWorldChoice::performSelected()
   {
      popState();
      if (mMenu.getSelectedTextString() != mContext.language.getString("back"))
      {
         if (mMenu.getSelectedTextString() == mContext.language.getString("babiac"))
         {
            mContext.world = "babiac";
         }
         else if (mMenu.getSelectedTextString() == mContext.language.getString("sudovia"))
         {
            mContext.world = "sudovia";
         }
         else if (mMenu.getSelectedTextString() == mContext.language.getString("tarnovia"))
         {
            mContext.world = "tarnovia";
         }
         else
         {
            throw std::runtime_error("jp::game::StateWorldChoice::performSelected - Wrong option");
         }

         if (mContext.algorithm != algorithm::AlgorithmName::Dummy)
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