#include "../inc/Jsonable.hpp"

#include <fstream>

namespace jp::core
{
   void Jsonable::loadFromJsonFile(const std::string& filename)
   {
      std::ifstream file(filename);
      if (!file.is_open())
      {
         throw std::runtime_error("jp::logic::Jsonable::loadFromJsonFile - Failed to open file " + filename);
      }

      nlohmann::json data;
      file >> data;
      file.close();

      fromJson(data);
   }

   void Jsonable::saveToJsonFile(const std::string& filename) const
   {
      std::ofstream file(filename);
      if (!file.is_open())
      {
         throw std::runtime_error("jp::logic::Jsonable::saveToJsonFile - Failed to open file " + filename);
      }

      file << toJson();
      file.close();
   }
}