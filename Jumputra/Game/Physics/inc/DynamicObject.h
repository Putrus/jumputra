#pragma once

#include "StaticObject.h"

#include <vector>

namespace jp::game::physics
{
   class DynamicObject : public StaticObject
   {
   public:
      DynamicObject();
      DynamicObject(const sf::FloatRect& rect,
         const sf::Vector2f& velocity = sf::Vector2f(0.f, 0.f), const sf::Vector2f& acceleration = sf::Vector2f(0.f, 0.f));
      DynamicObject(const sf::Vector2f& position, const sf::Vector2f& size,
         const sf::Vector2f& velocity = sf::Vector2f(0.f, 0.f), const sf::Vector2f& acceleration = sf::Vector2f(0.f, 0.f));

      bool update(const sf::Time& dt, const std::vector<StaticObject>& objects);

      sf::Vector2f getVelocity() const;
      sf::Vector2f getAcceleration() const;

      void setVelocity(const sf::Vector2f& velocity);
      void setAcceleration(const sf::Vector2f& acceleration);

   private:
      sf::Vector2f mVelocity;
      sf::Vector2f mAcceleration;
   };

}