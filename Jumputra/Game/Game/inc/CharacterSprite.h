#pragma once

#include <SFML/Graphics.hpp>

namespace jp::game
{
   enum class CharacterSide : int
   {
      Front = 0,
      Left,
      Right,
      Turning
   };

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
      CharacterSide getSide() const;

      void setAnimation(CharacterAnimation animation, int frame = -1);
      void setSide(CharacterSide side);
      void setCurrentFrame(int frame);

   private:
      bool isFlipped() const;

      int getCurrentFrame() const;

      void setTextureRectTop(int top);

      float mAnimSeconds = 0.f;
      bool mRun = false;
   };
}