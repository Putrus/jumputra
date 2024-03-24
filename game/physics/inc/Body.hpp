#pragma once

#include "Entity.hpp"

#include "../../../math/inc/Rect.hpp"

namespace jp::game::physics
{
   enum class BodyState : int
   {
      Dying = 0,
      Falling,
      Flying,
      Running,
      Sledding,
      Sliding,
      Squatting,
      Standing,
      Sticking,
      Stopping
   };

   std::ostream& operator<<(std::ostream& os, BodyState state);

   class Body : public Entity
   {
   public:
      Body();
      Body(const math::Vector2<float>& position, const math::Vector2<float>& size);
      Body(const math::Rect<float>& rect);

      BodyState getState() const;

      void setState(BodyState state);

   protected:
      BodyState mState = BodyState::Flying;
   };
}