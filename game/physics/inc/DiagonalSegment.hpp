#include "Segment.hpp"

namespace jp::game::physics
{
   class DiagonalSegment final : public Segment
   {
   public:
      DiagonalSegment(float aX, float aY, float bX, float bY,
         SegmentSurface surface = SegmentSurface::Ordinary);
      DiagonalSegment(const math::Vector2<float>& a, const math::Vector2<float>& b,
         SegmentSurface surface = SegmentSurface::Ordinary);

      virtual SegmentCollision checkCollision(const math::Rect<float>& oldRect,
         const math::Rect<float>& newRect) const override;

   private:
      bool isHorizontalCollision(math::Vector2<float> a,
         math::Vector2<float> b, float slope, float intercept) const;
      bool isVerticalCollision(math::Vector2<float> a,
         math::Vector2<float> b, float slope, float intercept) const;
   };
}