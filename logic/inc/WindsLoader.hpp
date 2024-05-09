#pragma once

#include "EntityLoader.hpp"

namespace jp::logic
{
   template <typename T>
   class WindsLoader : public EntityLoader<T>
   {
   public:
      std::vector<std::shared_ptr<T>> loadFromJson(const nlohmann::json& json) const;
   };

   template <typename T>
   std::vector<std::shared_ptr<T>> WindsLoader<T>::loadFromJson(const nlohmann::json& json) const
   {
      std::vector<std::shared_ptr<T>> winds;
      for (const auto& jsonWind : json["winds"])
      {
         float impact = jsonWind["impact"];
         math::Vector2<float> acceleration(jsonWind["acceleration"]);
         math::Vector2<float> maxVelocity(jsonWind["maxVelocity"]);
         math::Rect<float> rect(jsonWind["rect"]);
         math::Vector2<float> velocity(jsonWind["velocity"]);
         winds.push_back(T::create(impact, maxVelocity, rect, acceleration, velocity));
      }

      return winds;
   }
}