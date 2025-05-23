#include "../inc/Resources.hpp"

namespace jp::graphics
{
   void Resources::loadFromDirectory(const std::string& dirname)
   {
      loadFonts(dirname + "/fonts");
      loadTextures(dirname + "/textures");
      loadSoundBuffers(dirname + "/soundBuffers");
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

   void Resources::loadFonts(const std::string& dirname)
   {
      mFontManager.load(FontID::Pixeled, dirname + "/Pixeled.ttf");
   }

   void Resources::loadTextures(const std::string& dirname) {}

   void Resources::loadSoundBuffers(const std::string& dirname) {}
}