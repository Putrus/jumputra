#include "../inc/StateGame.hpp"

#include "../../algorithm/inc/AntColony.hpp"
#include "../../algorithm/inc/Dummy.hpp"
#include "../../algorithm/inc/Genetic.hpp"
#include "../../algorithm/inc/Greedy.hpp"

#include <chrono>
#include <format>

namespace jp::game
{
   StateGame::StateGame(StateStack* stack, Context& context)
      : mGame(std::make_shared<Game>(context)), State(stack, context)
   {
      switch (context.controller)
      {
      case Controller::AntColony:
         mAlgorithm = std::make_shared<algorithm::AntColony>(mGame, mContext.properties.algorithm);
         break;
      case Controller::Genetic:
         mAlgorithm = std::make_shared<algorithm::Genetic>(mGame, mContext.properties.algorithm);
         break;
      case Controller::Greedy:
         mAlgorithm = std::make_shared<algorithm::Greedy>(mGame, mContext.properties.algorithm);
         break;
      case Controller::Human:
         mAlgorithm = std::make_shared<algorithm::Dummy>(mGame, mContext.properties.algorithm);
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
      if (mGame->hasGoalBeenAchieved())
      {
         const auto now = std::chrono::system_clock::now();
         std::string time = std::format("{:%d-%m-%Y_%H-%M}", now);
         std::stringstream filenameSS;
         filenameSS << mContext.world << '_' << mContext.controller;
         std::string filename = filenameSS.str();
         std::transform(filename.begin(), filename.end(), filename.begin(),
            [](char c) { return std::tolower(c); });
         std::filesystem::remove(std::string(SAVES_DIR) + filename + ".json");
         mGame->saveStatistics(std::string(STATISTICS_DIR) + filename + "_" + time + ".json");
         mContext.statistics = mGame->getStatistics();
         popState();
         pushState(StateID::Win);
      }
      mAlgorithm->update(dt);
   }
}