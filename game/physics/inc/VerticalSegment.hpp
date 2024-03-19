#include "Segment.hpp"

namespace jp::game::physics
{
   class VerticalSegment final : public Segment
   {
   public:
      VerticalSegment(float aX, float aY, float bX, float bY,
         SegmentSurface surface = SegmentSurface::Ordinary);
      VerticalSegment(float x1, float x2, float y,
         SegmentSurface surface = SegmentSurface::Ordinary);
      VerticalSegment(const math::Vector2<float>& a, const math::Vector2<float>& b,
         SegmentSurface surface = SegmentSurface::Ordinary);

      virtual SegmentCollision checkCollision(const math::Rect<float>& oldRect,
         const math::Rect<float>& newRect) const override;

   private:
      bool isCollision(math::Vector2<float> a, math::Vector2<float> b) const;
   };
}