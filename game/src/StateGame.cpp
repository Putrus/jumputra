#include "../inc/StateGame.hpp"

#include "../../agents/inc/Greedy.hpp"
#include "../../agents/inc/Human.hpp"

#include <chrono>
#include <format>

namespace jp::game
{
   StateGame::StateGame(StateStack* stack, Context& context)
      : mGame(std::make_shared<Game>(context)), State(stack, context)
   {
      switch (context.agent)
      {
      case agents::AgentName::Greedy:
         mAgent = std::make_shared<agents::Greedy>(mGame, context.properties.agents.greedy.bots);
         break;
      case agents::AgentName::Human:
         mAgent = std::make_shared<agents::Human>(mGame);
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
         mGame->save();
      }

      if (event.type == sf::Event::KeyReleased)
      {
         switch (event.key.code)
         {
         case sf::Keyboard::Key::Escape:
            mGame->save();
            mContext.statistics = mGame->getStatistics();
            popState();
            pushState(StateID::Pause);
            break;
         case sf::Keyboard::Key::M:
            mAgent->saveMoves("test.json");
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
         filenameSS << mContext.world << mContext.agent;
         std::string filename = filenameSS.str();
         std::filesystem::remove(std::string(SAVES_DIR) + filename + ".json");
         mGame->saveStatistics(std::string(STATISTICS_DIR) + filename + "_" + time + ".json");
         mContext.statistics = mGame->getStatistics();
         popState();
         pushState(StateID::Win);
      }
      mAgent->update(dt);
   }
}