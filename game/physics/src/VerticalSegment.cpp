#include "../inc/VerticalSegment.hpp"

#include <algorithm>
#include <sstream>

namespace jp::game::physics
{
   VerticalSegment::VerticalSegment(float aX, float aY, float bX, float bY,
      SegmentSurface surface/* = SegmentSurface::Ordinary*/)
      : Segment(aX, aY, bX, bY, surface)
   {
      if (!isVertical())
      {
         std::stringstream ss;
         ss << "VerticalSegment::VerticalSegment - Failed to create, " << *this << " isn't vertical";
         throw std::invalid_argument(ss.str());
      }

      if (a.y > b.y)
      {
         swapPoints();
      }
   }

   VerticalSegment::VerticalSegment(float x, float y1, float y2,
      SegmentSurface surface/* = SegmentSurface::Ordinary*/)
      : VerticalSegment(x, y1, x, y2, surface) {}

   VerticalSegment::VerticalSegment(const math::Vector2<float>& a, const math::Vector2<float>& b,
      SegmentSurface surface/* = SegmentSurface::Ordinary*/)
      : VerticalSegment(a.x, a.y, b.x, b.y, surface) {}

   SegmentCollision VerticalSegment::checkCollision(const math::Rect<float>& oldRect,
         const math::Rect<float>& newRect) const
   {
      if (isCollision(newRect.getLeftTop(), newRect.getRightTop()) ||
         isCollision(newRect.getLeftBottom(), newRect.getRightBottom()))
      {
         if (oldRect.top >= b.y)
         {
            return SegmentCollision::Top;
         }
         else if (oldRect.getBottom() <= a.y)
         {
            return SegmentCollision::Bottom;
         }
         else if (oldRect.getCenter().x > b.x)
         {
            return SegmentCollision::Left;
         }
         else
         {
            return SegmentCollision::Right;
         }
      }
      return SegmentCollision::No;
   }

   bool VerticalSegment::isCollision(math::Vector2<float> a, math::Vector2<float> b) const
   {
      return a.y > a.y && a.y < b.y && a.x > a.x && a.x < b.x;
   }
}