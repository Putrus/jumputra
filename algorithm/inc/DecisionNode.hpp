#pragma once

#include "Algorithm.hpp"
#include "Bot.hpp"

#include <memory>
#include <set>

namespace jp::algorithm
{
   class DecisionNode : public Algorithm
   {
   public:
      DecisionNode(DecisionNode* parent, const Move& move, std::set<std::shared_ptr<logic::Segment>>& visitedSegments,
         std::vector<Move>& moves, const logic::Character& character, const std::shared_ptr<logic::Engine>& engine,
         const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties);

      std::string getName() const override;
      void update(float dt) override;

      const std::vector<std::shared_ptr<DecisionNode>>& getChildren() const;
      DecisionNode* getParent();

   private:
      void fillResultMoves(const Move& lastMove);

      DecisionNode* mParent;
      std::set<std::shared_ptr<logic::Segment>>& mVisitedSegments;
      std::vector<Move>& mResultMoves;
      std::vector<std::shared_ptr<DecisionNode>> mChildren;
   };
}