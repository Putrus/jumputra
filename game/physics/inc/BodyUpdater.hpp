#pragma once

#include "Body.hpp"
#include "Properties.hpp"
#include "Segment.hpp"
#include "Wind.hpp"

#include <memory>
#include <vector>

namespace jp::game::physics
{
   class BodyUpdater final
   {
   public:
      void update(float dt, Body& body,
         const Properties& properties,
         const std::vector<std::shared_ptr<Segment>>& segments,
         const std::vector<std::shared_ptr<Wind>>& winds) const;
   };
}