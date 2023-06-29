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
         mFontManager.load(Font::Pixel, "Resources/Fonts/Pixel.ttf");
         mTextureManager.load(Texture::Penguin, "Resources/Textures/Penguin.png");
      }
      catch (const std::runtime_error& e)
      {
         std::cout << e.what() << std::endl;
      }
   }
}