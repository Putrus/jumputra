#include "../inc/Jsonable.hpp"

#include <fstream>

namespace jp::logic
{
   Jsonable::Jsonable() {}

   Jsonable::Jsonable(const std::string& filename)
   {
      loadFromJsonFile(filename);
   }

   Jsonable::Jsonable(const nlohmann::json& json)
   {
      fromJson(json);
   }

   void Jsonable::loadFromJsonFile(const std::string& filename)
   {
      std::ifstream file(filename);
      if (!file.is_open())
      {
         throw std::runtime_error("jp::logic::Jsonable::fromJsonFile - Failed to open file " + filename);
      }

      nlohmann::json data;
      file >> data;
      file.close();

      fromJson(data);
   }

   void Jsonable::saveToJsonFile(const std::string& filename)
   {
      std::ofstream file(filename);
      if (!file.is_open())
      {
         throw std::runtime_error("jp::logic::Jsonable::saveToJsonFile - Failed to open file " + filename);
      }

      file << toJson();
      file.close();
   }

   void Jsonable::fromJson(const nlohmann::json& json) {}
}