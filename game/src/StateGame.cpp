#include "../inc/StateGame.hpp"

#include "../../algorithm/inc/AntColony.hpp"
#include "../../algorithm/inc/DecisionTree.hpp"
#include "../../algorithm/inc/Genetic.hpp"
#include "../../algorithm/inc/Greedy.hpp"
#include "../../algorithm/inc/Human.hpp"
#include "../../algorithm/inc/QLearning.hpp"

#include "../../core/inc/String.hpp"

#include <chrono>
#include <format>

namespace jp::game
{
   StateGame::StateGame(StateStack* stack, Context& context)
      : mGame(std::make_shared<Game>(context)), State(stack, context)
   {
      std::shared_ptr<core::Logger> logger = std::make_shared<core::Logger>(std::string(LOGS_DIR) + mContext.world + "_" +
         algorithm::Algorithm::nameToString(mContext.algorithm) + "_" + core::String::currentDate() + ".txt", true);

      mAlgorithm = algorithm::Algorithm::create(mContext.algorithm, mGame, logger, context.properties.algorithm);
   }

   void StateGame::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
   {
      target.draw(*mGame);
   }

   void StateGame::event(const sf::Event& event)
   {
      if (event.type == sf::Event::Closed)
      {
         if (mContext.algorithm == algorithm::AlgorithmName::Human)
         {
            mGame->save();
         }
      }

      if (event.type == sf::Event::KeyReleased)
      {
         switch (event.key.code)
         {
         case sf::Keyboard::Key::Escape:
            if (mContext.algorithm == algorithm::AlgorithmName::Human)
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
         std::string filename = core::String::toLower(mContext.world + "_" + mAlgorithm->getName());
         std::filesystem::remove(std::string(SAVES_DIR) + filename + ".json");
         std::string statisticsFilename = std::string(STATISTICS_DIR) + filename + "_" + core::String::currentDate() + ".json";
         mAlgorithm->saveStatistics(statisticsFilename);
         mContext.statistics = mGame->getStatistics();
         popState();
         pushState(StateID::Win);
      }
      mAlgorithm->update(dt);
   }
}