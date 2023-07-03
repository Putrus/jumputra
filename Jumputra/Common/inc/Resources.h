#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace jp::res
{
   enum class Font : int
   {
      Pixel = 0
   };

   enum class Texture : int
   {
      Penguin = 0
   };

   enum class SoundBuffer : int
   {

   };

   template <typename Enum, typename Resource>
   class ResourceManager final
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
         if (resource == resources.end())
         {
            throw std::runtime_error("Resource with id " + std::to_string(static_cast<int>(id)) + " doesn't exist");
         }
         return *resource->second;
      }

   private:
      std::map<Enum, std::unique_ptr<Resource>> resources;
   };

   typedef ResourceManager<Texture, sf::Texture> TextureManager;
   typedef ResourceManager<Font, sf::Font> FontManager;
   typedef ResourceManager<SoundBuffer, sf::SoundBuffer> SoundBufferManager;

   class Resources final
   {
   public:
      Resources();

      const sf::Font& getFont(Font font) const;
      const sf::Texture& getTexture(Texture texture) const;
      const sf::SoundBuffer getSoundBuffer(SoundBuffer soundBuffer) const;

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