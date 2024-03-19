#include "../inc/DiagonalSegment.hpp"

#include <algorithm>
#include <sstream>

namespace jp::game::physics
{
   DiagonalSegment::DiagonalSegment(float aX, float aY, float bX, float bY,
      SegmentSurface surface/* = SegmentSurface::Ordinary*/)
      : Segment(aX, aY, bX, bY, surface)
   {
      if (!isDiagonal())
      {
         std::stringstream ss;
         ss << "DiagonalSegment::DiagonalSegment - Failed to create, " << *this << " isn't diagonal";
         throw std::invalid_argument(ss.str());
      }

      if (a.x > b.x)
      {
         swapPoints();
      }
   }

   DiagonalSegment::DiagonalSegment(const math::Vector2<float>& a, const math::Vector2<float>& b,
      SegmentSurface surface/* = SegmentSurface::Ordinary*/)
      : DiagonalSegment(a.x, a.y, b.x, b.y, surface) {}

   SegmentCollision DiagonalSegment::checkCollision(const math::Rect<float>& oldRect,
         const math::Rect<float>& newRect) const
   {
      float slope = getSlope();
      float intercept = b.y - slope * b.x;
      if (isHorizontalCollision(newRect.getLeftTop(), newRect.getRightTop(), slope, intercept) ||
         isHorizontalCollision(newRect.getLeftBottom(), newRect.getRightBottom(), slope, intercept))
      {
         return newRect.getCenter().y > oldRect.getCenter().y ? SegmentCollision::Roof : SegmentCollision::Attic;
      }
      else if (isVerticalCollision(newRect.getLeftTop(), newRect.getLeftBottom(), slope, intercept) ||
         isVerticalCollision(newRect.getRightTop(), newRect.getRightBottom(), slope, intercept))
      {
         if (oldRect.left >= b.x)
         {
            return SegmentCollision::Left;
         }
         else if (oldRect.getRight() <= a.x)
         {
            return SegmentCollision::Right;
         }
         else
         {
            return SegmentCollision::No;
         }
      }
      return SegmentCollision::No;
   }

   bool DiagonalSegment::isHorizontalCollision(math::Vector2<float> a,
      math::Vector2<float> b, float slope, float intercept) const
   {
      float commonX = (a.y - intercept) / slope;
      return commonX >= a.x && commonX <= b.x && commonX >= a.x && commonX <= b.x;
   }

   bool DiagonalSegment::isVerticalCollision(math::Vector2<float> a,
      math::Vector2<float> b, float slope, float intercept) const
   {
      float commonY = a.x * slope + intercept;
      return commonY >= a.y && commonY <= b.y && commonY >= std::min(a.y, b.y) && commonY <= std::max(a.y, b.y);
   }
}