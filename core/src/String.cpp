#include "../inc/String.hpp"

#include <algorithm>
#include <chrono>
#include <format>

namespace jp::core
{
   std::string String::toUpper(const std::string& str)
   {
      std::string strCopy = str;
      std::transform(strCopy.begin(), strCopy.end(), strCopy.begin(), toupper);
      return strCopy;
   }

   std::string String::toLower(const std::string& str)
   {
      std::string strCopy = str;
      std::transform(strCopy.begin(), strCopy.end(), strCopy.begin(), tolower);
      return strCopy;
   }

   std::string String::currentDate()
   {
      const auto now = std::chrono::system_clock::now();
      std::string time = std::format("{:%d-%m-%Y_%H-%M}", now);
      return time;
   }

   std::string String::currentDateWithSeconds()
   {
      const auto now = std::chrono::system_clock::now();
      std::string time = std::format("{:%d-%m-%Y_%H-%M-%S}", now);
      return time;
   }
}