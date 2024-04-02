#include "../inc/Character.hpp"

namespace jp::logic
{
   std::ostream& operator<<(std::ostream& os, CharacterState state)
   {
      switch (state)
      {
         case CharacterState::Dying:
         os << "Dying";
         break;
         case CharacterState::Falling:
         os << "Falling";
         break;
         case CharacterState::Flying:
         os << "Flying";
         break;
         case CharacterState::Running:
         os << "Running";
         break;
         case CharacterState::Sledding:
         os << "Sledding";
         break;
         case CharacterState::Squatting:
         os << "Squatting";
         break;
         case CharacterState::Standing:
         os << "Standing";
         break;
         case CharacterState::Sticking:
         os << "Sticking";
         break;
         case CharacterState::Stopping:
         os << "Stopping";
         break;
         default:
         os << "Unknown";
         break;
      }
      return os;
   }

   Character::Character(const math::Vector2<float> &position, const math::Vector2<float> &size,
      const Properties &properties,
      const std::vector<std::shared_ptr<Segment>>& segments,
      const std::vector<std::shared_ptr<Wind>>& winds)
      : mProperties(properties), mSegments(segments), mWinds(winds), Entity(math::Rect<float>(position, size)) {}

   Character::Character(const math::Rect<float>& rect,
      const Properties &properties,
      const std::vector<std::shared_ptr<Segment>>& segments,
      const std::vector<std::shared_ptr<Wind>>& winds)
      : mProperties(properties), mSegments(segments), mWinds(winds), Entity(rect) {}

   void Character::update(float dt)
   {
      //sum of winds velocities * impacts
      math::Vector2<float> windAcceleration = 0.f;
      for (const auto& wind : mWinds)
      {
         if (mRect.intersects(wind->getRect()))
         {
            windAcceleration += wind->getVelocity() * wind->getImpact();
         }
      }

      math::Vector2<float> resultantAcceleration = mAcceleration +
         mProperties.physics.gravity + windAcceleration;

      math::Vector2<float> newVelocity = mVelocity +
         resultantAcceleration * dt;
      
      //flying is default state
      CharacterState newState = CharacterState::Flying;
      if (newVelocity.y >= mProperties.physics.fallSpeed)
      {
         newVelocity.y = mProperties.physics.fallSpeed;
         newState = CharacterState::Falling;
      }

      //distance/spatium traveled
      math::Vector2<float> distance = (newVelocity + mVelocity) * dt / 2.f;
      math::Rect<float> newRect = mRect;
      newRect.setPosition(newRect.getPosition() + distance);
      
      const math::Rect<float>& oldRect = mRect;
      for (const auto& segment : mSegments)
      {
         SegmentCollision segmentCollision = segment->checkCollision(oldRect, newRect);
         switch (segmentCollision)
         {
            case SegmentCollision::No:
            break;
            case SegmentCollision::Left:
            {
               newRect.left = segment->b.x;
               newVelocity.x *= -mProperties.physics.bounceFactor;
               break;
            }
            case SegmentCollision::Right:
            {
               newRect.left = segment->a.x - newRect.width;
               newVelocity.x *= -mProperties.physics.bounceFactor;
               break;
            }
            case SegmentCollision::Top:
            {
               newRect.top = segment->a.y;
               newVelocity.x *= mProperties.physics.bounceFactor;
               newVelocity.y = 0.f;  
               break;
            }
            case SegmentCollision::Bottom:
            {
               newRect.top = segment->a.y - newRect.height;
               newVelocity.x = 0.f;
               newState = CharacterState::Standing;
               break;
            }
            default:
            break;
         }
      }

      setVelocity(newVelocity);
      setRect(newRect);
      setState(newState);
   }

   CharacterState Character::getState() const
   {
      return mState;
   }

   void Character::setState(CharacterState state)
   {
      mState = state;
   }  
}