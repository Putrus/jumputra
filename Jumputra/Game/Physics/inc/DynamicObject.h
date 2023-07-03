#pragma once

#include "StaticObject.h"

#include "../../../Common/inc/Constant.h"

#include <vector>

namespace jp::game::physics
{
   class DynamicObject : public StaticObject
   {
   public:
      DynamicObject();
      DynamicObject(const sf::FloatRect& rect,
         const sf::Vector2f& velocity = sf::Vector2f(0.f, 0.f), const sf::Vector2f& acceleration = sf::Vector2f(0.f, GRAVITY));
      DynamicObject(const sf::Vector2f& position, const sf::Vector2f& size,
         const sf::Vector2f& velocity = sf::Vector2f(0.f, 0.f), const sf::Vector2f& acceleration = sf::Vector2f(0.f, GRAVITY));

      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

      void update(const sf::Time& dt, const std::vector<StaticObject>& objects);

      sf::Vector2f getVelocity() const;
      sf::Vector2f getAcceleration() const;
      bool isInAir() const;

      void setVelocity(const sf::Vector2f& velocity);
      void setAcceleration(const sf::Vector2f& acceleration);

   private:
      bool checkCollision(sf::FloatRect& newRect, const StaticObject& object);

      sf::Vector2f mVelocity;
      sf::Vector2f mAcceleration;
      bool inAir = false;
   };

}