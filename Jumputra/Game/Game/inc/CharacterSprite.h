#pragma once

#include <SFML/Graphics.hpp>

namespace jp::game
{
   enum class CharacterAnimation : int
   {
      IdleFront = 0,
      IdleSide,
      JumpFront,
      FlyFront,
      JumpSide,
      FlySide,
      RunSide,
      TurnFront,
      TurnSide,
      Dead
   };

   class CharacterSprite : public sf::Sprite
   {
   public:
      bool update(const sf::Time& dt, const sf::Vector2f& position);

      CharacterAnimation getAnimation() const;

      void setAnimation(CharacterAnimation animation);
      void setSide(bool right);

   private:
      void setTextureRectTop(int top);
      void setCurrentFrame(int frame);

      int getCurrentFrame() const;

      bool isFlipped() const;

      float mAnimSeconds = 0.f;
      bool mRun = false;
   };
}