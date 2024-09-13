#include "../inc/Wind.hpp"

#include "../../math/inc/Math.hpp"

namespace jp::logic
{
   Wind::Wind(float impact, const math::Vector2<float>& maxVelocity,
      const math::Rect<float>& rect, const math::Vector2<float>& acceleration,
      const math::Vector2<float>& velocity/* = 0.f*/)
      : mImpact(impact), mMaxVelocity(maxVelocity),
      Entity(rect, acceleration, velocity) {}

   Wind::Wind(const nlohmann::json& json)
   {
      fromJson(json);
   }

   Wind& Wind::operator=(const Wind& other)
   {
      if (this != &other)
      {
         mImpact = other.mImpact;
         mMaxVelocity = other.mMaxVelocity;
         mRect = other.mRect;
         mAcceleration = other.mAcceleration;
         mVelocity = other.mVelocity;
      }
      return *this;
   }
   
   std::shared_ptr<Wind> Wind::create(const nlohmann::json& json)
   {
      return std::make_shared<Wind>(json);
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
      mImpact = json.at("impact");
      mMaxVelocity = json.at("maxVelocity");
      Entity::fromJson(json);
   }

   nlohmann::json Wind::toJson() const
   {
      nlohmann::json json = Entity::toJson();
      json["impact"] = mImpact;
      json["maxVelocity"] = mMaxVelocity.toJson();
      return json;
   }

   void Wind::reset()
   {
      mMaxVelocity = math::abs(mMaxVelocity);
      mAcceleration = math::abs(mAcceleration);
      mVelocity = math::Vector2<float>();
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