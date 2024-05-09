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
      jumps = json.at("jumps");
      falls = json.at("falls");
      time = json.at("time");
   }

   nlohmann::json Statistics::toJson() const
   {
      nlohmann::json json;
      json.at("jumps") = jumps;
      json.at("falls") = falls;
      json.at("time") = time;

      return json;
   }

   Statistics& Statistics::operator=(const nlohmann::json& json)
   {
      fromJson(json);
      return *this;
   }

   std::ostream& operator<<(std::ostream& os, const Statistics& statistics)
   {
      os << "jumps: " << statistics.jumps << " falls: " << statistics.falls << " time: " << statistics.time;
      return os;
   }
}