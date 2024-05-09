#pragma once

#include "Jsonable.hpp"

#include "../../math/inc/Vector2.hpp"

namespace jp::logic
{
   struct Properties : public Jsonable
   {
      void fromJson(const nlohmann::json& json) override;
      nlohmann::json toJson() const override;

      float secondsPerUpdate = 0.f;

      struct Character
      {
         struct Jump
         {
            math::Vector2<float> gain = 0.f;
            math::Vector2<float> max = 0.f;
         } jump;
         float runSpeed = 0.f;
         math::Vector2<float> size = 0.f;
      } character;

      struct Physics
      {
         float bounceFactor = 0.f;
         float checkCollisionDistance = 0.f;
         float fallSpeed = 0.f;
         float slipperyFriction = 0.f;
         math::Vector2<float> gravity = 0.f;
      } physics;
   };
}