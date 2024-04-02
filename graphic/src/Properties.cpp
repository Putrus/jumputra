#include "../inc/Properties.hpp"

namespace jp::graphic
{
   void Properties::loadFromJson(const nlohmann::json& json)
   {
      window.size.x = json["graphic"]["window"]["size"]["x"];
      window.size.y = json["graphic"]["window"]["size"]["y"];
   }
}