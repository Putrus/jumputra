#include <SFML/Graphics.hpp>

#include <cassert>
#include <map>
#include <stdexcept>
#include <string>

namespace jumputra
{
   enum Font
   {
      Pixel = 0
   };

   enum Texture
   {

   };

   enum Sound
   {

   };

   template <typename Enum, typename Resource>
   class ResourceManager
   {
   public:
      void load(Enum id, const std::string& path)
      {
         auto resource = std::make_unique<Resource>();
         if (!resource->loadFromFile(path))
         {
            throw std::runtime_error("Failed to load " + path);
         }
         resources[id] = std::move(resource);
      }

      const Resource& get(Enum id) const
      {
         auto resource = resources.find(id);
         assert(resource != resources.end());
         return *resource->second;
      }

   private:
      std::map<Enum, std::unique_ptr<Resource>> resources;
   };

   typedef ResourceManager<Font, sf::Font> FontManager;
}