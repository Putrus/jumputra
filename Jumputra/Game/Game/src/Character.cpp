#include "../inc/Character.h"

#include <json/json.h>
#include <json/json-forwards.h>

#include <iostream>
#include <fstream>

namespace jp::game
{
   Character::Character(const std::string& name, const Context& context)
   {
      mSprite.setTexture(context.resources.getTexture(name));
      std::ifstream file(CHARACTERS_JSON);
      if (file.is_open())
      {
         Json::Value characters;
         file >> characters;
         for (const auto& character : characters)
         {
            if (character["name"] == name)
            {
               mFrameSize.x = character["frameSize"]["width"].asInt();
               mFrameSize.y = character["frameSize"]["height"].asInt();
               mSprite.setTextureRect(sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y));
               mCollisionOffset.x = character["collisionRect"]["left"].asFloat();
               mCollisionOffset.y = character["collisionRect"]["top"].asFloat();
               mObject = physics::DynamicObject(sf::FloatRect(0.f, 0.f,
                  character["collisionRect"]["width"].asFloat(),
                  character["collisionRect"]["height"].asFloat()));
            }
         }
         file.close();
      }
      setScale(3.f, 3.f);
   }
   void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(mSprite);
   }

   void Character::update(const sf::Time& dt, const std::vector<physics::StaticObject>& objects)
   {
      mObject.update(dt, objects);
      mSprite.setPosition(mObject.getPosition() - mCollisionOffset);
   }

   void Character::jump(const sf::Vector2f& velocity)
   {
   
   }

   void Character::setScale(float factorX, float factorY)
   {
      mSprite.setScale(factorX, factorY);
      mObject.setSize(sf::Vector2f(mObject.getSize().x * factorX, mObject.getSize().y * factorY));
      mCollisionOffset.x *= factorX;
      mCollisionOffset.y *= factorY;
   }
}