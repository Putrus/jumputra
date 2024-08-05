#include "../inc/Greedy.hpp"

#include <random>

namespace jp::agents
{
   Greedy::Greedy(int botsNumber/* = 100*/) : mBotsNumber(botsNumber) {}

   void Greedy::control(const std::shared_ptr<logic::Engine>& engine)
   {
      auto& characters = engine->characters();

      if (characters.size() == 1)
      {
         mLastY = characters.at(0)->getPosition().y;
      }

      auto findIt = std::find_if(characters.begin(), characters.end(),
         [](const auto& character)
         {
            return !character->canSquat() || character->getState() == logic::CharacterState::Squatting;
         });

      if (mSquatMustBeDone)
      {
         mSquatMustBeDone = false;
         for (size_t i = 0; i < mBots.size(); ++i)
         {
            characters.at(i + 1)->squat();
         }
         return;
      }

      if (findIt == characters.end())
      {
         auto bestJumperIt = std::min_element(characters.begin(), characters.end(),
         [](const auto& lhs, const auto& rhs)
         {
            return lhs->getPosition().y < rhs->getPosition().y;
         });

         std::shared_ptr<logic::Character>& bestJumper = *bestJumperIt;
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

         math::Rect<float> rect = bestJumper->getRect();
         mLastY = bestJumper->getPosition().y;
         engine->removeAllCharactersExcept(bestJumper);

         mBots.clear();
         for (int i = 0; i < mBotsNumber; ++i)
         {
            engine->addCharacter(rect);
            Bot bot;
            bot.jumpPowerY = randomInRange(0, engine->getProperties().character.jump.max.y);
            bot.direction = static_cast<logic::CharacterDirection>(randomInRange(1, 2));
            mBots.push_back(bot);
            characters.at(i + 1)->setDirection(bot.direction);
            characters.at(i + 1)->squat();
         }
         mSquatMustBeDone = true;
      }
      else
      {
         for (size_t i = 0; i < mBots.size(); ++i)
         {
            if (characters.at(i + 1)->getJumpPower().y >= mBots[i].jumpPowerY)
            {
               characters.at(i + 1)->jump();
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