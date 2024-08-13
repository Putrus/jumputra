#include "../inc/StateAlgorithmChoice.hpp"

namespace jp::game
{
   StateAlgorithmChoice::StateAlgorithmChoice(StateStack* stack, Context& context) : StateMenu(stack, context)
   {
      mMenu.addItem(context.language.getString("antColony"), context.resources.getFont(graphic::FontID::Pixeled), sf::Color::White, sf::Color::Green);
      mMenu.addItem(context.language.getString("genetic"), context.resources.getFont(graphic::FontID::Pixeled), sf::Color::White, sf::Color::Cyan);
      mMenu.addItem(context.language.getString("greedy"), context.resources.getFont(graphic::FontID::Pixeled), sf::Color::White, sf::Color::Magenta);
      mMenu.addItem(context.language.getString("back"), context.resources.getFont(graphic::FontID::Pixeled));
   }

   void StateAlgorithmChoice::update(float dt)
   {
      if (mMenu.getItems().at(0)->getTextString() != mContext.language.getString("antColony"))
      {
         mMenu.setItemText(0, mContext.language.getString("antColony"));
         mMenu.setItemText(1, mContext.language.getString("genetic"));
         mMenu.setItemText(2, mContext.language.getString("greedy"));
         mMenu.setItemText(3, mContext.language.getString("back"));
      }
   }

   void StateAlgorithmChoice::performSelected()
   {
      if (mMenu.getSelectedTextString() == mContext.language.getString("back"))
      {
         popState();
      }
      else
      {
         if (mMenu.getSelectedTextString() == mContext.language.getString("antColony"))
         {
            mContext.controller = Controller::AntColony;
         }
         else if (mMenu.getSelectedTextString() == mContext.language.getString("genetic"))
         {
            mContext.controller = Controller::Genetic;
         }
         else if (mMenu.getSelectedTextString() == mContext.language.getString("greedy"))
         {
            mContext.controller = Controller::Greedy;
         }
         else
         {
            throw std::runtime_error("jp::game::StateAlgorithmChoice::performSelected - Wrong option");
         }
         pushState(StateID::WorldChoice);
      }
   }

   void StateAlgorithmChoice::close()
   {
      popState();
   }
}