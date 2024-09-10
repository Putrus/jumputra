#include "../inc/StateGame.hpp"

#include "../../algorithm/inc/AntColony.hpp"
#include "../../algorithm/inc/DecisionTree.hpp"
#include "../../algorithm/inc/Dummy.hpp"
#include "../../algorithm/inc/Genetic.hpp"
#include "../../algorithm/inc/Greedy.hpp"
#include "../../algorithm/inc/QLearning.hpp"

#include "../../core/inc/String.hpp"

#include <chrono>
#include <format>

namespace jp::game
{
   StateGame::StateGame(StateStack* stack, Context& context)
      : mGame(std::make_shared<Game>(context)), State(stack, context)
   {
      std::stringstream ss;
      ss << mContext.controller;
      std::shared_ptr<core::Logger> logger = std::make_shared<core::Logger>(std::string(LOGS_DIR) + mContext.world + "_" +
         core::String::toLower(ss.str()) + "_" + core::String::currentDate() + ".txt", true);
      switch (context.controller)
      {
      case Controller::AntColony:
         mAlgorithm = std::make_shared<algorithm::AntColony>(mGame, logger, mContext.properties.algorithm);
         break;
      case Controller::DecisionTree:
         mAlgorithm = std::make_shared<algorithm::DecisionTree>(mGame, logger, mContext.properties.algorithm);
         break;
      case Controller::Genetic:
         mAlgorithm = std::make_shared<algorithm::Genetic>(mGame, logger, mContext.properties.algorithm);
         break;
      case Controller::Greedy:
         mAlgorithm = std::make_shared<algorithm::Greedy>(mGame, logger, mContext.properties.algorithm);
         break;
      case Controller::Human:
         mAlgorithm = std::make_shared<algorithm::Dummy>(mGame, logger, mContext.properties.algorithm);
         break;
      case Controller::QLearning:
         mAlgorithm = std::make_shared<algorithm::QLearning>(mGame, logger, mContext.properties.algorithm);
         break;
      default:
         throw std::invalid_argument("jp::game::StateGame::StateGame - Failed to create agent, wrong agent name");
      }
   }

   void StateGame::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
   {
      target.draw(*mGame);
   }

   void StateGame::event(const sf::Event& event)
   {
      if (event.type == sf::Event::Closed)
      {
         if (mContext.controller == Controller::Human)
         {
            mGame->save();
         }
      }

      if (event.type == sf::Event::KeyReleased)
      {
         switch (event.key.code)
         {
         case sf::Keyboard::Key::Escape:
            if (mContext.controller == Controller::Human)
            {
               mGame->save();
            }
            mGame->resetView();
            mContext.statistics = mGame->getStatistics();
            pushState(StateID::Pause);
            break;
         case sf::Keyboard::Key::M:
            mAlgorithm->saveMoves("test.json");
            break;
         default:
            break;
         }
      }

      mGame->event(event);
   }

   void StateGame::update(float dt)
   {
      mGame->update(dt);
      if (mGame->getWinner())
      {
         std::stringstream filenameSS;
         filenameSS << mContext.world << '_' << mContext.controller;
         std::string filename = filenameSS.str();
         filename = core::String::toLower(filename);
         std::filesystem::remove(std::string(SAVES_DIR) + filename + ".json");
         mGame->saveStatistics(std::string(STATISTICS_DIR) + filename + "_" + core::String::currentDate() + ".json");
         mContext.statistics = mGame->getStatistics();
         popState();
         pushState(StateID::Win);
      }
      mAlgorithm->update(dt);
   }
}