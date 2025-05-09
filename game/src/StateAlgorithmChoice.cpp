#include "../inc/StateAlgorithmChoice.hpp"

namespace jp::game
{
   StateAlgorithmChoice::StateAlgorithmChoice(StateStack* stack, Context& context) : StateMenu(stack, context)
   {
      mMenu.addItem(context.language.getString("antColony"), context.resources.getFont(graphics::FontID::Pixeled), sf::Color::White, sf::Color::Green);
      mMenu.addItem(context.language.getString("decisionTree"), context.resources.getFont(graphics::FontID::Pixeled), sf::Color::White, sf::Color::Red);
      mMenu.addItem(context.language.getString("genetic"), context.resources.getFont(graphics::FontID::Pixeled), sf::Color::White, sf::Color::Cyan);
      mMenu.addItem(context.language.getString("greedy"), context.resources.getFont(graphics::FontID::Pixeled), sf::Color::White, sf::Color::Magenta);
      mMenu.addItem(context.language.getString("qLearning"), context.resources.getFont(graphics::FontID::Pixeled), sf::Color::White, sf::Color::Blue);
      mMenu.addItem(context.language.getString("back"), context.resources.getFont(graphics::FontID::Pixeled));
   }

   void StateAlgorithmChoice::update(float dt)
   {
      if (mMenu.getItems().at(0)->getTextString() != mContext.language.getString("antColony"))
      {
         mMenu.setItemText(0, mContext.language.getString("antColony"));
         mMenu.setItemText(1, mContext.language.getString("decisionTree"));
         mMenu.setItemText(2, mContext.language.getString("genetic"));
         mMenu.setItemText(3, mContext.language.getString("greedy"));
         mMenu.setItemText(4, mContext.language.getString("qLearning"));
         mMenu.setItemText(5, mContext.language.getString("back"));
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
            mContext.algorithm = algorithm::AlgorithmName::AntColony;
         }
         else if (mMenu.getSelectedTextString() == mContext.language.getString("decisionTree"))
         {
            mContext.algorithm = algorithm::AlgorithmName::DecisionTree;
         }
         else if (mMenu.getSelectedTextString() == mContext.language.getString("genetic"))
         {
            mContext.algorithm = algorithm::AlgorithmName::Genetic;
         }
         else if (mMenu.getSelectedTextString() == mContext.language.getString("greedy"))
         {
            mContext.algorithm = algorithm::AlgorithmName::Greedy;
         }
         else if (mMenu.getSelectedTextString() == mContext.language.getString("qLearning"))
         {
            mContext.algorithm = algorithm::AlgorithmName::QLearning;
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