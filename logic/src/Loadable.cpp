#include "../inc/Loadable.hpp"

#include <fstream>

namespace jp::logic
{
   void Loadable::loadFromFile(const std::string& filename)
   {
      std::ifstream file(filename);
      if (!file.is_open())
      {
         throw std::runtime_error("jp::logic::Loadable::loadFromFile - Failed to open file " + filename);
      }

      nlohmann::json data;
      file >> data;
      file.close();

      loadFromJson(data);
   }
}