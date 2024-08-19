#pragma once

#include "Algorithm.hpp"
#include "Bot.hpp"

#include <memory>
#include <set>
#include <vector>

namespace jp::algorithm
{
   class DecisionNode : public Algorithm
   {
   public:
      DecisionNode(DecisionNode* parent, const Move& move, std::set<std::shared_ptr<logic::Segment>>& visitedSegments,
         const logic::Character& character, const std::shared_ptr<logic::Engine>& engine, const algorithm::Properties& properties);

      void update(float dt) override;

   private:
      std::vector<Bot> mBots;
      std::set<std::shared_ptr<logic::Segment>>& mVisitedSegments;
      DecisionNode* mParent;
      std::vector<std::shared_ptr<DecisionNode>> mChildren;
   };
}