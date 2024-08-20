#include "../inc/Greedy.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   Greedy::Greedy(const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties)
      : Algorithm(engine, properties)
   {
      nextIteration(*mEngine->getCharacters()[0]);
   }

   void Greedy::update(float dt)
   {
      for (auto& bot : mBots)
      {
         bot.update(dt);
      }

      if (std::find_if(mBots.begin(), mBots.end(), [](const auto& bot)
         { return !bot.finishedMoves(); }) == mBots.end())
      {
         auto bestJumperIt = std::min_element(mBots.begin(), mBots.end(),
         [](const auto& lhs, const auto& rhs)
         {
            return lhs.getFinishedCharacter().getPosition().y < rhs.getFinishedCharacter().getPosition().y;
         });

         Bot bestJumper = *bestJumperIt;
         if (bestJumper.getFinishedCharacter().getPosition().y == mLastY)
         {
            if (core::Random::getFloat(0, 1) <= mProperties.greedy.epsilon)
            {
               bestJumper = mBots.at(core::Random::getInt(0, mBots.size() - 1));
            }
            else
            {
               std::vector<Bot> filteredBots;
               for (const auto& bot : mBots)
               {
                  if (bot.getFinishedCharacter().getPosition().y == mLastY)
                  {
                     filteredBots.push_back(bot);
                  }
               }

               bestJumper = filteredBots.at(core::Random::getInt(0, filteredBots.size() - 1));
            }
         }

         mMoves.push_back(bestJumper.getMoves().back());
         nextIteration(bestJumper.getFinishedCharacter());
      }
   }

   void Greedy::addBot(const logic::Character& character, const Move& move)
   {
      mEngine->addCharacterCopy(character);
      mBots.push_back(Bot(mEngine->getCharacters().back(), { move }));
   }

   void Greedy::clear()
   {
      mBots.clear();
      mEngine->removeAllCharacters();
   }

   void Greedy::nextIteration(logic::Character bestJumper)
   {
      mLastY = bestJumper.getPosition().y;
      clear();

      std::cout << "Iteration: " << mMoves.size() << " position: " << bestJumper.getPosition() << std::endl;

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