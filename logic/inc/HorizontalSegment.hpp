#pragma once

#include "Segment.hpp"

namespace jp::logic
{
   class HorizontalSegment final : public Segment
   {
   public:
      HorizontalSegment(float aX, float aY, float bX, float bY,
         SegmentSurface surface = SegmentSurface::Ordinary);
      HorizontalSegment(float x1, float x2, float y,
         SegmentSurface surface = SegmentSurface::Ordinary);
      HorizontalSegment(const math::Vector2<float>& a, const math::Vector2<float>& b,
         SegmentSurface surface = SegmentSurface::Ordinary);
      
      virtual SegmentCollision checkCollision(const math::Rect<float>& oldRect,
         const math::Rect<float>& newRect) const override;

   private:
      bool isCollision(math::Vector2<float> a, math::Vector2<float> b) const;
   };
}