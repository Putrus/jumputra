#include "../inc/WindUpdater.hpp"

#include "../../../math/inc/Math.hpp"

namespace jp::game::physics
{
   void WindUpdater::update(float dt, Wind& wind) const
   {   
      wind.setVelocity(wind.getVelocity() + wind.getAcceleration() * dt);
      math::Vector2<float> absVelocity =
          math::Vector2<float>(math::abs(wind.getVelocity()));
      math::Vector2<float> absMaxVelocity = 
         math::Vector2<float>(math::abs(wind.getMaxVelocity()));

      if (absVelocity.x > absMaxVelocity.x)
      {
         wind.setVelocityX(wind.getMaxVelocity().x);
      }

      if (absVelocity.y > absMaxVelocity.y)
      {
         wind.setVelocityY(wind.getMaxVelocity().y);
      }

      if (wind.getVelocity() == wind.getMaxVelocity())
      {
         wind.setMaxVelocity(wind.getMaxVelocity() * -1);
         wind.setAcceleration(wind.getAcceleration() * -1);
      }
   }
}