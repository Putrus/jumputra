#include "../inc/CharacterSprite.h"

#include <iostream>

namespace jp::game
{
   bool CharacterSprite::update(const sf::Time& dt, const sf::Vector2f& position)
   {
      setPosition(position);

      mAnimSeconds += dt.asSeconds();
      float animUpdateSeconds = 0.f;
      switch (getAnimation())
      {
      case CharacterAnimation::IdleFront:
      case CharacterAnimation::IdleSide:
      {
         animUpdateSeconds = 0.5f;
         while (mAnimSeconds > animUpdateSeconds)
         {
            mAnimSeconds -= animUpdateSeconds;
            if (getCurrentFrame() == 1)
            {
               //20% chance for blink
               int random = std::rand() % 100 + 1;
               if (random % 5 == 0)
               {
                  setCurrentFrame(2);
               }
               else
               {
                  setCurrentFrame(0);
               }
            }
            else
            {
               setCurrentFrame(1);
            }
         }
         break;
      }
      case CharacterAnimation::RunSide:
      {
         animUpdateSeconds = 0.2f;
         while (mAnimSeconds > animUpdateSeconds)
         {
            mAnimSeconds -= animUpdateSeconds;
            if (getCurrentFrame() == 1)
            {
               if (mRun)
               {
                  setCurrentFrame(0);
                  mRun = false;
               }
               else
               {
                  setCurrentFrame(2);
                  mRun = true;
               }
            }
            else
            {
               setCurrentFrame(1);
            }
         }
         break;
      }
      case CharacterAnimation::JumpSide:
      {
         animUpdateSeconds = 0.5f;
         while (mAnimSeconds > animUpdateSeconds)
         {
            int currentFrame = getCurrentFrame();
            if (currentFrame != 2)
            {
               setCurrentFrame(++currentFrame);
            }
            mAnimSeconds -= animUpdateSeconds;
         }
         break;
      }
      case CharacterAnimation::TurnFront:
      case CharacterAnimation::TurnSide:
         animUpdateSeconds = 0.2f;
         while (mAnimSeconds > animUpdateSeconds)
         {
            int currentFrame = getCurrentFrame();
            if (currentFrame != 2)
            {
               setCurrentFrame(++currentFrame);
            }
            else if (getAnimation() == CharacterAnimation::TurnFront)
            {
               setAnimation(CharacterAnimation::IdleFront, 0);
            }
            else
            {
               setAnimation(CharacterAnimation::IdleSide, 0);
            }
            mAnimSeconds -= animUpdateSeconds;
         }
         break;
      }
      return true;
   }

   CharacterAnimation CharacterSprite::getAnimation() const
   {
      return static_cast<CharacterAnimation>(getTextureRect().top / getTextureRect().height);
   }

   CharacterSide CharacterSprite::getSide() const
   {
      CharacterAnimation animation = getAnimation();
      if (animation == CharacterAnimation::IdleFront ||
         animation == CharacterAnimation::FlyFront ||
         animation == CharacterAnimation::JumpFront)
      {
         return CharacterSide::Front;
      }
      else if (animation == CharacterAnimation::TurnFront || animation == CharacterAnimation::TurnSide)
      {
         return CharacterSide::Turning;
      }
      else
      {
         return getTextureRect().width > 0 ? CharacterSide::Right : CharacterSide::Left;
      }
   }

   void CharacterSprite::setAnimation(CharacterAnimation animation, int frame /*= -1*/)
   {
      CharacterAnimation previousAnimation = getAnimation();
      if (previousAnimation != getAnimation())
      {
         //animation change so timer reset
         mAnimSeconds = 0.f;
      }
      setTextureRectTop(static_cast<int>(animation));
      if (frame > -1 && frame < 3)
      {
         setCurrentFrame(frame);
      }
   }

   void CharacterSprite::setSide(CharacterSide side)
   {
      sf::IntRect textureRect = getTextureRect();
      //for blinking bug
      int currentFrame = getCurrentFrame();
      if (side == CharacterSide::Front || side == CharacterSide::Right)
      {
         textureRect.width = std::abs(textureRect.width);
      }
      else
      {
         textureRect.width = -std::abs(textureRect.width);
      }
      setTextureRect(textureRect);
      setCurrentFrame(currentFrame);
   }

   void CharacterSprite::setCurrentFrame(int frame)
   {
      sf::IntRect textureRect = getTextureRect();
      int width = std::abs(textureRect.width);
      textureRect.left = frame * width;
      if (isFlipped())
      {
         textureRect.left += width;
      }
      setTextureRect(textureRect);
   }

   bool CharacterSprite::isFlipped() const
   {
      return getTextureRect().width < 0;
   }

   int CharacterSprite::getCurrentFrame() const
   {
      int currentFrame = getTextureRect().left / std::abs(getTextureRect().width);
      if (isFlipped())
      {
         --currentFrame;
      }
      return currentFrame;
   }

   void CharacterSprite::setTextureRectTop(int top)
   {
      sf::IntRect textureRect = getTextureRect();
      textureRect.top = top * textureRect.height;
      setTextureRect(textureRect);
   }
}