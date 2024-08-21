#include "../inc/DecisionNode.hpp"

namespace jp::algorithm
{
   DecisionNode::DecisionNode(DecisionNode* parent, const Move& move, std::set<std::shared_ptr<logic::Segment>>& visitedSegments,
         const logic::Character& character, const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties)
      : mParent(parent), mVisitedSegments(visitedSegments), Algorithm(engine, properties)
   {
      if (move.type != MoveType::Idle)
      {
         mMoves.push_back(move);
      }

      if (parent != nullptr && move.type == MoveType::Run ||
         (move.value == mProperties.decisionTree.jumpValue && character.isSticked()))
      {
         mEngine->addCharacterCopy(character);
         if (move.type == MoveType::Run)
         {
            mBots.push_back(Bot(mEngine->getCharacters().back(), { Move(MoveType::Run,
               move.direction, mProperties.decisionTree.runValue) }));
         }
         else
         {
            mBots.push_back(Bot(mEngine->getCharacters().back(), { Move(MoveType::Jump,
               move.direction, mProperties.decisionTree.jumpValue) }));
         }
      }
      else
      {
         if (character.isSticked())
         {
            mEngine->addCharacterCopy(character);
            mBots.push_back(Bot(mEngine->getCharacters().back(), { Move(MoveType::Jump,
               logic::CharacterDirection::Left, mProperties.decisionTree.jumpValue) }));
            mEngine->addCharacterCopy(character);
            mBots.push_back(Bot(mEngine->getCharacters().back(), { Move(MoveType::Jump,
               logic::CharacterDirection::Right, mProperties.decisionTree.jumpValue) }));
         }
         else
         {
            mEngine->addCharacterCopy(character);
            mBots.push_back(Bot(mEngine->getCharacters().back(), { Move(MoveType::Run,
               logic::CharacterDirection::Left, engine->getProperties().secondsPerUpdate) }));
            mEngine->addCharacterCopy(character);
            mBots.push_back(Bot(mEngine->getCharacters().back(), { Move(MoveType::Run,
               logic::CharacterDirection::Right, engine->getProperties().secondsPerUpdate) }));
         }
         
      }

      float step = mEngine->getProperties().character.jump.max.y * 2.f / static_cast<float>(mProperties.decisionTree.jumps);
      if (!mEngine->getWinds().empty())
      {
         step *= 1.5f;
      }

      for (float jumpPowerY = step; jumpPowerY <= mEngine->getProperties().character.jump.max.y; jumpPowerY += step)
      {
         if (jumpPowerY == mProperties.decisionTree.jumpValue)
         {
            continue;
         }
         mEngine->addCharacterCopy(character);
         mBots.push_back(Bot(mEngine->getCharacters().back(), { Move(MoveType::Jump, logic::CharacterDirection::Left, jumpPowerY) }));
         mEngine->addCharacterCopy(character);
         mBots.push_back(Bot(mEngine->getCharacters().back(), { Move(MoveType::Jump, logic::CharacterDirection::Right, jumpPowerY) }));
         if (!mEngine->getWinds().empty())
         {
            mEngine->addCharacterCopy(character);
            mBots.push_back(Bot(mEngine->getCharacters().back(), { Move(MoveType::Jump, logic::CharacterDirection::Up, jumpPowerY) }));
         }
      }
   }

   void DecisionNode::update(float dt)
   {
      for (auto& child : mChildren)
      {
         child->update(dt);
      }

      if (mBots.empty())
      {
         return;
      }

      for (auto& bot : mBots)
      {
         bot.update(dt);
      }

      if (std::find_if(mBots.begin(), mBots.end(), [](const auto& bot)
         { return !bot.finishedMoves(); }) == mBots.end())
      {
         for (auto& bot : mBots)
         {
            if (bot.getMoves().empty())
            {
               throw std::runtime_error("DecisionNode::update - Failed to update, bot moves are empty");
            }

            if (bot.getMoves().back().type == MoveType::Idle)
            {
               throw std::runtime_error("DecisionNode::update - Failed to update, wrong move type");
            }

            if (bot.getMoves().back().type == MoveType::Run)
            {
               if (bot.getPositionBeforeMoves() == bot.getFinishedCharacter().getPosition() ||
                  bot.getFinishedCharacter().getPosition().y > bot.getPositionBeforeMoves().y)
               {
                  mEngine->removeCharacter(bot.getCharacter());
                  continue;
               }

               mVisitedSegments.insert(bot.getCharacter()->getVisitedSegments().back());
               mChildren.push_back(std::make_shared<DecisionNode>(this, bot.getMoves().back(),
                  mVisitedSegments, bot.getFinishedCharacter(), mEngine, mProperties));
            }
            else if (mVisitedSegments.find(bot.getCharacter()->getVisitedSegments().back()) == mVisitedSegments.end() ||
               (bot.getMoves().back().value == mProperties.decisionTree.jumpValue && bot.getFinishedCharacter().isSticked()))
            {
               mVisitedSegments.insert(bot.getCharacter()->getVisitedSegments().back());
               mChildren.push_back(std::make_shared<DecisionNode>(this, bot.getMoves().back(),
                  mVisitedSegments, bot.getFinishedCharacter(), mEngine, mProperties));
            }

            mEngine->removeCharacter(bot.getCharacter());
         }
         mBots.clear();
      }
   }
}