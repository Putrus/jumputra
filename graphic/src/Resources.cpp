#include "../inc/Resources.hpp"

namespace jp::graphic
{
   Resources::Resources()
   {
      loadFonts();
      loadTextures();
      loadSoundBuffers();
   }

   const sf::Font& Resources::getFont(FontID id) const
   {
      return mFontManager.get(id);
   }

   const sf::Texture& Resources::getTexture(TextureID id) const
   {
      return mTextureManager.get(id);
   }

   const sf::SoundBuffer& Resources::getSoundBuffer(SoundBufferID id) const
   {
      return mSoundBufferManager.get(id);
   }

   void Resources::loadFonts()
   {
      mFontManager.load(FontID::Alkhemikal, "data/resources/fonts/Alkhemikal.ttf");
   }

   void Resources::loadTextures()
   {
   }

   void Resources::loadSoundBuffers()
   {
   }
}