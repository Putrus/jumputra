#pragma once

#include <SFML/Graphics>

namespace jp::game
{
   enum class Action
   {
      IdleFront = 0,
      IdleSide,
      RotateSideFront,
      RotateFrontSide,
      RunSide,
      Jump,
      Fly,
      Dead
   };

   class AnimatedSprite : public sf::Sprite
   {
      

   private:
      
   };
}