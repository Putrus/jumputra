#include "../inc/Logger.hpp"

namespace jp::core
{
   Logger::Logger(const std::string& filename, bool console) : mFile(filename, std::ios::out | std::ios::app), mConsole(console) {}

   Logger::~Logger()
   {
      mFile.close();
   }
}