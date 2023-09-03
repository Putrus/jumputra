#include "Platform.h"

#include <string>

namespace jp::physics
{
   Platform::Platform(const std::vector<math::Vector2<float>>& points, PlatformType type /*= PlatformType::Ordinary*/)
      : mPoints(points), mType(type) {}

   const std::vector<math::Vector2<float>>& Platform::getPoints() const
   {
      return mPoints;
   }

   PlatformSegment Platform::getSegment(size_t id) const
   {
      return { { mPoints.at(id), mPoints.at((id + 1) % mPoints.size()) }, mType };
   }

   std::vector<PlatformSegment> Platform::getSegments() const
   {
      std::vector<PlatformSegment> segments;
      size_t segmentsSize = getSegmentsSize();
      for (size_t segmentId = 0; segmentId < segmentsSize; ++segmentId)
      {
         segments.push_back(getSegment(segmentId));
      }
      return segments;
   }

   size_t Platform::getSegmentsSize() const
   {
      if (mPoints.size() < 2)
      {
         return 0;
      }
      else if (mPoints.size() == 2)
      {
         return 1;
      }
      else
      {
         return mPoints.size();
      }
   }

   PlatformType Platform::getType() const
   {
      return mType;
   }
}