#pragma once

#include "Entity.hpp"

namespace jp::game::physics
{
   class Wind final : public Entity
   {
   public:
      Wind();
      Wind(float impact, const math::Vector2<float>& maxVelocity,
         const math::Rect<float>& rect, const math::Vector2<float>& acceleration,
         const math::Vector2<float>& velocity = 0.f);

      float getImpact() const;
      const math::Vector2<float>& getMaxVelocity() const;

      void setMaxVelocity(const math::Vector2<float>& maxVelocity);

   private:
      float mImpact = 0.f;
      math::Vector2<float> mMaxVelocity = 0.f;
   };
}