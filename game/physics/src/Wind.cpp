#include "../inc/Wind.hpp"

namespace jp::game::physics
{
   Wind::Wind() {}
   
   Wind::Wind(float impact, const math::Vector2<float>& maxVelocity,
      const math::Rect<float>& rect, const math::Vector2<float>& acceleration,
      const math::Vector2<float>& velocity/* = 0.f*/)
      : mImpact(impact), mMaxVelocity(maxVelocity),
      Entity(rect, acceleration, velocity) {}

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