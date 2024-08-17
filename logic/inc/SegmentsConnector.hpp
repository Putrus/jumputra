#pragma once

#include "Segment.hpp"

#include <vector>

namespace jp::logic
{
   class SegmentsConnector
   {
   public:
      static void connect(std::vector<std::shared_ptr<Segment>>& segments);

   private:
      static bool isHorizontalOverlap(const std::shared_ptr<Segment>& first, const std::shared_ptr<Segment>& second);
      static bool isVerticalOverlap(const std::shared_ptr<Segment>& first, const std::shared_ptr<Segment>& second);
      static void horizontalMerge(const std::shared_ptr<Segment>& first, const std::shared_ptr<Segment>& second);
      static void verticalMerge(const std::shared_ptr<Segment>& first, const std::shared_ptr<Segment>& second);
      static bool removeSecond(std::vector<std::shared_ptr<Segment>>& segments,
         std::vector<std::shared_ptr<jp::logic::Segment>>::iterator& first,
         std::vector<std::shared_ptr<jp::logic::Segment>>::iterator& second);
   };
}