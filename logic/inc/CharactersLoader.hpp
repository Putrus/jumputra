#pragma once

#include "EntityLoader.hpp"

namespace jp::logic
{
   template <typename T>
   class CharactersLoader : public EntityLoader<T>
   {
   public:
      std::vector<std::shared_ptr<T>> loadFromJson(const nlohmann::json& json) const;
   };

   template <typename T>
   std::vector<std::shared_ptr<T>> CharactersLoader<T>::loadFromJson(const nlohmann::json& json) const
   {
      std::vector<std::shared_ptr<T>> characters;
      for (const auto& jsonWind : json["characters"])
      {
         //TODO
      }

      return characters;
   }
}