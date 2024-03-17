#pragma once

#include "../../../math/inc/Segment.hpp"

#include <iostream>

namespace jp::game::physics
{
   enum class SegmentSurface : int
   {
      Ordinary = 0,
      Slippery,
      Sticky
   };

   std::ostream& operator<<(std::ostream& os, SegmentSurface surface);

   class Segment : public math::Segment<float>
   {
   public:
      Segment(float aX, float aY, float bX, float bY);
      Segment(const math::Vector2<float>& a, const math::Vector2<float>& b);

      SegmentSurface getSurface() const;

      void setSurface(SegmentSurface surface);

   private:
      SegmentSurface mSurface;
   };
}