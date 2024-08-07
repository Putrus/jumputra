#include "../inc/Greedy.hpp"

namespace jp::algorithm
{
   Greedy::Greedy(const std::shared_ptr<logic::Engine>& engine, size_t bots/* = 100*/)
      : mBotsSize(bots), Algorithm(engine)
   {
      logic::Character character = *mEngine->getCharacters()[0];
      nextIteration(character);
   }

   void Greedy::update(float dt)
   {
      for (auto& bot : mBots)
      {
         bot.update(dt);
      }

      for (size_t i = 0; i < mBots.size(); ++i)
      {
         if (mCharactersThatLanded.find(i) == mCharactersThatLanded.end() && mBots.at(i).finishedMoves())
         {
            mCharactersThatLanded.insert({ i, logic::Character(*mBots.at(i).getCharacter()) });
         }
      }

      if (mCharactersThatLanded.size() == mBotsSize)
      {
         auto bestJumperIt = std::min_element(mCharactersThatLanded.begin(), mCharactersThatLanded.end(),
         [](const auto& lhs, const auto& rhs)
         {
            return lhs.second.getPosition().y < rhs.second.getPosition().y;
         });

         if (bestJumperIt == mCharactersThatLanded.end())
         {
            throw std::runtime_error("Greedy::update - Failed to find best jumper in this group");
         }

         logic::Character bestJumper = bestJumperIt->second;
         Move bestMove = mBots.at(bestJumperIt->first).getMoves().at(0);
         if (bestJumper.getPosition().y == mLastY)
         {
            int random = randomInRange(1, 5);
            if (random == 1)
            {
               int randomId = randomInRange(0, mCharactersThatLanded.size() - 1);
               bestJumper = mCharactersThatLanded.at(randomId);
               bestMove = mBots.at(randomId).getMoves().at(0);
            }
            else
            {
               std::map<size_t, logic::Character> filteredCharacters;
               for (const auto& character : mCharactersThatLanded)
               {
                  if (character.second.getPosition().y == mLastY)
                  {
                     filteredCharacters.insert(character);
                  }
               }

               int randomId = randomInRange(0, filteredCharacters.size() - 1);

               int id = 0;
               for (const auto& character : filteredCharacters)
               {
                  if (id == randomId)
                  {
                     bestJumper = character.second;
                     bestMove = mBots.at(character.first).getMoves().at(0);
                     break;
                  }
                  ++id;
               }
            }
         }

         mMoves.push_back(bestMove);
         nextIteration(bestJumper);
      }
   }

   void Greedy::nextIteration(const logic::Character& character)
   {
      mLastY = character.getPosition().y;
      mCharactersThatLanded.clear();
      mBots.clear();
      mEngine->removeAllCharacters();

      for (int i = 0; i < mBotsSize; ++i)
      {
         mEngine->addCharacterCopy(character);
         mBots.push_back(Bot(mEngine->characters().at(i), { randomJump() }));
      }
   }
}