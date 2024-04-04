#pragma once

#include "../../graphic/inc/Segment.hpp"
#include "../../logic/inc/Segment.hpp"

namespace jp::game
{
   class Segment : public graphic::Segment
   {
   public:
      Segment(float aX, float aY, float bX, float bY,
         logic::SegmentSurface surface = logic::SegmentSurface::Ordinary);
      Segment(const math::Vector2<float>& a, const math::Vector2<float>& b,
         logic::SegmentSurface surface = logic::SegmentSurface::Ordinary);
      
      static std::shared_ptr<Segment> create(const math::Vector2<float>& a, const math::Vector2<float>& b,
         logic::SegmentSurface surface = logic::SegmentSurface::Ordinary);

      std::shared_ptr<logic::Segment> getLogicSegment() const;

   private:
      std::shared_ptr<logic::Segment> mLogicSegment;
   };
}