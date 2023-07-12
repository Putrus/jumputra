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
   }

   void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(mSprite);
   }

   void Character::update(const sf::Time& dt, const std::vector<physics::StaticObject>& objects)
   {
      mObject.update(dt, objects);
      CharacterAnimation previousAnimation = mSprite.getAnimation();
      if (mObject.isInAir())
      {
         if (previousAnimation == CharacterAnimation::TurnFront ||
            previousAnimation == CharacterAnimation::IdleFront ||
            previousAnimation == CharacterAnimation::JumpFront ||
            previousAnimation == CharacterAnimation::FlyFront)
         {
            mSprite.setAnimation(CharacterAnimation::FlyFront);
         }
         else
         {
            mSprite.setAnimation(CharacterAnimation::FlySide);
         }

         if (mObject.getVelocity().y > 0)
         {
            mSprite.setCurrentFrame(1);
         }
         else
         {
            mSprite.setCurrentFrame(0);
         }
      }
      else if (previousAnimation == CharacterAnimation::FlyFront)
      {
         //set idle animation
         mSprite.setAnimation(CharacterAnimation::IdleFront);
      }
      else if (previousAnimation == CharacterAnimation::FlySide)
      {
         mSprite.setAnimation(CharacterAnimation::IdleSide);
      }
      else if (previousAnimation == CharacterAnimation::JumpFront ||
         previousAnimation == CharacterAnimation::JumpSide)
      {
         mJumpVelocity = std::max(mJumpVelocity + dt.asSeconds() * JUMP_VELOCITY_Y, MAX_JUMP_VELOCITY_Y);
      }
      mSprite.update(dt, mObject.getPosition() - mCollisionOffset);
   }

   void Character::jump()
   {
      if (!mObject.isInAir())
      {
         CharacterSide side = mSprite.getSide();
         //fix situation when y velocity is 0.f;
         mJumpVelocity = std::min(mJumpVelocity, -10.f);
         if (side == CharacterSide::Front)
         {
            mObject.setVelocity(sf::Vector2f(0.f, mJumpVelocity));
         }
         else if (side == CharacterSide::Right)
         {
            mObject.setVelocity(sf::Vector2f(JUMP_VELOCITY_X, mJumpVelocity));
         }
         else
         {
            mObject.setVelocity(sf::Vector2f(-JUMP_VELOCITY_X, mJumpVelocity));
         }
         mJumpVelocity = 0.f;
      }
   }

   void Character::go(bool right)
   {
      if (!mObject.isInAir())
      {
         CharacterSide side = mSprite.getSide();
         CharacterAnimation animation = mSprite.getAnimation();
         if (right)
         {
            mSprite.setSide(CharacterSide::Right);
            //go right
            mObject.setVelocity(sf::Vector2f(GROUND_VELOCITY_X, 0.f));
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
            }
         }
         else
         {
            mSprite.setSide(CharacterSide::Left);
            //go left
            mObject.setVelocity(sf::Vector2f(-GROUND_VELOCITY_X, 0.f));
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
            }
         }
      }
   }

   void Character::readyForJump()
   {
      CharacterAnimation animation = mSprite.getAnimation();
      if (animation != CharacterAnimation::JumpSide && animation != CharacterAnimation::JumpFront)
      {
         if (mObject.getVelocity().x > 0.f && animation != CharacterAnimation::FlyFront && animation != CharacterAnimation::FlySide)
         {
            mObject.setVelocity(sf::Vector2f(0.f, 0.f));
         }
         CharacterSide side = mSprite.getSide();
         if (side == CharacterSide::Left || side == CharacterSide::Right)
         {
            mSprite.setAnimation(CharacterAnimation::JumpSide, 0);
         }
         else if (side == CharacterSide::Front)
         {
            mSprite.setAnimation(CharacterAnimation::JumpFront, 0);
         }
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
}