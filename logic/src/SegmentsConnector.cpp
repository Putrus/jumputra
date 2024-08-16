#include "../inc/SegmentsConnector.hpp"

namespace jp::logic
{
   void SegmentsConnector::connect(std::vector<std::shared_ptr<Segment>>& segments)
   {
      for (auto itFirstSegment = segments.begin(); itFirstSegment != segments.end(); ++itFirstSegment)
      {
         for (auto itSecondSegment = segments.begin(); itSecondSegment != segments.end();)
         {
            std::shared_ptr<Segment> first = *itFirstSegment;
            std::shared_ptr<Segment> second = *itSecondSegment;
            if (first == second || first->getSurface() != second->getSurface())
            {
               ++itSecondSegment;
               continue;
            }

            if (first->isHorizontal() && second->isHorizontal() &&
               first->a.y == second->a.y &&
               first->b.x >= second->a.x - 1.f && first->b.x <= second->b.x + 1.f)
            {
               first->b.x = second->b.x;
               itSecondSegment = segments.erase(itSecondSegment);
            }
            else if (first->isVertical() && second->isVertical() &&
               first->a.x == second->a.x &&
               first->b.y >= second->a.y - 1.f && first->b.y <= second->b.y + 1.f)
            {
               first->b.y = second->b.y;
               itSecondSegment = segments.erase(itSecondSegment);
            }
            else if (first->isDiagonal() && second->isDiagonal() &&
               first->getSlope() == second->getSlope() &&
               first->getIntercept() == second->getIntercept() &&
               first->b.x >= second->a.x - 1.f && first->b.x <= second->b.x + 1.f &&
               first->b.y >= second->a.y - 1.f && first->b.y <= second->b.y + 1.f)
            {
               first->b = second->b;
               itSecondSegment = segments.erase(itSecondSegment);
               itFirstSegment = segments.begin();
            }
            else
            {
               ++itSecondSegment;
            }
         }
      }
   }
}