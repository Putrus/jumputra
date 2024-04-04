#include "../inc/Wind.hpp"

namespace jp::game
{
   Wind::Wind(float impact, const math::Vector2<float>& maxVelocity,
      const math::Rect<float>& rect, const math::Vector2<float>& acceleration,
      const math::Vector2<float>& velocity/* = 0.f*/)
      : logic::Wind(impact, maxVelocity, rect, acceleration, velocity) {}
   
   std::shared_ptr<Wind> Wind::create(float impact, const math::Vector2<float>& maxVelocity,
      const math::Rect<float>& rect, const math::Vector2<float>& acceleration,
      const math::Vector2<float>& velocity/* = 0.f*/)
   {
      return std::make_shared<Wind>(impact, maxVelocity, rect, acceleration, velocity);
   }
}