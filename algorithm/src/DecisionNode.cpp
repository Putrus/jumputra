#include "../inc/DecisionNode.hpp"

namespace jp::algorithm
{
   DecisionNode::DecisionNode(DecisionNode* parent, const Move& move, std::set<std::shared_ptr<logic::Segment>>& visitedSegments,
      std::vector<Move>& moves, const logic::Character& character, const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : mParent(parent), mVisitedSegments(visitedSegments), mResultMoves(moves), Algorithm(engine, logger, properties)
   {
      if (move.type != MoveType::Idle)
      {
         mMoves.push_back(move);
      }

      if (parent != nullptr && move.type == MoveType::Run ||
         (move.value == mProperties.decisionTree.jumpValue && character.isSticked()))
      {
         if (move.type == MoveType::Run)
         {
            addBot(character, Move(MoveType::Run,
               move.direction, mProperties.decisionTree.runValue));
         }
         else
         {
            addBot(character, Move(MoveType::Jump,
               move.direction, mProperties.decisionTree.jumpValue));
         }
      }
      else
      {
         if (character.isSticked())
         {
            addBot(character, Move(MoveType::Jump,
               logic::CharacterDirection::Left, mProperties.decisionTree.jumpValue));
            addBot(character, Move(MoveType::Jump,
               logic::CharacterDirection::Right, mProperties.decisionTree.jumpValue));
         }
         else
         {
            addBot(character, Move(MoveType::Run,
               logic::CharacterDirection::Left, mProperties.decisionTree.runValue));
            addBot(character, Move(MoveType::Run,
               logic::CharacterDirection::Right, mProperties.decisionTree.runValue));
         }
         
      }

      auto lockedEngine = mEngine.lock();
      if (!lockedEngine)
      {
         throw std::runtime_error("jp::algorithm::DecisionNode::DecisionNode - Failed to create decision node, engine doesn't exist");
      }

      float step = lockedEngine->getProperties().character.jump.max.y * 2.f / static_cast<float>(mProperties.decisionTree.jumps);
      if (!lockedEngine->getWinds().empty())
      {
         step *= 1.5f;
      }

      for (float jumpPowerY = step; jumpPowerY < lockedEngine->getProperties().character.jump.max.y + step; jumpPowerY += step)
      {
         if (jumpPowerY == mProperties.decisionTree.jumpValue)
         {
            continue;
         }
         addBot(character, Move(MoveType::Jump,
               logic::CharacterDirection::Left, jumpPowerY));
         addBot(character, Move(MoveType::Jump,
            logic::CharacterDirection::Right, jumpPowerY));
         if (!lockedEngine->getWinds().empty())
         {
            addBot(character, Move(MoveType::Jump,
            logic::CharacterDirection::Up, jumpPowerY));
         }
      }
   }

   std::string DecisionNode::getName() const
   {
      return "DecisionNode";
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

      auto lockedEngine = mEngine.lock();
      if (!lockedEngine)
      {
         throw std::runtime_error("jp::algorithm::DecisionNode::update - Failed to update, engine doesn't exist");
      }

      for (auto& bot : mBots)
      {
         bot->update(dt);
         if (lockedEngine->getWinner() == bot->getCharacter())
         {
            if (bot->getMoves().empty())
            {
               throw std::runtime_error("jp::algorithm::DecisionNode::update - Failed to fill result moves, winner bot moves are empty");
            }

            fillResultMoves(bot->getMoves().back());
            return;
         }
      }

      if (haveBotsFinishedMoves())
      {
         for (auto& bot : mBots)
         {
            if (bot->getMoves().empty())
            {
               throw std::runtime_error("jp::algorithm::DecisionNode::update - Failed to update, bot moves are empty");
            }

            if (bot->getMoves().back().type == MoveType::Idle)
            {
               throw std::runtime_error("jp::algorithm::DecisionNode::update - Failed to update, wrong move type");
            }

            if (bot->getCharacter()->getVisitedSegments().empty())
            {
               throw std::runtime_error("jp::algorithm::DecisionNode::update - Failed to update, bot visited segments are empty");
            }

            if (bot->getMoves().back().type == MoveType::Run)
            {
               if (bot->getPositionBeforeMoves() == bot->getFinishedCharacter().getPosition() ||
                  bot->getFinishedCharacter().getPosition().y > bot->getPositionBeforeMoves().y)
               {
                  lockedEngine->removeCharacter(bot->getCharacter());
                  continue;
               }

               mVisitedSegments.insert(bot->getCharacter()->getVisitedSegments().back());
               mChildren.push_back(std::make_shared<DecisionNode>(this, bot->getMoves().back(),
                  mVisitedSegments, mResultMoves, bot->getFinishedCharacter(), lockedEngine, mLogger, mProperties));

               *mLogger << "New node at the position: " << bot->getFinishedCharacter().getPosition() << std::endl;
            }
            else if (mVisitedSegments.find(bot->getCharacter()->getVisitedSegments().back()) == mVisitedSegments.end() ||
               (bot->getMoves().back().value == mProperties.decisionTree.jumpValue && bot->getFinishedCharacter().isSticked()))
            {
               mVisitedSegments.insert(bot->getCharacter()->getVisitedSegments().back());
               mChildren.push_back(std::make_shared<DecisionNode>(this, bot->getMoves().back(),
                  mVisitedSegments, mResultMoves, bot->getFinishedCharacter(), lockedEngine, mLogger, mProperties));

               *mLogger << "New node at the position: " << bot->getFinishedCharacter().getPosition() << std::endl;
            }

            lockedEngine->removeCharacter(bot->getCharacter());
         }
         mBots.clear();
      }
   }

   const std::vector<std::shared_ptr<DecisionNode>>& DecisionNode::getChildren() const
   {
      return mChildren;
   }

   DecisionNode* DecisionNode::getParent()
   {
      return mParent;
   }

   void DecisionNode::fillResultMoves(const Move& lastMove)
   {
      mResultMoves.push_back(lastMove);
      DecisionNode* parent = mParent;
      while (parent != nullptr && !parent->getMoves().empty())
      {
         mResultMoves.push_back(parent->getMoves().back());
         parent = parent->getParent();
      }
      std::reverse(mResultMoves.begin(), mResultMoves.end());
   }
}