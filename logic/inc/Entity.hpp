#pragma once

#include "Updatable.hpp"

#include "../../math/inc/Rect.hpp"

namespace jp::logic
{
   class Entity : public Updatable, public core::Jsonable
   {
   public:
      Entity();
      Entity(const math::Rect<float>& rect,
         const math::Vector2<float>& acceleration = 0.f,
         const math::Vector2<float>& velocity = 0.f);

      virtual void update(float dt) override;
      virtual void fromJson(const nlohmann::json& json) override;
      virtual nlohmann::json toJson() const override;

      math::Vector2<float> getPosition() const;
      const math::Rect<float>& getRect() const;
      const math::Vector2<float>& getAcceleration() const;
      const math::Vector2<float>& getVelocity() const;

      virtual void setPosition(float x, float y);
      virtual void setPosition(const math::Vector2<float>& position);
      virtual void setRect(const math::Rect<float>& rect);
      virtual void setRectTop(float y);
      virtual void setRectBottom(float y);
      virtual void setRectLeft(float x);
      virtual void setRectRight(float x);
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