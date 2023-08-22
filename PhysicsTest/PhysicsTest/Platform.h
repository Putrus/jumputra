#pragma once

#include "Vector2.h"

#include <vector>

namespace jp::physics
{
   enum class SurfaceType
   {
      Normal,
      Slippery,
      Sticky
   };

   class Platform
   {
   public:
      Platform(const std::vector<math::Vector2<float>>& points, SurfaceType type = SurfaceType::Normal);

      std::vector<math::Vector2<float>> mPoints;
      SurfaceType mType;
   };
}