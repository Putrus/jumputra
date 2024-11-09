#pragma once

#include "Move.hpp"

namespace jp::algorithm
{
   class AgentMove
   {
   public:
      AgentMove() = default;
      AgentMove(const math::Vector2<float>& position, const Move& move, float q);

      AgentMove& operator=(const AgentMove& other);

      const math::Vector2<float>& getPosition() const;
      float getQ() const;

      void setPosition(const math::Vector2<float> &position);
      void setQ(float q);

      friend std::ostream& operator<<(std::ostream& os, const AgentMove& move);

   private:
      math::Vector2<float> mPosition;
      Move mMove;
      float mQ;
   };

   std::ostream& operator<<(std::ostream& os, const AgentMove& move);
}