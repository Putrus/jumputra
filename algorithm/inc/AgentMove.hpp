#pragma once

#include "Move.hpp"

namespace jp::algorithm
{
   class AgentMove
   {
   public:
      AgentMove(const math::Vector2<float>& position, const Move& move, float q);

      const math::Vector2<float>& getPosition() const;
      float getQ() const;

      void setPosition(const math::Vector2<float> &position);
      void setQ(float q);

   private:
      math::Vector2<float> mPosition;
      Move mMove;
      float mQ;
   };
}