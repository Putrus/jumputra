#pragma once

#include "Wind.hpp"

#include <nlohmann/json.hpp>

#include <vector>

namespace jp::logic
{
   class WindsLoader
   {
   public:
      std::vector<std::shared_ptr<Wind>> loadWindsFromFile(const std::string &filename) const;
      std::vector<std::shared_ptr<Wind>> loadWindsFromJson(const nlohmann::json& json) const;
   };
}