#pragma once

#include "StaticObject.h"

#include <vector>

namespace jp::game::physics
{
   class DynamicObject : public StaticObject
   {
   public:
      bool update(const sf::Time& dt, const std::vector<StaticObject>& objects);

   private:
      sf::Vector2f mVelocity;
      sf::Vector2f mAcceleration;
   };

}