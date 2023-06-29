#pragma once

#include <SFML/Graphics.hpp>

#include "../../Common/inc/Updatable.h"

namespace jp::game
{
   
   class CollisionRect : public Updatable
   {
   public:
      virtual void update(sf::Time& dt);
      
      sf::Vector2f getPosition() const;
      void setPosition(const sf::Vector2f& position);

   private:
      sf::FloatRect mRect;
      sf::Vector2f mSpeed;
      sf::Vector2f mAcceleration;
   };

}