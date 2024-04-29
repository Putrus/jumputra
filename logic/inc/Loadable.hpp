#pragma once

#include <nlohmann/json.hpp>

#include <string>

namespace jp::logic
{
   class Loadable
   {
   public:
      void loadFromFile(const std::string& filename);
      virtual void loadFromJson(const nlohmann::json& json) = 0;
   };
}