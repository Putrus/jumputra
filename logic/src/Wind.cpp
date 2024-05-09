#include "../inc/Wind.hpp"

#include "../../math/inc/Math.hpp"

namespace jp::logic
{
   Wind::Wind(float impact, const math::Vector2<float>& maxVelocity,
      const math::Rect<float>& rect, const math::Vector2<float>& acceleration,
      const math::Vector2<float>& velocity/* = 0.f*/)
      : mImpact(impact), mMaxVelocity(maxVelocity),
      Entity(rect, acceleration, velocity) {}

   Wind::Wind(const nlohmann::json& json) : Entity(json) {}
   
   std::shared_ptr<Wind> Wind::create(float impact, const math::Vector2<float>& maxVelocity,
      const math::Rect<float>& rect, const math::Vector2<float>& acceleration,
      const math::Vector2<float>& velocity/* = 0.f*/)
   {
      return std::make_shared<Wind>(impact, maxVelocity, rect, acceleration, velocity);
   }
   
   void Wind::update(float dt)
   {
      setVelocity(getVelocity() + getAcceleration() * dt);
      math::Vector2<float> absVelocity =
          math::Vector2<float>(math::abs(getVelocity()));
      math::Vector2<float> absMaxVelocity = 
         math::Vector2<float>(math::abs(getMaxVelocity()));

      if (absVelocity.x > absMaxVelocity.x)
      {
         setVelocityX(getMaxVelocity().x);
      }

      if (absVelocity.y > absMaxVelocity.y)
      {
         setVelocityY(getMaxVelocity().y);
      }

      if (getVelocity() == getMaxVelocity())
      {
         setMaxVelocity(getMaxVelocity() * -1);
         setAcceleration(getAcceleration() * -1);
      }
   }

   void Wind::fromJson(const nlohmann::json& json)
   {
      mImpact = json["impact"];
      mMaxVelocity = json["maxVelocity"];
      Entity::fromJson(json);
   }

   nlohmann::json Wind::toJson() const
   {
      nlohmann::json json;


      return json;
   }

   float Wind::getImpact() const
   {
      return mImpact;
   }

   const math::Vector2<float>& Wind::getMaxVelocity() const
   {
      return mMaxVelocity;
   }

   void Wind::setMaxVelocity(const math::Vector2<float>& maxVelocity)
   {
      mMaxVelocity = maxVelocity;
   }
}