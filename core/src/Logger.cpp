#include "../inc/Logger.hpp"

#include <filesystem>

namespace jp::core
{
   Logger::Logger(const std::string& filename, bool console) : mConsole(console), mFile(std::make_unique<std::ofstream>())
   {
      std::filesystem::create_directories(std::filesystem::path(filename).parent_path());
      mFile->open(filename, std::ios::out | std::ios::app);
      if (!mFile->is_open())
      {
         throw std::runtime_error("jp::core::Logger::Logger - Failed to log, file isn't open");
      }
   }

   Logger::~Logger()
   {
      mFile->close();
   }

   Logger& Logger::operator<<(std::ostream& (*manip)(std::ostream&))
   {
      if (mFile->is_open())
      {
         *mFile << manip;
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