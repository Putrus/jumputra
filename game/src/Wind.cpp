#include "../inc/Wind.hpp"

namespace jp::game
{
   Wind::Wind(float impact, const math::Vector2<float>& maxVelocity,
      const math::Rect<float>& rect, const math::Vector2<float>& acceleration,
      const math::Vector2<float>& velocity/* = 0.f*/)
      : graphic::Wind(sf::FloatRect(sf::Vector2f(rect.left, rect.top), sf::Vector2f(rect.width, rect.height))),
         logic::Wind(impact, maxVelocity, rect, acceleration, velocity) {}
   
   void Wind::update(float dt)
   {
      graphic::Wind::move(sf::Vector2f(mVelocity.x * dt, mVelocity.y * dt));
      logic::Wind::update(dt);
   }

   std::shared_ptr<Wind> Wind::create(float impact, const math::Vector2<float>& maxVelocity,
      const math::Rect<float>& rect, const math::Vector2<float>& acceleration,
      const math::Vector2<float>& velocity/* = 0.f*/)
   {
      return std::make_shared<Wind>(impact, maxVelocity, rect, acceleration, velocity);
   }
}