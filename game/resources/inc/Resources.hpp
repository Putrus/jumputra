#pragma once

#include "ResourceManager.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace jp::game::res
{
   enum class FontID : int
   {
      Alkhemikal = 0
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
      Resources();

      const sf::Font& getFont(FontID id) const;
      const sf::Texture& getTexture(TextureID id) const;
      const sf::SoundBuffer& getSoundBuffer(SoundBufferID id) const;

   private:
      void loadFonts();
      void loadTextures();
      void loadSoundBuffers();

      FontManager mFontManager;
      TextureManager mTextureManager;
      SoundBufferManager mSoundBufferManager;
   };
}