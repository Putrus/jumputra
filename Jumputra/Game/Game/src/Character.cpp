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
               mSprite.setTextureRect(sf::IntRect(0, 0, character["frameSize"]["width"].asInt(),
                  character["frameSize"]["height"].asInt()));
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
      if (mObject.isInAir())
      {
         mSprite.setAnimation(CharacterAnimation::FlySide);
         if (mObject.getVelocity().y > 0)
         {
            mSprite.setCurrentFrame(1);
         }
         else
         {
            mSprite.setCurrentFrame(0);
         }
      }
      else if (mSprite.getAnimation() == CharacterAnimation::FlySide)
      {
         mSprite.setAnimation(CharacterAnimation::IdleSide);
      }
      mSprite.update(dt, mObject.getPosition() - mCollisionOffset);
   }

   void Character::jump(const sf::Vector2f& velocity)
   {
      if (!mObject.isInAir())
      {
         //jump
         mObject.setVelocity(velocity);
      }
   }

   void Character::go(bool right)
   {
      if (!mObject.isInAir())
      {
         CharacterSide side = mSprite.getSide();
         if (right)
         {
            mSprite.setSide(CharacterSide::Right);
            if (side == CharacterSide::Left)
            {
               mSprite.setAnimation(CharacterAnimation::TurnFront, 0);
            }
            else if (side == CharacterSide::Front)
            {
               mSprite.setAnimation(CharacterAnimation::TurnSide, 0);
            }
            else if (side == CharacterSide::Right)
            {
               mSprite.setAnimation(CharacterAnimation::RunSide);
               mObject.setVelocity(sf::Vector2f(VELOCITY_X, 0.f));
            }
            //go right
         }
         else
         {
            mSprite.setSide(CharacterSide::Left);
            //go left
            if (side == CharacterSide::Right)
            {
               mSprite.setAnimation(CharacterAnimation::TurnFront, 0);
            }
            else if (side == CharacterSide::Front)
            {
               mSprite.setAnimation(CharacterAnimation::TurnSide, 0);
            }
            else if (side == CharacterSide::Left)
            {
               mSprite.setAnimation(CharacterAnimation::RunSide);
               mObject.setVelocity(sf::Vector2f(-VELOCITY_X, 0.f));
            }
         }
      }
   }

   void Character::readyForJump()
   {
      if (mSprite.getAnimation() != CharacterAnimation::JumpSide)
      {
         mSprite.setAnimation(CharacterAnimation::JumpSide, 0);
      }
   }

   void Character::stop()
   {
      if (!mObject.isInAir())
      {
         //stop running
         CharacterSide side = mSprite.getSide();
         mObject.setVelocity(sf::Vector2f(0.f, 0.f));
         if (side == CharacterSide::Left || side == CharacterSide::Right)
         {
            mSprite.setAnimation(CharacterAnimation::IdleSide);
         }
      }
   }

   void Character::setScale(float factorX, float factorY)
   {
      mSprite.setScale(factorX, factorY);
      mObject.setSize(sf::Vector2f(mObject.getSize().x * factorX, mObject.getSize().y * factorY));
      mCollisionOffset.x *= factorX;
      mCollisionOffset.y *= factorY;
   }
}