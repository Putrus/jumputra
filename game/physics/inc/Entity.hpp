#pragma once

#include "../../../math/inc/Rect.hpp"

namespace jp::game::physics
{
   class Entity
   {
   public:
      Entity();
      Entity(const math::Rect<float>& rect,
         const math::Vector2<float>& acceleration = 0.f,
         const math::Vector2<float>& velocity = 0.f);

      math::Vector2<float> getPosition() const;
      const math::Rect<float>& getRect() const;
      const math::Vector2<float>& getAcceleration() const;
      const math::Vector2<float>& getVelocity() const;

      void setPosition(float x, float y);
      void setPosition(const math::Vector2<float>& position);
      void setRect(const math::Rect<float>& rect);
      void setRectTop(float y);
      void setRectBottom(float y);
      void setRectLeft(float x);
      void setRectRight(float x);
      void setAcceleration(const math::Vector2<float>& acceleration);
      void setAccelerationX(float x);
      void setAccelerationY(float y);
      void setVelocity(const math::Vector2<float>& velocity);
      void setVelocityX(float x);
      void setVelocityY(float y);

   protected:
      math::Rect<float> mRect;
      math::Vector2<float> mAcceleration;
      math::Vector2<float> mVelocity;
   };
}