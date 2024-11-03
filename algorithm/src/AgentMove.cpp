#include "../inc/AgentMove.hpp"

namespace jp::algorithm
{
   AgentMove::AgentMove(const math::Vector2<float>& position, const Move& move, float q)
      : mPosition(position), mMove(move), mQ(q) {}

   const math::Vector2<float>& AgentMove::getPosition() const
   {
      return mPosition;
   }

   float AgentMove::getQ() const
   {
      return mQ;
   }

   void AgentMove::setPosition(const math::Vector2<float>& position)
   {
      mPosition = position;
   }

   void AgentMove::setQ(float q)
   {
      mQ = q;
   }
}