#pragma once

namespace jp::logic
{
   class Updatable
   {
   public:
      virtual void update(float dt) = 0;
   };
}