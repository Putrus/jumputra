#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

namespace jp::core
{
   class Logger
   {
   public:
      Logger(const std::string& filename, bool console);

      virtual ~Logger();

      template <typename T>
      Logger& operator<<(const T& value);

      Logger& operator<<(std::ostream& (*manip)(std::ostream&));

   private:
      std::unique_ptr<std::ofstream> mFile;
      bool mConsole;
   };

   template <typename T>
   Logger& Logger::operator<<(const T& value)
   {
      if (mFile->is_open())
      {
         *mFile << value;
      }
      else
      {
         throw std::runtime_error("jp::core::Logger::operator<< - Failed to log, file isn't open");
      }

      if (mConsole)
      {
         std::cout << value;
      }
      return *this;
   }
}