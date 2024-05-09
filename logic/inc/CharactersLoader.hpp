#pragma once

#include "EntityLoader.hpp"

namespace jp::logic
{
   template <typename T>
   class CharactersLoader : public EntityLoader<T>
   {
   public:
      CharactersLoader(const Properties &properties,
         const std::vector<std::shared_ptr<Segment>>& segments,
         const std::vector<std::shared_ptr<Wind>>& winds);
      std::vector<std::shared_ptr<T>> loadFromJson(const nlohmann::json& json) const;

   private:
      const Properties& mProperties;
      const std::vector<std::shared_ptr<Segment>>& mSegments;
      const std::vector<std::shared_ptr<Wind>>& mWinds;
   };

   template <typename T>
   CharactersLoader<T>::CharactersLoader(const Properties &properties,
      const std::vector<std::shared_ptr<Segment>>& segments,
      const std::vector<std::shared_ptr<Wind>>& winds)
      : mProperties(properties), mSegments(segments), mWinds(winds) {}

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
         characters.push_back(T::create(rect, acceleration, velocity, state, direction,
            jumpPower, gravity, runSpeed, statistics, mProperties, mSegments, mWinds));
      }

      return characters;
   }
}