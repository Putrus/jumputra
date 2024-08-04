#include "../inc/StateAgentChoice.hpp"

namespace jp::game
{
   StateAgentChoice::StateAgentChoice(StateStack* stack, Context& context) : StateMenu(stack, context)
   {
      mMenu.addItem(context.language.getString("human"), context.resources.getFont(graphic::FontID::Pixeled), sf::Color::White, sf::Color::Yellow);
      mMenu.addItem(context.language.getString("greedy"), context.resources.getFont(graphic::FontID::Pixeled), sf::Color::White, sf::Color::Magenta);
      mMenu.addItem(context.language.getString("back"), context.resources.getFont(graphic::FontID::Pixeled));
   }

   void StateAgentChoice::update(float dt)
   {
      if (mMenu.getItems().at(0)->getTextString() != mContext.language.getString("human"))
      {
         mMenu.setItemText(0, mContext.language.getString("human"));
         mMenu.setItemText(1, mContext.language.getString("greedy"));
         mMenu.setItemText(2, mContext.language.getString("back"));
      }
   }

   void StateAgentChoice::performSelected()
   {
      if (mMenu.getSelectedTextString() == mContext.language.getString("back"))
      {
         popState();
      }
      else
      {
         if (mMenu.getSelectedTextString() == mContext.language.getString("human"))
         {
            mContext.agent = agents::AgentName::Human;
         }
         else if (mMenu.getSelectedTextString() == mContext.language.getString("greedy"))
         {
            mContext.agent = agents::AgentName::Greedy;
         }
         else
         {
            throw std::runtime_error("jp::game::StateAgentChoice::performSelected - Wrong option");
         }
         pushState(StateID::WorldChoice);
      }
   }

   void StateAgentChoice::close()
   {
      popState();
   }
}