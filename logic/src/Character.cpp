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
         default:
         os << "Unknown";
         break;
      }
      return os;
   }

      std::ostream& operator<<(std::ostream& os, CharacterDirection direction)
   {
      switch (direction)
      {
         case CharacterDirection::Up:
         os << "Up";
         break;
         case CharacterDirection::Left:
         os << "Left";
         break;
         case CharacterDirection::Right:
         os << "Right";
         break;
         default:
         os << "Unknown";
         break;
      }
      return os;
   }

   Character::Character(const math::Vector2<float> &position, const math::Vector2<float> &size,
      const Properties &properties,
      Statistics& totalStatistics,
      const std::vector<std::shared_ptr<Segment>>& segments,
      const std::vector<std::shared_ptr<Wind>>& winds)
      : mProperties(properties), mTotalStatistics(totalStatistics), mSegments(segments),
      mWinds(winds), Entity(math::Rect<float>(position, size)) {}

   Character::Character(const math::Rect<float>& rect,
      const Properties &properties,
      Statistics& totalStatistics,
      const std::vector<std::shared_ptr<Segment>>& segments,
      const std::vector<std::shared_ptr<Wind>>& winds)
      : mProperties(properties), mTotalStatistics(totalStatistics), mSegments(segments), mWinds(winds), Entity(rect) {}

   Character::Character(const nlohmann::json& json,
      const Properties& properties,
      Statistics& totalStatistics,
      const std::vector<std::shared_ptr<Segment>>& segments,
      const std::vector<std::shared_ptr<Wind>>& winds)
      : mProperties(properties), mTotalStatistics(totalStatistics), mSegments(segments), mWinds(winds)
   {
      fromJson(json);
   }

   Character::Character(const Character& other) : mState(other.mState), mDirection(other.mDirection),
      mJumpPower(other.mJumpPower), mGravity(other.mGravity), mRunSpeed(other.mRunSpeed),
      mProperties(other.mProperties), mTotalStatistics(other.mTotalStatistics),
      mSegments(other.mSegments), mWinds(other.mWinds), Entity(other) {}
   
   Character& Character::operator=(const Character& other)
   {
      if (this != &other)
      {
         mState = other.mState;
         mDirection = other.mDirection;
         mJumpPower = other.mJumpPower;
         mGravity = other.mGravity;
         mVisitedSegments = other.mVisitedSegments;
         mRunSpeed = other.mRunSpeed;
         mRect = other.mRect;
         mAcceleration = other.mAcceleration;
         mVelocity = other.mVelocity;
      }
      return *this;
   }

   std::shared_ptr<Character> Character::create(const nlohmann::json& json,
      const Properties& properties,
      Statistics& totalStatistics,
      const std::vector<std::shared_ptr<Segment>>& segments,
      const std::vector<std::shared_ptr<Wind>>& winds)
   {
      return std::make_shared<Character>(json, properties, totalStatistics, segments, winds);
   }

   CharacterDirection Character::oppositeDirection(CharacterDirection direction)
   {
      if (direction == CharacterDirection::Left)
      {
         return CharacterDirection::Right;
      }
      else if (direction == CharacterDirection::Right)
      {
         return CharacterDirection::Left;
      }
      else
      {
         return CharacterDirection::Up;
      }
   }

   void Character::update(float dt)
   {
      if (getState() != CharacterState::Sledding)
      {
         mGravity = mProperties.physics.gravity;
      }

      if (getState() == CharacterState::Squatting)
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
         mGravity + windAcceleration;

      math::Vector2<float> newAcceleration = 0.f;

      math::Vector2<float> newVelocity = mVelocity +
         resultantAcceleration * dt;
      
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
         if (std::max(segment->a.y, segment->b.y) < newRect.top - mProperties.physics.checkCollisionDistance ||
            std::min(segment->a.y, segment->b.y) > newRect.getBottom() + mProperties.physics.checkCollisionDistance)
         {
            continue;
         }
         
         SegmentCollision segmentCollision = segment->checkCollision(oldRect, newRect);
         switch (segmentCollision)
         {
            case SegmentCollision::No:
               break;
            case SegmentCollision::Left:
            {
               if (getState() == CharacterState::Sledding)
               {
                  break;
               }
               newRect.left = segment->b.x;
               if (newVelocity.x < 0.f)
               {
                  newVelocity.x = getVelocity().x * -mProperties.physics.bounceFactor;
               }
               if (math::sign(newVelocity.x) == math::sign(getRunSpeed()))
               {
                  newVelocity.x = 0.f;
               }
               break;
            }
            case SegmentCollision::Right:
            {
               if (getState() == CharacterState::Sledding)
               {
                  break;
               }
               newRect.left = segment->a.x - newRect.width;
               if (newVelocity.x > 0.f)
               {
                  newVelocity.x = getVelocity().x * -mProperties.physics.bounceFactor;
               }
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
               if (getState() == CharacterState::Sledding)
               {
                  break;
               }
               newRect.top = std::min(segment->a.y, segment->b.y) - newRect.height;
               newVelocity.y = 0.f;
               if (mVisitedSegments.empty() || segment != mVisitedSegments.back())
               {
                  mVisitedSegments.push_back(segment);
               }

               if (segment->getSurface() == SegmentSurface::Ordinary)
               {
                  newRunSpeed = getRunSpeed();
                  newVelocity.x = 0.f;

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
                  newRect.left = oldRect.left;
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

                  if (getVelocity().x < 5.f && getVelocity().x > -5.f)
                  {
                     newAcceleration.x = 0.f;
                     newVelocity.x = 0.f;
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
               newRect.left = getRect().left;
               break;
            }
            case SegmentCollision::Roof:
            {
               float slope = segment->getSlope();
               float intercept = segment->getIntercept();
               if (slope < 0)
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
               else
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
               
               if (getState() != CharacterState::Sledding)
               {
                  mGravity.x = mProperties.physics.gravity.y * slope / 1.41f; 
                  mGravity.y = mProperties.physics.gravity.y / 1.41f;
                  newVelocity.x /= 1.41f;
                  newVelocity.y /= 1.41f;
               }
               newRect.top -= newRect.height;
               newState = CharacterState::Sledding;
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

      if (getState() == CharacterState::Falling && newState != getState())
      {
         ++mStatistics.falls;
         ++mTotalStatistics.falls;
      }

      mStatistics.time += dt;
      mTotalStatistics.totalTime += dt;

      setAcceleration(newAcceleration);
      setVelocity(newVelocity);
      setRunSpeed(newRunSpeed);
      setRect(newRect);
      setState(newState);
   }

   void Character::fromJson(const nlohmann::json& json)
   {
      mState = static_cast<CharacterState>(json.at("state"));
      mDirection = static_cast<CharacterDirection>(json.at("direction"));
      mJumpPower = json.at("jumpPower");
      mGravity = json.at("gravity");
      mRunSpeed = json.at("runSpeed");
      mStatistics = json.at("statistics");
      Entity::fromJson(json);
   }

   nlohmann::json Character::toJson() const
   {
      nlohmann::json json = Entity::toJson();
      json["state"] = static_cast<unsigned long long>(mState);
      json["direction"] = static_cast<unsigned long long>(mDirection);
      json["jumpPower"] = mJumpPower.toJson();
      json["gravity"] = mGravity.toJson();
      json["runSpeed"] = mRunSpeed;
      json["statistics"] = mStatistics.toJson();
      return json;
   }

   void Character::jump()
   {
      if (getState() == CharacterState::Squatting)
      {
         ++mStatistics.jumps;
         ++mTotalStatistics.jumps;
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

   void Character::setDirection(CharacterDirection direction)
   {
      mDirection = direction;
   }

   void Character::setRunSpeed(float speed)
   {
      mRunSpeed = speed;
   }

   float Character::getRunSpeed() const
   {
      return mRunSpeed;
   }

   CharacterDirection Character::getDirection() const
   {
      return mDirection;
   }

   CharacterState Character::getState() const
   {
      return mState;
   }

   Statistics Character::getStatistics() const
   {
      return mStatistics;
   }

   const std::vector<std::shared_ptr<logic::Segment>>& Character::getVisitedSegments() const
   {
      return mVisitedSegments;
   }

   const math::Vector2<float>& Character::getJumpPower() const
   {
      return mJumpPower;
   }

   const Properties& Character::getProperties() const
   {
      return mProperties;
   }

   bool Character::canRun() const
   {
      return getState() == CharacterState::Dying ||
         getState() == CharacterState::Lying ||
         getState() == CharacterState::Running ||
         getState() == CharacterState::Sliding ||
         getState() == CharacterState::Standing;
   }

   bool Character::canSquat() const
   {
      return canRun() ||
         isSticked();
   }

   bool Character::isSticked() const
   {
      return getState() == CharacterState::Burying ||
         getState() == CharacterState::Sticking;
   }

   void Character::setState(CharacterState state)
   {
      mState = state;
   }

   void Character::resetJumpPower()
   {
      mJumpPower = 0.f;
   }
}