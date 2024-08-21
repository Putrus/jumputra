#pragma once

#include "../../core/inc/Jsonable.hpp"

namespace jp::algorithm
{
   struct Properties : public core::Jsonable
   {
      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

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
            size_t elitism;
         } population;

         struct Mutation
         {
            float max;
            float change;
         } mutation;

         struct Tournament
         {
            size_t size;
         } tournament;

      } genetic;

      struct Greedy
      {
         size_t bots;
         float epsilon;
      } greedy;
   };
}