#pragma once

#include "Segment.hpp"

#include <nlohmann/json.hpp>

#include <vector>

namespace jp::logic
{
   class SegmentsLoader
   {
   public:
      std::vector<std::shared_ptr<Segment>> loadSegmentsFromFile(const std::string &filename) const;
      std::vector<std::shared_ptr<Segment>> loadSegmentsFromJson(const nlohmann::json& json) const;
   };
}