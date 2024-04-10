#include "../inc/Statistics.hpp"

namespace jp::logic
{
   std::ostream& operator<<(std::ostream& os, const Statistics& statistics)
   {
      os << "jumps: " << statistics.jumps << " falls: " << statistics.falls << " time: " << statistics.time;
      return os;
   }
}