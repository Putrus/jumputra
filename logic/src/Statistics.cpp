#include "../inc/Statistics.hpp"

namespace jp::logic
{
   void Statistics::loadFromJson(const nlohmann::json& json)
   {
      jumps = json["jumps"];
      falls = json["falls"];
      time = json["time"];
   }

   std::ostream& operator<<(std::ostream& os, const Statistics& statistics)
   {
      os << "jumps: " << statistics.jumps << " falls: " << statistics.falls << " time: " << statistics.time;
      return os;
   }
}