#pragma once

#include <nlohmann/json.hpp>

namespace jp::logic
{
   class Jsonable
   {
   public:
      Jsonable();
      Jsonable(const std::string& filename);
      Jsonable(const nlohmann::json& json);

      void loadFromJsonFile(const std::string& filename);
      void saveToJsonFile(const std::string& filename);

      virtual void fromJson(const nlohmann::json& json);
      virtual nlohmann::json toJson() const = 0;
   };
}