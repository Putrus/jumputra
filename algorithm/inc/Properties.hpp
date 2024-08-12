#pragma once

#include "../../core/inc/Jsonable.hpp"

namespace jp::algorithm
{
   struct Properties : public core::Jsonable
   {
      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

      struct Genetic
      {
         struct Population
         {
            size_t size;
         } population;

         struct Mutation
         {
            float max;
            float change;
         } mutation;

      } genetic;
      struct Greedy
      {
         size_t bots;
      } greedy;
   };
}