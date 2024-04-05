#include "../inc/Character.hpp"

#include "../../math/inc/Math.hpp"

namespace jp::logic
{
   std::ostream& operator<<(std::ostream& os, CharacterState state)
   {
      switch (state)
      {
         case CharacterState::Burying:
         os << "Burying";
         break;
         case CharacterState::Dying:
         os << "Dying";
         break;
         case CharacterState::Falling:
         os << "Falling";
         break;
         case CharacterState::Flying:
         os << "Flying";
         break;
         case CharacterState::Lying:
         os << "Lying";
         break;
         case CharacterState::Running:
         os << "Running";
         break;
         case CharacterState::Sledding:
         os << "Sledding";
         break;
         case CharacterState::Sliding:
         os << "Sliding";
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
      if (mState == CharacterState::Squatting)
      {
         mJumpPower += mProperties.character.jump.gain * dt;
         if (mJumpPower.y >= mProperties.character.jump.gain.y)
         {
            jump();
         }
      }

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

      math::Vector2<float> newAcceleration = 0.f;

      math::Vector2<float> newVelocity = mVelocity +
         resultantAcceleration * dt;
      
      if (newVelocity.x < 5.f && newVelocity.x > -5.f)
      {
         newVelocity.x = 0.f;
      }

      float newRunSpeed = 0.f;

      //flying is default state
      CharacterState newState = CharacterState::Flying;
      if (newVelocity.y >= mProperties.physics.fallSpeed)
      {
         newVelocity.y = mProperties.physics.fallSpeed;
         newState = CharacterState::Falling;
      }

      //distance/spatium traveled
      math::Vector2<float> distance = (newVelocity + mVelocity +
         math::Vector2<float>(2 * mRunSpeed, 0.f)) * dt / 2.f;
      math::Rect<float> newRect = mRect;
      newRect.setPosition(newRect.getPosition() + distance);
      
      math::Rect<float> oldRect = mRect;
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
               newVelocity.x = getVelocity().x * -mProperties.physics.bounceFactor;
               if (math::sign(newVelocity.x) == math::sign(getRunSpeed()))
               {
                  newVelocity.x = 0.f;
               }
               break;
            }
            case SegmentCollision::Right:
            {
               newRect.left = segment->a.x - newRect.width;
               newVelocity.x = getVelocity().x * -mProperties.physics.bounceFactor;
               if (math::sign(newVelocity.x) == math::sign(getRunSpeed()))
               {
                  newVelocity.x = 0.f;
               }
               break;
            }
            case SegmentCollision::Top:
            {
               newRect.top = segment->b.y;
               newVelocity.x = getVelocity().x * mProperties.physics.bounceFactor;
               newVelocity.y = 0.f;
               break;
            }
            case SegmentCollision::Bottom:
            {
               newRect.top = segment->a.y - newRect.height;
               newVelocity.y = 0.f;
               if (segment->getSurface() == SegmentSurface::Ordinary)
               {
                  if (getState() != CharacterState::Running)
                  {
                     newVelocity.x = 0;
                  }
                  else
                  {
                     newRunSpeed = getRunSpeed();
                  }

                  switch (getState())
                  {
                     case CharacterState::Running:
                        if (getDirection() == CharacterDirection::Up)
                        {
                           newState = CharacterState::Standing;
                           break;
                        }
                     case CharacterState::Lying:
                     case CharacterState::Squatting:
                        newState = getState();
                        break;
                     case CharacterState::Falling:
                        newState = CharacterState::Lying;
                        break;
                     default:
                        newState = CharacterState::Standing;
                        break;
                  }
               }
               else if (segment->getSurface() == SegmentSurface::Sticky)
               {
                  newVelocity.x = 0.f;
                  switch (getState())
                  {
                     case CharacterState::Burying:
                     case CharacterState::Squatting:
                        newState = getState();
                        break;
                     case CharacterState::Falling:
                        newState = CharacterState::Burying;
                        break;
                     default:
                        newState = CharacterState::Sticking;
                        break;
                  }
               }
               else 
               {
                  newAcceleration.x = mProperties.physics.slipperyFriction * -math::sign(getVelocity().x);

                  if (getVelocity().x == 0.f)
                  {
                     newAcceleration.x = 0.f;
                  }

                  switch (getState())
                  {
                     case CharacterState::Running:
                        if (getDirection() == CharacterDirection::Up)
                        {
                           newState = CharacterState::Sliding;
                           break;
                        }
                        newRunSpeed = getRunSpeed();
                     case CharacterState::Dying:
                     case CharacterState::Squatting:
                        newState = getState();
                        break;
                     case CharacterState::Falling:
                        newState = CharacterState::Dying;
                        break;
                     default:
                        newState = CharacterState::Sliding;
                        break;
                  }
               } 
               break;
            }
            case SegmentCollision::Attic:
            {
               newVelocity = 0.f;
               float slope = segment->getSlope();
               float intercept = segment->getIntercept();
               if (slope < 0)
               {
                  if (newRect.left < segment->a.x)
                  {
                     newRect.top = segment->a.y;
                  }
                  else
                  {
                     newRect.top = newRect.left * slope + intercept;
                  }
               }
               else
               {
                  if (newRect.getRight() > segment->b.x)
                  {
                     newRect.top = segment->b.y;
                  }
                  else
                  {
                     newRect.top = newRect.getRight() * slope + intercept;
                  }
               }
               break;
            }
            default:
               break;
         }
      }

      if (getState() == CharacterState::Running &&
         newState == CharacterState::Flying)
      {
         newVelocity.x += getRunSpeed();
      }

      setAcceleration(newAcceleration);
      setVelocity(newVelocity);
      setRunSpeed(newRunSpeed);
      setRect(newRect);
      setState(newState);
   }

   void Character::jump()
   {
      if (getState() == CharacterState::Squatting)
      {
         setState(CharacterState::Flying);
         setAccelerationX(0.f);
         switch (mDirection)
         {
         case CharacterDirection::Up:
         {
            setVelocityY(-std::min(mProperties.character.jump.max.y, mJumpPower.y));
            break;
            }
            case CharacterDirection::Left:
            {
               setVelocity(math::Vector2<float>(getVelocity().x - mProperties.character.jump.max.x,
                  -std::min(mProperties.character.jump.max.y, mJumpPower.y)));
               break;
            }
            case CharacterDirection::Right:
            {
               setVelocity(math::Vector2<float>(getVelocity().x + mProperties.character.jump.max.x,
                  -std::min(mProperties.character.jump.max.y, mJumpPower.y)));
               break;
            }
            default:
               break;
         }
         resetJumpPower();
      }
   }

   void Character::run(CharacterDirection direction)
    {
      setDirection(direction);
      if (canRun() && direction != CharacterDirection::Up)
      {
         setState(CharacterState::Running);
         float directionSign = direction == CharacterDirection::Left ? -1.f : 1.f;
         if (math::sign(getRunSpeed()) != directionSign)
         {
            setVelocityX(getVelocity().x + getRunSpeed());
            setRunSpeed(directionSign * mProperties.character.runSpeed);
            if (math::sign(getVelocity().x) == math::sign(getRunSpeed()))
            {
               setAccelerationX(0.f);
               setVelocityX(0.f);
            }
         }
         else
         {
            setVelocityX(0.f);
            setRunSpeed(directionSign * mProperties.character.runSpeed);
         }
      }
    }

   void Character::squat()
   {
      if (canSquat())
      {
         if (getState() == CharacterState::Running)
         {
            setVelocityX(getVelocity().x + mRunSpeed);
            setRunSpeed(0.f);
         }
         setState(CharacterState::Squatting);
      }
   }

   void Character::stop()
   {
      setDirection(CharacterDirection::Up);
      if (getState() == CharacterState::Running)
      {
         setVelocityX(getVelocity().x + mRunSpeed);
         setRunSpeed(0.f);
      }
   }

   void Character::resetJumpPower()
   {
      mJumpPower = 0.f;
   }

   bool Character::canRun() const
   {
      return getState() == CharacterState::Dying ||
         getState() == CharacterState::Lying ||
         getState() == CharacterState::Running ||
         getState() == CharacterState::Sliding ||
         getState() == CharacterState::Standing ||
         getState() == CharacterState::Stopping;
   }

   bool Character::canSquat() const
   {
      return canRun() ||
         getState() == CharacterState::Burying ||
         getState() == CharacterState::Sticking;
   }

   CharacterDirection Character::getDirection() const
   {
      return mDirection;
   }

   float Character::getRunSpeed() const
   {
      return mRunSpeed;
   }

   CharacterState Character::getState() const
   {
      return mState;
   }

   void Character::setDirection(CharacterDirection direction)
   {
      mDirection = direction;
   }

   void Character::setRunSpeed(float speed)
   {
      mRunSpeed = speed;
   }

   void Character::setState(CharacterState state)
   {
      if (state != getState())
      {
         std::cout << getState() << " -> " << state << std::endl;
      }
      mState = state;
   }
}