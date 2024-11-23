#pragma once

#include "../../core/inc/Jsonable.hpp"

namespace jp::algorithm
{
   struct Properties : public core::Jsonable
   {
      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

      struct AntColony
      {
         size_t ants;
         float randomJumpChance;
         float evaporationRate;
         float maxIntensity;
         float minIntensity;
      } antColony;

      struct DecisionTree
      {
         size_t jumps;
         float jumpValue;
         float runValue;
      } decisionTree;

      struct Genetic
      {
         struct Population
         {
            size_t size;
            float elitism;
         } population;

         struct Mutation
         {
            float max;
            float change;
         } mutation;

         float tournament;
         float visitedSegmentsImpact;

      } genetic;

      struct Greedy
      {
         size_t bots;
         float epsilon;
      } greedy;

      struct QLearning
      {
         size_t agents;
         float learningRate;
         float discountFactor;
         float epsilon;
         float randomJumpChance;
      } qLearning;
   };
}