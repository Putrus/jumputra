#pragma once

#include "AgentMove.hpp"
#include "Bot.hpp"
#include "Properties.hpp"

#include "../../logic/inc/Engine.hpp"

#include <map>

namespace jp::algorithm
{
   class Agent final : public Bot
   {
   public:
      Agent(const algorithm::Properties& properties, const std::shared_ptr<logic::Character>& character);

      virtual void update(float dt) override;

   private:
      void setMove(const Move& move);

      math::Vector2<float> mLastChangeDirectionPosition = math::Vector2<float>();
      math::Vector2<float> mLastPosition = math::Vector2<float>();
      std::shared_ptr<logic::Segment> mSegmentBeforeJump;
      const Properties& mProperties;

      std::map<math::Vector2<float>, std::vector<AgentMove>> mQ;
   };
}