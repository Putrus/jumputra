#pragma once

#include "CharacterSprite.h"

#include "../../Physics/inc/DynamicObject.h"

#include "../../../Common/inc/Context.h"
#include "../../../Common/inc/Updatable.h"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class Character : public sf::Drawable
   {
   public:
      Character(const std::string& name, const Context& context);

      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
      void update(const sf::Time& dt, const std::vector<physics::StaticObject>& objects);

      void jump(const sf::Vector2f& velocity);
      void go(bool right);
      void stop();

      void setScale(float factorX, float factorY);

   private:
      physics::DynamicObject mObject;
      CharacterSprite mSprite;
      sf::Vector2f mCollisionOffset;
   };
}