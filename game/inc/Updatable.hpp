#pragma once

namespace jp::game
{
   class Updatable
   {
   public:
      virtual void update(float dt) = 0;
   };
}