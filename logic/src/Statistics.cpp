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
      totalTime = json.at("totalTime");
   }

   nlohmann::json Statistics::toJson() const
   {
      nlohmann::json json;
      json["jumps"] = jumps;
      json["falls"] = falls;
      json["time"] = time;
      json["totalTime"] = totalTime;

      return json;
   }

   Statistics& Statistics::operator=(const Statistics& other)
   {
      jumps = other.jumps;
      falls = other.falls;
      time = other.time;
      totalTime = other.totalTime;
      return *this;
   }

   Statistics& Statistics::operator=(const nlohmann::json& json)
   {
      fromJson(json);
      return *this;
   }

   std::ostream& operator<<(std::ostream& os, const Statistics& statistics)
   {
      os << "jumps: " << statistics.jumps << ", falls: " << statistics.falls <<
         ", time: " << statistics.time << ", totalTime: " << statistics.totalTime;
      return os;
   }
}