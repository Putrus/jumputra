#include "../inc/Constant.h"
#include "../inc/Resources.h"

#include <iostream>

namespace jp::res
{
   Resources::Resources()
   {
      load();
   }

   const sf::Font& Resources::getFont(const std::string& font) const
   {
      return mFontManager.get(font);
   }

   const sf::Texture& Resources::getTexture(const std::string& texture) const
   {
      return mTextureManager.get(texture);
   }

   const sf::SoundBuffer Resources::getSoundBuffer(const std::string& soundBuffer) const
   {
      return mSoundBufferManager.get(soundBuffer);
   }

   void Resources::load()
   {
      try
      {
         loadFonts();
         loadSoundBuffers();
         loadTextures();
      }
      catch (const std::runtime_error& e)
      {
         std::cout << e.what() << std::endl;
      }
   }

   void Resources::loadFonts()
   {
      std::string dir = std::string(FONTS_DIR);

      mFontManager.load("Pixel", dir + "Pixel.ttf");
   }

   void Resources::loadSoundBuffers()
   {

   }

   void Resources::loadTextures()
   {
      std::string dir = std::string(TEXTURES_DIR);

      mTextureManager.load("Penguin", dir + "Penguin.png");
   }
}