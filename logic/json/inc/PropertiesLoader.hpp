#pragma once

#include "../../inc/Properties.hpp"

namespace jp::game::json
{
   class PropertiesLoader
   {
   public:
      Properties loadProperties(const std::string& filename) const;
   };
}