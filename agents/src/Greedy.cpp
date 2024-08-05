#include "../inc/Greedy.hpp"

#include <random>

namespace jp::agents
{
   Greedy::Greedy(size_t bots/* = 100*/) : mBotsSize(bots) {}

   void Greedy::control(const std::shared_ptr<logic::Engine>& engine)
   {
      auto& characters = engine->characters();

      if (characters.size() == 1)
      {
         mLastY = characters.at(0)->getPosition().y;
      }

      if (mSquatMustBeDone)
      {
         mSquatMustBeDone = false;
         for (auto& character : characters)
         {
            character->squat();
         }
         return;
      }

      auto findIt = std::find_if(characters.begin(), characters.end(),
         [](const auto& character)
         {
            return !character->canSquat() || character->getState() == logic::CharacterState::Squatting;
         });

      if (findIt == characters.end())
      {
         auto bestJumperIt = std::min_element(characters.begin(), characters.end(),
         [](const auto& lhs, const auto& rhs)
         {
            return lhs->getPosition().y < rhs->getPosition().y;
         });

         std::shared_ptr<logic::Character> bestJumper = *bestJumperIt;
         if (bestJumper->getPosition().y == mLastY)
         {
            int random = randomInRange(1, 5);
            if (random == 1)
            {
               bestJumper = characters.at(randomInRange(0, characters.size() - 1));
            }
            else
            {
               std::vector<std::shared_ptr<logic::Character>> filteredCharacters;
               std::copy_if(characters.begin(), characters.end(), std::back_inserter(filteredCharacters),
               [this](const std::shared_ptr<logic::Character>& character)
               {
                  return character->getPosition().y == mLastY;
               });

               bestJumper = filteredCharacters.at(randomInRange(0, filteredCharacters.size() - 1));
            }
         }

         mLastY = bestJumper->getPosition().y;
         engine->removeAllCharacters();

         mTargetJumpPowers.clear();
         for (int i = 0; i < mBotsSize; ++i)
         {
            engine->addCharacterCopy(bestJumper);
            mTargetJumpPowers.push_back(randomInRange(0, engine->getProperties().character.jump.max.y));
            characters.at(i)->setDirection(static_cast<logic::CharacterDirection>(randomInRange(1, 2)));
            characters.at(i)->squat();
         }
         mSquatMustBeDone = true;
      }
      else
      {
         for (size_t i = 0; i < mTargetJumpPowers.size(); ++i)
         {
            if (characters.at(i)->getJumpPower().y >= mTargetJumpPowers[i])
            {
               characters.at(i)->jump();
            }
         }
      }
   }

   int Greedy::randomInRange(int min, int max)
   {
      std::random_device rd;
      std::mt19937 gen(rd());

      std::uniform_int_distribution<std::mt19937::result_type> distrib(min, max);

      return distrib(gen);
   }
}