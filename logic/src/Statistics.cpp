#include "../inc/Statistics.hpp"

namespace jp::logic
{
   Statistics::Statistics() {}

   Statistics::Statistics(const nlohmann::json& json)
   {
      fromJson(json);
   }

   void Statistics::fromJson(const nlohmann::json& json)
   {
      jumps = json["jumps"];
      falls = json["falls"];
      time = json["time"];
   }

   nlohmann::json Statistics::toJson() const
   {
      nlohmann::json json;
      json["jumps"] = jumps;
      json["falls"] = falls;
      json["time"] = time;

      return json;
   }

   std::ostream& operator<<(std::ostream& os, const Statistics& statistics)
   {
      os << "jumps: " << statistics.jumps << " falls: " << statistics.falls << " time: " << statistics.time;
      return os;
   }
}