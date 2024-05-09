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
      for (const auto& jsonCharacter : json["characters"])
      {
         math::Rect<float> rect(jsonCharacter["rect"]);
         math::Vector2<float> acceleration(jsonCharacter["acceleration"]);
         math::Vector2<float> velocity(jsonCharacter["velocity"]);
         CharacterState state = static_cast<CharacterState>(jsonCharacter["state"]);
         CharacterDirection direction = static_cast<CharacterDirection>(jsonCharacter["direction"]);
         math::Vector2<float> jumpPower(jsonCharacter["jumpPower"]);
         math::Vector2<float> gravity(jsonCharacter["gravity"]);
         float runSpeed = jsonCharacter["runSpeed"];
         Statistics statistics(jsonCharacter["statistics"]);
      }

      return characters;
   }
}