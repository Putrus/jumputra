#pragma once

#include "Segment.h"

#include <vector>

namespace jp::physics
{
   enum class PlatformType
   {
      Ordinary,
      Slippery,
      Sticky
   };

   struct PlatformSegment
   {
      math::Segment<float> segment;
      PlatformType type;
   };

   class Platform
   {
   public:
      Platform(const std::vector<math::Vector2<float>>& points, PlatformType type = PlatformType::Ordinary);

      const std::vector<math::Vector2<float>>& getPoints() const;
      PlatformSegment getSegment(size_t id) const;
      std::vector<PlatformSegment> getSegments() const;
      size_t getSegmentsSize() const;
      PlatformType getType() const;

   private:
      std::vector<math::Vector2<float>> mPoints;
      PlatformType mType;
   };
}