#pragma once

#include "Segment.hpp"

#include <vector>

namespace jp::logic
{
   class SegmentsConnector
   {
   public:
      static void connect(std::vector<std::shared_ptr<Segment>>& segments);
   };
}