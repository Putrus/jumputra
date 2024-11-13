#pragma once

#include <string>

namespace jp::core
{
   class String
   {
   public:
      static std::string toUpper(const std::string& str);
      static std::string toLower(const std::string& str);
      static std::string currentDate();
      static std::string currentDateWithSeconds();
   };
}