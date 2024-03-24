#pragma once

#include "../../physics/inc/Wind.hpp"

#include <memory>
#include <vector>

namespace jp::game::json
{
   class WindsLoader
   {
   public:
      std::vector<std::shared_ptr<physics::Wind>> loadWinds(const std::string& filename) const;
   };
}