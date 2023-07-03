#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace jp::res
{
   template <typename Resource>
   class ResourceManager final
   {
   public:
      void load(const std::string& id, const std::string& path)
      {
         auto resource = std::make_unique<Resource>();
         if (!resource->loadFromFile(path))
         {
            throw std::runtime_error("Failed to load " + path);
         }
         resources[id] = std::move(resource);
      }

      const Resource& get(const std::string& name) const
      {
         auto resource = resources.find(name);
         if (resource == resources.end())
         {
            throw std::runtime_error("Resource with name " + name + " doesn't exist");
         }
         return *resource->second;
      }

   private:
      std::map<std::string, std::unique_ptr<Resource>> resources;
   };

   typedef ResourceManager<sf::Texture> TextureManager;
   typedef ResourceManager<sf::Font> FontManager;
   typedef ResourceManager<sf::SoundBuffer> SoundBufferManager;

   class Resources final
   {
   public:
      Resources();

      const sf::Font& getFont(const std::string& font) const;
      const sf::Texture& getTexture(const std::string& texture) const;
      const sf::SoundBuffer getSoundBuffer(const std::string& soundBuffer) const;

   private:
      void load();
      void loadFonts();
      void loadTextures();
      void loadSoundBuffers();

      FontManager mFontManager;
      SoundBufferManager mSoundBufferManager;
      TextureManager mTextureManager;
   };
}