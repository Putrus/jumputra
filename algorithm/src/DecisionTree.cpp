#include "../inc/DecisionTree.hpp"

namespace jp::algorithm
{
   DecisionTree::DecisionTree(const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties)
      : Algorithm(engine, properties)
   {
      math::Rect<float> startRect = math::Rect<float>(200.f, 15100.f, 24.f, 24.f);
      //(engine->getCharacters().at(0)->getRect();
      mBots.clear();
      mEngine->removeAllCharacters();
      int i = 0;
      for (float jumpPowerY = 50.f; jumpPowerY <= mEngine->getProperties().character.jump.max.y; jumpPowerY += 50.f)
      {
         mEngine->addCharacter(startRect);
         mBots.push_back(Bot(mEngine->characters().at(i++), { Move(MoveType::Jump, logic::CharacterDirection::Left, jumpPowerY) }));
         mEngine->addCharacter(startRect);
         mBots.push_back(Bot(mEngine->characters().at(i++), { Move(MoveType::Jump, logic::CharacterDirection::Right, jumpPowerY) }));
      }
      mEngine->addCharacter(startRect);
      mBots.push_back(Bot(mEngine->characters().at(i), { Move(MoveType::Run, mRunDirection, mEngine->getProperties().secondsPerUpdate) }));
   }

   void DecisionTree::update(float dt)
   {
      for (auto& bot : mBots)
      {
         bot.update(dt);
      }

      if (std::find_if(mBots.begin(), mBots.end(), [](const auto& bot)
         { return !bot.finishedMoves(); }) == mBots.end())
      {
         //run character at the beginning is the best
         logic::Character bestDecisionCharacter = mBots.back().getFinishedCharacter();
         if (bestDecisionCharacter.getPosition() == mLastRunPosition)
         {
            mRunDirection = logic::Character::oppositeDirection(mRunDirection);
         }
         mLastRunPosition = bestDecisionCharacter.getPosition();
         
         // for (const auto& bot : mBots)
         // {
         //    if (bot.getPosition().y < bestDecisionCharacter.getPosition().y)
         //    {
         //       bestDecisionCharacter = *bot.getCharacter();
         //    }
         // }

         mBots.clear();
         mEngine->removeAllCharacters();
         int i = 0;
         for (float jumpPowerY = 50.f; jumpPowerY <= mEngine->getProperties().character.jump.max.y; jumpPowerY += 50.f)
         {
            mEngine->addCharacterCopy(bestDecisionCharacter);
            mBots.push_back(Bot(mEngine->characters().at(i++), { Move(MoveType::Jump, logic::CharacterDirection::Left, jumpPowerY) }));
            mEngine->addCharacterCopy(bestDecisionCharacter);
            mBots.push_back(Bot(mEngine->characters().at(i++), { Move(MoveType::Jump, logic::CharacterDirection::Right, jumpPowerY) }));
         }
         mEngine->addCharacterCopy(bestDecisionCharacter);
         mBots.push_back(Bot(mEngine->characters().at(i), { Move(MoveType::Run, mRunDirection, dt *  12) }));
      }
   }
}