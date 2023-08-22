#include "Platform.h"

namespace jp::physics
{
   Platform::Platform(const std::vector<math::Vector2<float>>& points, SurfaceType type /*= SurfaceType::Normal*/)
      : mPoints(points), mType(type) {}
}