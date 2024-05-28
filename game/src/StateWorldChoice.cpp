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
      if (mMenu.getSelectedTextString() == mContext.language.getString("babiac"))
      {
         mContext.world = "babiac";
         popState();
         pushState(StateID::Game);
      }

      if (mMenu.getSelectedTextString() == mContext.language.getString("sudovia"))
      {
         mContext.world = "sudovia";
         popState();
         pushState(StateID::Game);
      }

      if (mMenu.getSelectedTextString() == mContext.language.getString("tarnovia"))
      {
         mContext.world = "tarnovia";
         popState();
         pushState(StateID::Game);
      }

      if (mMenu.getSelectedTextString() == mContext.language.getString("back"))
      {
         popState();
      }
   }

   void StateWorldChoice::close()
   {
      popState();
   }
}