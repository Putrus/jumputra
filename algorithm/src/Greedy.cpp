#include "../inc/Greedy.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   Greedy::Greedy(const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : Algorithm(engine, logger, properties)
   {
      nextIteration(*mEngine->getCharacters()[0]);
   }

   std::string Greedy::getName() const
   {
      return "Greedy";
   }

   void Greedy::update(float dt)
   {
      for (auto& bot : mBots)
      {
         bot->update(dt);
      }

      if (haveBotsFinishedMoves())
      {
         auto bestJumperIt = std::min_element(mBots.begin(), mBots.end(),
         [](const auto& lhs, const auto& rhs)
         {
            return lhs->getFinishedCharacter().getPosition().y < rhs->getFinishedCharacter().getPosition().y;
         });

         std::shared_ptr<Bot> bestJumper = *bestJumperIt;
         if (bestJumper->getFinishedCharacter().getPosition().y == mLastY)
         {
            if (core::Random::getFloat(0, 1) <= mProperties.greedy.epsilon)
            {
               bestJumper = mBots.at(core::Random::getInt(0, mBots.size() - 1));
            }
            else
            {
               std::vector<std::shared_ptr<Bot>> filteredBots;
               for (const auto& bot : mBots)
               {
                  if (bot->getFinishedCharacter().getPosition().y == mLastY)
                  {
                     filteredBots.push_back(bot);
                  }
               }

               bestJumper = filteredBots.at(core::Random::getInt(0, filteredBots.size() - 1));
            }
         }

         mMoves.push_back(bestJumper->getMoves().back());
         nextIteration(bestJumper->getFinishedCharacter());
      }
   }

   void Greedy::nextIteration(logic::Character bestJumper)
   {
      mLastY = bestJumper.getPosition().y;
      clearBots();

      *mLogger << "Iteration: " << mMoves.size() << " position: " << bestJumper.getPosition() << std::endl;

      for (size_t i = 0; i < mProperties.greedy.bots; ++i)
      {
         if (mEngine->getWinds().empty())
         {
            addBot(bestJumper, Move::randomSideJump(1.f, mEngine->getProperties().character.jump.max.y));
         }
         else
         {
            addBot(bestJumper, Move::randomJump(1.f, mEngine->getProperties().character.jump.max.y));
         }
      }
   }
}