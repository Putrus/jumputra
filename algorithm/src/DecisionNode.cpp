#include "../inc/DecisionNode.hpp"

namespace jp::algorithm
{
   DecisionNode::DecisionNode(DecisionNode* parent, const Move& move, std::set<std::shared_ptr<logic::Segment>>& visitedSegments,
      const logic::Character& character, const std::shared_ptr<logic::Engine>& engine,
      const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties)
      : mParent(parent), mVisitedSegments(visitedSegments), Algorithm(engine, logger, properties)
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

      float step = mEngine->getProperties().character.jump.max.y * 2.f / static_cast<float>(mProperties.decisionTree.jumps);
      if (!mEngine->getWinds().empty())
      {
         step *= 1.5f;
      }

      for (float jumpPowerY = step; jumpPowerY < mEngine->getProperties().character.jump.max.y + step; jumpPowerY += step)
      {
         if (jumpPowerY == mProperties.decisionTree.jumpValue)
         {
            continue;
         }
         addBot(character, Move(MoveType::Jump,
               logic::CharacterDirection::Left, jumpPowerY));
         addBot(character, Move(MoveType::Jump,
            logic::CharacterDirection::Right, jumpPowerY));
         if (!mEngine->getWinds().empty())
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

      for (auto& bot : mBots)
      {
         bot->update(dt);
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

            if (bot->getMoves().back().type == MoveType::Run)
            {
               if (bot->getPositionBeforeMoves() == bot->getFinishedCharacter().getPosition() ||
                  bot->getFinishedCharacter().getPosition().y > bot->getPositionBeforeMoves().y)
               {
                  mEngine->removeCharacter(bot->getCharacter());
                  continue;
               }

               if (!bot->getCharacter()->getVisitedSegments().empty())
               {
                  mVisitedSegments.insert(bot->getCharacter()->getVisitedSegments().back());
               }

               mChildren.push_back(std::make_shared<DecisionNode>(this, bot->getMoves().back(),
                  mVisitedSegments, bot->getFinishedCharacter(), mEngine, mLogger, mProperties));

               *mLogger << "New node at the position: " << bot->getFinishedCharacter().getPosition() << std::endl;
            }
            else if (bot->getCharacter()->getVisitedSegments().empty() || mVisitedSegments.find(bot->getCharacter()->getVisitedSegments().back()) == mVisitedSegments.end() ||
               (bot->getMoves().back().value == mProperties.decisionTree.jumpValue && bot->getFinishedCharacter().isSticked()))
            {
               if (!bot->getCharacter()->getVisitedSegments().empty())
               {
                  mVisitedSegments.insert(bot->getCharacter()->getVisitedSegments().back());
               }

               mChildren.push_back(std::make_shared<DecisionNode>(this, bot->getMoves().back(),
                  mVisitedSegments, bot->getFinishedCharacter(), mEngine, mLogger, mProperties));

               *mLogger << "New node at the position: " << bot->getFinishedCharacter().getPosition() << std::endl;
            }

            mEngine->removeCharacter(bot->getCharacter());
         }
         mBots.clear();
      }
   }

   const std::vector<std::shared_ptr<DecisionNode>>& DecisionNode::getChildren() const
   {
      return mChildren;
   }
}