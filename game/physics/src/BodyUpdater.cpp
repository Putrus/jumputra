#include "../inc/BodyUpdater.hpp"

namespace jp::game::physics
{
   void BodyUpdater::update(float dt, Body& body,
      const Properties& properties,
      const std::vector<std::shared_ptr<Segment>>& segments,
      const std::vector<std::shared_ptr<Wind>>& winds) const
   {
      //sum of winds velocities * impacts
      math::Vector2<float> windAcceleration = 0.f;
      for (const auto& wind : winds)
      {
         if (body.getRect().intersects(wind->getRect()))
         {
            windAcceleration += wind->getVelocity() * wind->getImpact();
         }
      }

      math::Vector2<float> resultantAcceleration = body.getAcceleration() +
         properties.gravity + windAcceleration;

      math::Vector2<float> newVelocity = body.getVelocity() +
         resultantAcceleration * dt;
      
      //flying is default state
      BodyState newState = BodyState::Flying;
      if (newVelocity.y >= properties.fallVelocity)
      {
         newVelocity.y = properties.fallVelocity;
         newState = BodyState::Falling;
      }

      //distance/spatium traveled
      math::Vector2<float> distance = (newVelocity + body.getVelocity()) * dt / 2.f;
      math::Rect<float> newRect = body.getRect();
      newRect.setPosition(newRect.getPosition() + distance);
      
      const math::Rect<float>& oldRect = body.getRect();
      for (const auto& segment : segments)
      {
         SegmentCollision segmentCollision = segment->checkCollision(oldRect, newRect);
         switch (segmentCollision)
         {
            case SegmentCollision::No:
            break;
            case SegmentCollision::Left:
            {
               newRect.left = segment->b.x;
               newVelocity.x *= -properties.bounceFactor;
               break;
            }
            case SegmentCollision::Right:
            {
               newRect.left = segment->a.x - newRect.width;
               newVelocity.x *= -properties.bounceFactor;
               break;
            }
            case SegmentCollision::Top:
            {
               newRect.top = segment->a.y;
               newVelocity.x *= properties.bounceFactor;
               newVelocity.y = 0.f;  
               break;
            }
            case SegmentCollision::Bottom:
            {
               newRect.top = segment->a.y - newRect.height;
               newVelocity.x = 0.f;
               newState = BodyState::Standing;
               break;
            }
            default:
            break;
         }
      }

      body.setVelocity(newVelocity);
      body.setRect(newRect);
      body.setState(newState);
   }
}