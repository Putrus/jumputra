#pragma once

#include <nlohmann/json.hpp>

#include <fstream>
#include <vector>

namespace jp::logic
{
   template <typename T>
   class EntityLoader
   {
   public:
      std::vector<std::shared_ptr<T>> loadFromFile(const std::string &filename) const;
      virtual std::vector<std::shared_ptr<T>> loadFromJson(const nlohmann::json& json) const = 0;
   };

   template <typename T>
   std::vector<std::shared_ptr<T>> EntityLoader<T>::loadFromFile(const std::string &filename) const
   {
      std::ifstream file(filename);
      if (!file.is_open())
      {
         throw std::runtime_error("jp::logic::EntityLoader::loadFromFile - Failed to open file " + filename);
      }

      nlohmann::json data;
      file >> data;
      file.close();

      return loadFromJson(data);
   }
}