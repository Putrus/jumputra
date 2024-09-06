#include "../inc/Logger.hpp"

namespace jp::core
{
   Logger::Logger(const std::string& filename, bool console) : mFile(filename, std::ios::out | std::ios::app), mConsole(console) {}

   Logger::~Logger()
   {
      mFile.close();
   }

   Logger& Logger::operator<<(std::ostream& (*manip)(std::ostream&))
   {
      if (mFile.is_open())
      {
         mFile << manip;
      }
      else
      {
         throw std::runtime_error("jp::core::Logger::operator<< - Failed to log, file isn't open");
      }

      if (mConsole)
      {
         std::cout << manip;
      }
      return *this;
   }
}