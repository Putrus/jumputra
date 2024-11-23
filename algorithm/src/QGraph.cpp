#include "../inc/QGraph.hpp"

#include "../../core/inc/Random.hpp"

namespace jp::algorithm
{
   QGraph::QGraph(const Properties& properties) : mProperties(properties) {}

   void QGraph::insertEdge(const std::shared_ptr<logic::Segment>& originSegment,
      const std::shared_ptr<logic::Segment>& destinationSegment,
      const std::shared_ptr<EdgeMove>& edgeMove)
   {
      float reward = edgeMove->value;
      float q = 0.f;
      float maxQ = getMaxQ(destinationSegment);

      auto originFind = mAdjacencyList.find(originSegment);
      if (originFind != mAdjacencyList.end())
      {
         auto destinationFind = originFind->second.find(destinationSegment);
         if (destinationFind != originFind->second.end())
         {
            q = destinationFind->second->value;
            if (destinationFind->second->time <= edgeMove->time)
            {
               edgeMove->move = destinationFind->second->move;
               edgeMove->value += 1.f;
               edgeMove->time = destinationFind->second->time;
            }
         }
      }

      edgeMove->value = q + mProperties.qLearning.learningRate * (reward + mProperties.qLearning.discountFactor * maxQ - q);

      mAdjacencyList[originSegment][destinationSegment] = edgeMove;
      mBackwardAdjacencyList[destinationSegment][originSegment] = edgeMove;
   }

   std::shared_ptr<EdgeMove> QGraph::getBestAction(const std::shared_ptr<logic::Segment>& segment) const
   {
      std::shared_ptr<EdgeMove> bestAction = nullptr;
      auto segmentFind = mAdjacencyList.find(segment);
      if (segmentFind != mAdjacencyList.end())
      {
         for (const auto& action : segmentFind->second)
         {
            if (core::Random::getFloat(0, 1.f) > mProperties.qLearning.epsilon &&
               (!bestAction || action.second->value > bestAction->value))
            {
               bestAction = action.second;
            }
         }
      }

      if (!bestAction || bestAction->value < 0.f)
      {
         return nullptr;
      }
      return bestAction;
   }

   std::shared_ptr<EdgeMove> QGraph::getRandomAction(const std::shared_ptr<logic::Segment>& segment) const
   {
      std::shared_ptr<EdgeMove> randomAction = nullptr;
      auto segmentFind = mAdjacencyList.find(segment);
      if (segmentFind != mAdjacencyList.end())
      {
         for (const auto& action : segmentFind->second)
         {
            if (core::Random::getFloat(0, 1000.f) < action.second->value)
            {
               return action.second;
            }
         }
      }
      return randomAction;
   }

   float QGraph::getQ(const std::shared_ptr<logic::Segment>& originSegment,
      const std::shared_ptr<logic::Segment>& destinationSegment) const
   {
      float q = 0.f;
      auto originFind = mAdjacencyList.find(originSegment);
      if (originFind != mAdjacencyList.end())
      {
         auto destinationFind = originFind->second.find(destinationSegment);
         if (destinationFind != originFind->second.end())
         {
            return destinationFind->second->value;
         }
      }
      return q;
   }

   float QGraph::getMaxQ(const std::shared_ptr<logic::Segment>& segment) const
   {
      float maxQ = 0.f;
      auto segmentFind = mAdjacencyList.find(segment);
      if (segmentFind != mAdjacencyList.end())
      {
         for (const auto& move : segmentFind->second)
         {
            if (move.second->value > maxQ)
            {
               maxQ = move.second->value;
            }
         }
      }
      return maxQ;
   }
}