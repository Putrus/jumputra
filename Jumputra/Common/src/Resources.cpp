#include "../inc/Constant.h"
#include "../inc/Resources.h"

#include <iostream>

namespace jp::res
{
   Resources::Resources()
   {
      load();
   }

   const sf::Font& Resources::getFont(Font font) const
   {
      return mFontManager.get(font);
   }

   const sf::Texture& Resources::getTexture(Texture texture) const
   {
      return mTextureManager.get(texture);
   }

   const sf::SoundBuffer Resources::getSoundBuffer(SoundBuffer soundBuffer) const
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
      std::string dir = std::string(DATA_DIR) + '/' + std::string(RESOURCES_DIR) + '/' + std::string(FONTS_DIR) + '/';

      mFontManager.load(Font::Pixel, dir + "Pixel.ttf");
   }

   void Resources::loadSoundBuffers()
   {

   }

   void Resources::loadTextures()
   {
      std::string dir = std::string(DATA_DIR) + '/' + std::string(RESOURCES_DIR) + '/' + std::string(TEXTURES_DIR) + '/';

      mTextureManager.load(Texture::Penguin, dir + "Pixel.ttf");
   }
}