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

   void StateGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(*mGame);
   }

   void StateGame::event(const std::optional<sf::Event>& event)
   {
      if (event->is<sf::Event::Closed>())
        {
         if (mContext.algorithm == algorithm::AlgorithmName::Human)
         {
            mGame->save();
         }
      }

      if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
      {
         switch (keyReleased->scancode)
         {
         case sf::Keyboard::Scancode::Escape:
            if (mContext.algorithm == algorithm::AlgorithmName::Human)
            {
               mGame->save();
            }
            mGame->resetView();
            mContext.statistics = mGame->getStatistics();
            pushState(StateID::Pause);
            break;
         case sf::Keyboard::Scancode::M:
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
      mAlgorithm->update(dt);
      mGame->update(dt);
      if (mGame->getWinner())
      {
         if (mContext.algorithm == algorithm::AlgorithmName::Human)
         {
            std::filesystem::remove(std::string(SAVES_DIR) + mContext.world + ".json");
         }

         if (!std::filesystem::exists(STATISTICS_DIR))
         {
            std::filesystem::create_directory(STATISTICS_DIR);
         }

         mAlgorithm->fillMoves(mGame->getWinner());
         std::string filename = std::string(STATISTICS_DIR) +
            core::String::toLower(mContext.world + "_" + mAlgorithm->getName()) + "_" + core::String::currentDate() + ".json";
         mAlgorithm->saveStatistics(filename);
         mContext.statistics = mGame->getStatistics();
         popState();
         pushState(StateID::Win);
      }
   }
}