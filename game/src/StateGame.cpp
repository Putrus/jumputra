#include "../inc/StateGame.hpp"

#include <chrono>
#include <format>

namespace jp::game
{
   StateGame::StateGame(StateStack* stack, Context& context)
      : mGame(std::make_shared<Game>(context)), mAgent(agents::Agent::create(context.agent)), State(stack, context) {}

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
      mAgent->control(mGame);
   }
}