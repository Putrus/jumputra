#pragma once

#include "../../graphic/inc/Segment.hpp"
#include "../../logic/inc/Segment.hpp"

namespace jp::game
{
   class Segment : public graphic::Segment
   {
   public:
      Segment(const std::shared_ptr<logic::Segment>& logicSegment);

   private:
      std::shared_ptr<logic::Segment> mLogicSegment;
   };
}