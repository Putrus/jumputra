#pragma once

#include "DecisionNode.hpp"

#include <set>

namespace jp::algorithm
{
   class DecisionTree final : public Algorithm
   {
   public:
      DecisionTree(const std::shared_ptr<logic::Engine>& engine,
         const std::shared_ptr<core::Logger>& logger, const algorithm::Properties& properties);

      void update(float dt) override;

   private:
      std::shared_ptr<DecisionNode> mNode;
      std::set<std::shared_ptr<logic::Segment>> mVisitedSegments;
   };
}