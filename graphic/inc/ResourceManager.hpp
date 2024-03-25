#pragma once

#include <map>
#include <memory>

namespace jp::graphic
{
   template <typename Identifier, typename Resource>
   class ResourceManager
   {
   public:
      void load(Identifier id, const char* filename);

      const Resource& get(Identifier id) const;

   private:
      void insertResource(Identifier id, std::unique_ptr<Resource>&& resource);

      std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
   };

   template <typename Identifier, typename Resource>
   void ResourceManager<Identifier, Resource>::load(Identifier id, const char* filename)
   {
      std::unique_ptr<Resource> resource(new Resource());
      if (!resource->loadFromFile(filename))
      {
         throw std::runtime_error("ResourceManager::load -\
            Failed to load " + std::string(filename));
      }
      insertResource(id, std::move(resource));
   }

   template <typename Identifier, typename Resource>
   const Resource& ResourceManager<Identifier, Resource>::get(Identifier id) const
   {
      auto found = mResourceMap.find(id);
      if (found == mResourceMap.end())
      {
         throw std::runtime_error("ResourceManager::load -\
            Failed to get resource with id " + std::to_string((int)id));
      }
      return *found->second;
   }

   template <typename Identifier, typename Resource>
   void ResourceManager<Identifier, Resource>::insertResource(Identifier id,
      std::unique_ptr<Resource>&& resource)
   {
      auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
      if (!inserted.second)
      {
         throw std::runtime_error("ResourceManager::insertResource -\
            Failed to insert resource with id " + std::to_string((int)id));
      }
   }
}