#pragma once

#include "../../graphic/inc/Wind.hpp"
#include "../../logic/inc/Wind.hpp"

namespace jp::game
{
   class Wind : public graphic::Wind, public logic::Wind
   {
   public:
      Wind(float impact, const math::Vector2<float>& maxVelocity,
         const math::Rect<float>& rect, const math::Vector2<float>& acceleration,
         const math::Vector2<float>& velocity = 0.f);
      Wind(const nlohmann::json& json);

      static std::shared_ptr<Wind> create(const nlohmann::json& json);    

      void update(float dt) override;
   };
}