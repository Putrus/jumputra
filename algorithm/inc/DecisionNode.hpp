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
         const logic::Character& character, const std::shared_ptr<logic::Engine>& engine,
         const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties);

      void update(float dt) override;

   private:
      std::set<std::shared_ptr<logic::Segment>>& mVisitedSegments;
      DecisionNode* mParent;
      std::vector<std::shared_ptr<DecisionNode>> mChildren;
   };
}