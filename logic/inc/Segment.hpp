#pragma once

#include "../../math/inc/Segment.hpp"
#include "../../math/inc/Rect.hpp"

#include <iostream>

namespace jp::logic
{
   enum class SegmentSurface : int
   {
      Ordinary = 0,
      Slippery,
      Sticky
   };

   std::ostream& operator<<(std::ostream& os, SegmentSurface surface);

   enum class SegmentCollision : int
   {
      No = 0,
      Top,
      Bottom,
      Left,
      Right,
      Attic,
      Roof
   };

   std::ostream& operator<<(std::ostream& os, SegmentCollision collision);

   class Segment : public math::Segment<float>
   {
   public:
      Segment(float aX, float aY, float bX, float bY,
         SegmentSurface surface = SegmentSurface::Ordinary);
      Segment(const math::Vector2<float>& a, const math::Vector2<float>& b,
         SegmentSurface surface = SegmentSurface::Ordinary);

      virtual SegmentCollision checkCollision(const math::Rect<float>& oldRect,
         const math::Rect<float>& newRect) const = 0;

      SegmentSurface getSurface() const;

      void setSurface(SegmentSurface surface);

   private:
      SegmentSurface mSurface;
   };
}