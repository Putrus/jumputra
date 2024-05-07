#pragma once

#include "ResourceManager.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace jp::graphic
{
   enum class FontID : int
   {
      Pixeled = 0
   };

   enum class TextureID : int
   {
   };

   enum class SoundBufferID : int
   {

   };

   typedef ResourceManager<FontID, sf::Font> FontManager;
   typedef ResourceManager<TextureID, sf::Texture> TextureManager;
   typedef ResourceManager<SoundBufferID, sf::SoundBuffer> SoundBufferManager;

   class Resources final
   {
   public:
      void loadFromDirectory(const std::string& dirname);

      const sf::Font& getFont(FontID id) const;
      const sf::Texture& getTexture(TextureID id) const;
      const sf::SoundBuffer& getSoundBuffer(SoundBufferID id) const;

   private:
      void loadFonts(const std::string& dirname);
      void loadTextures(const std::string& dirname);
      void loadSoundBuffers(const std::string& dirname);

      FontManager mFontManager;
      TextureManager mTextureManager;
      SoundBufferManager mSoundBufferManager;
   };
}