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
      }
      return true;
   }

   CharacterAnimation CharacterSprite::getAnimation() const
   {
      return static_cast<CharacterAnimation>(getTextureRect().top / getTextureRect().height);
   }

   void CharacterSprite::setAnimation(CharacterAnimation animation)
   {
      setTextureRectTop(static_cast<int>(animation));
   }

   void CharacterSprite::setSide(bool right)
   {
      sf::IntRect textureRect = getTextureRect();
      //for blinking bug
      int currentFrame = getCurrentFrame();
      if (right)
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

   void CharacterSprite::setTextureRectTop(int top)
   {
      sf::IntRect textureRect = getTextureRect();
      textureRect.top = top * textureRect.height;
      setTextureRect(textureRect);
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

   int CharacterSprite::getCurrentFrame() const
   {
      int currentFrame = getTextureRect().left / std::abs(getTextureRect().width);
      if (isFlipped())
      {
         --currentFrame;
      }
      return currentFrame;
   }

   bool CharacterSprite::isFlipped() const
   {
      return getTextureRect().width < 0;
   }
}