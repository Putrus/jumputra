#include "../inc/DecisionNode.hpp"

constexpr float JUMP_RUN_VALUE = 10.f;

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
         (move.value == JUMP_RUN_VALUE && character.isSticked()))
      {
         mEngine->addCharacterCopy(character);
         if (move.type == MoveType::Run)
         {
            mBots.push_back(Bot(mEngine->getCharacters().back(), { Move(MoveType::Run,
               move.direction, engine->getProperties().secondsPerUpdate) }));
         }
         else
         {
            mBots.push_back(Bot(mEngine->getCharacters().back(), { Move(MoveType::Jump,
               move.direction, JUMP_RUN_VALUE) }));
         }
      }
      else
      {
         if (character.isSticked())
         {
            mEngine->addCharacterCopy(character);
            mBots.push_back(Bot(mEngine->getCharacters().back(), { Move(MoveType::Jump,
               logic::CharacterDirection::Left, JUMP_RUN_VALUE) }));
            mEngine->addCharacterCopy(character);
            mBots.push_back(Bot(mEngine->getCharacters().back(), { Move(MoveType::Jump,
               logic::CharacterDirection::Right, JUMP_RUN_VALUE) }));
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

      for (float jumpPowerY = 50.f; jumpPowerY <= mEngine->getProperties().character.jump.max.y; jumpPowerY += 50.f)
      {
         mEngine->addCharacterCopy(character);
         mBots.push_back(Bot(mEngine->getCharacters().back(), { Move(MoveType::Jump, logic::CharacterDirection::Left, jumpPowerY) }));
         mEngine->addCharacterCopy(character);
         mBots.push_back(Bot(mEngine->getCharacters().back(), { Move(MoveType::Jump, logic::CharacterDirection::Right, jumpPowerY) }));
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
               (bot.getMoves().back().value == JUMP_RUN_VALUE && bot.getFinishedCharacter().isSticked()))
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