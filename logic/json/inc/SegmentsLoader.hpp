#pragma once

#include "../../physics/inc/Segment.hpp"

#include <memory>
#include <vector>

namespace jp::game::json
{
   class SegmentsLoader
   {
   public:
      std::vector<std::shared_ptr<physics::Segment>> loadSegments(const std::string& filename) const;

   private:
      std::shared_ptr<physics::Segment> createSegment(const math::Vector2<float>& a,
        const math::Vector2<float>& b, physics::SegmentSurface surface) const;
   };
}