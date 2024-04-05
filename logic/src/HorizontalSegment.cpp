#include "../inc/HorizontalSegment.hpp"

#include <algorithm>
#include <sstream>

namespace jp::logic
{
   HorizontalSegment::HorizontalSegment(float aX, float aY, float bX, float bY,
      SegmentSurface surface/* = SegmentSurface::Ordinary*/)
      : Segment(aX, aY, bX, bY, surface)
   {
      if (!isHorizontal())
      {
         std::stringstream ss;
         ss << "jp::logic::HorizontalSegment::HorizontalSegment - Failed to create, " << *this << " isn't horizontal";
         throw std::invalid_argument(ss.str());
      }

      if (a.x > b.x)
      {
         swapPoints();
      }
   }

   HorizontalSegment::HorizontalSegment(float x1, float x2, float y,
      SegmentSurface surface/* = SegmentSurface::Ordinary*/)
      : HorizontalSegment(x1, y, x2, y, surface) {}

   HorizontalSegment::HorizontalSegment(const math::Vector2<float>& a, const math::Vector2<float>& b,
      SegmentSurface surface/* = SegmentSurface::Ordinary*/)
      : HorizontalSegment(a.x, a.y, b.x, b.y, surface) {}

   SegmentCollision HorizontalSegment::checkCollision(const math::Rect<float>& oldRect,
      const math::Rect<float>& newRect) const
   {
      if (isCollision(newRect.getLeftTop(), newRect.getLeftBottom()) ||
         isCollision(newRect.getRightTop(), newRect.getRightBottom()))
      {
         if (oldRect.left >= b.x)
         {
            std::cout << "horizontal::Left" << std::endl;
            return SegmentCollision::Left;
         }
         else if (oldRect.getRight() <= a.x)
         {
            std::cout << "horizontal::Right" << std::endl;
            return SegmentCollision::Right;
         }
         else if (oldRect.getCenter().y > b.y)
         {
            return SegmentCollision::Top;
         }
         else
         {
            return SegmentCollision::Bottom;
         }
      }
      return SegmentCollision::No;
   }

   bool HorizontalSegment::isCollision(math::Vector2<float> a, math::Vector2<float> b) const
   {
      return a.x > this->a.x && a.x < this->b.x && this->a.y > a.y && this->a.y < b.y;
   }
}