#pragma once

#include <nlohmann/json.hpp>

namespace jp::core
{
   class Jsonable
   {
   public:
      void loadFromJsonFile(const std::string& filename);
      void saveToJsonFile(const std::string& filename);

      virtual void fromJson(const nlohmann::json& json) = 0;
      virtual nlohmann::json toJson() const = 0;
   };
}