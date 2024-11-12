#pragma once

#include "Bot.hpp"
#include "Properties.hpp"

#include "../../logic/inc/Engine.hpp"

#include <map>

namespace jp::algorithm
{
   class Wanderer : public Bot
   {
   public:
      Wanderer(const algorithm::Properties& properties, const std::shared_ptr<logic::Character>& character);

      void update(float dt) override;

   protected:
      virtual void afterMove(math::Vector2<float>& position);
      virtual void whileWander(math::Vector2<float>& position);
      void setMove(const Move& move);

      std::shared_ptr<logic::Segment> mSegmentBeforeJump;
      math::Vector2<float> mLastPosition = math::Vector2<float>();
      const Properties& mProperties;

   private:
      void wander(math::Vector2<float>& position);

      math::Vector2<float> mLastChangeDirectionPosition = math::Vector2<float>();
   };
}