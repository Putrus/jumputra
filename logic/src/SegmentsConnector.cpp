#include "../inc/SegmentsConnector.hpp"

namespace jp::logic
{
   void SegmentsConnector::connect(std::vector<std::shared_ptr<Segment>>& segments)
   {
      for (auto itFirstSegment = segments.begin(); itFirstSegment != segments.end(); ++itFirstSegment)
      {
         std::shared_ptr<Segment> first = *itFirstSegment;
         for (auto itSecondSegment = segments.begin(); itSecondSegment != segments.end();)
         {
            std::shared_ptr<Segment> second = *itSecondSegment;
            if (first == second || (first->isHorizontal() && first->getSurface() != second->getSurface()))
            {
               ++itSecondSegment;
               continue;
            }

            if (first->isHorizontal() && second->isHorizontal() &&
               first->a.y == second->a.y && isHorizontalOverlap(first, second))
            {
               horizontalMerge(first, second);
               if (!removeSecond(segments, itFirstSegment, itSecondSegment))
               {
                  break;
               }
            }
            else if (first->isVertical() && second->isVertical() &&
               first->a.x == second->a.x && isVerticalOverlap(first, second))
            {
               verticalMerge(first, second);
               if (!removeSecond(segments, itFirstSegment, itSecondSegment))
               {
                  break;
               }
            }
            else if (first->isDiagonal() && second->isDiagonal() &&
               first->getSlope() == second->getSlope() &&
               first->getIntercept() == second->getIntercept() &&
               isHorizontalOverlap(first, second) && isVerticalOverlap(first, second))
            {
               horizontalMerge(first, second);
               verticalMerge(first, second);
               if (!removeSecond(segments, itFirstSegment, itSecondSegment))
               {
                  break;
               }
            }
            else
            {
               ++itSecondSegment;
            }
         }
      }
   }

   bool SegmentsConnector::isHorizontalOverlap(const std::shared_ptr<Segment>& first, const std::shared_ptr<Segment>& second)
   {
      return (first->a.x >= second->a.x - 1.f && first->a.x <= second->b.x + 1.f) ||
         (first->b.x >= second->a.x - 1.f && first->b.x <= second->b.x + 1.f) ||
         (second->a.x >= first->a.x - 1.f && second->a.x <= first->b.x + 1.f) ||
         (second->b.x >= first->a.x - 1.f && second->b.x <= first->b.x + 1.f);
   }
   
   bool SegmentsConnector::isVerticalOverlap(const std::shared_ptr<Segment>& first, const std::shared_ptr<Segment>& second)
   {
      return (first->a.y >= second->a.y - 1.f && first->a.y <= second->b.y + 1.f) ||
         (first->b.y >= second->a.y - 1.f && first->b.y <= second->b.y + 1.f) ||
         (second->a.y >= first->a.y - 1.f && second->a.y <= first->b.y + 1.f) ||
         (second->b.y >= first->a.y - 1.f && second->b.y <= first->b.y + 1.f);
   }

   void SegmentsConnector::horizontalMerge(const std::shared_ptr<Segment>& first, const std::shared_ptr<Segment>& second)
   {
      first->a.x = std::min(first->a.x, second->a.x);
      first->b.x = std::max(first->b.x, second->b.x);
   }
   
   void SegmentsConnector::verticalMerge(const std::shared_ptr<Segment>& first, const std::shared_ptr<Segment>& second)
   {
      first->a.y = std::min(first->a.y, second->a.y);
      first->b.y = std::max(first->b.y, second->b.y);
   }

   bool SegmentsConnector::removeSecond(std::vector<std::shared_ptr<Segment>>& segments,
      std::vector<std::shared_ptr<jp::logic::Segment>>::iterator& first,
      std::vector<std::shared_ptr<jp::logic::Segment>>::iterator& second)
   {
      int dist = std::distance(segments.begin(), first);
      second = segments.erase(second);
      if (dist >= segments.size())
      {
         return false;
      }
      first = segments.begin() + dist;
      return true;
   }
}