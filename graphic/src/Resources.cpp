#include "../inc/Resources.hpp"

namespace jp::graphic
{
   Resources::Resources(const std::string& dataPath/* = "data"*/)
   {
      loadFonts(dataPath + "/resources/fonts/");
      loadTextures(dataPath + "/resources/textures/");
      loadSoundBuffers(dataPath + "/resources/soundBuffers/");
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

   void Resources::loadFonts(const std::string& dirPath)
   {
      mFontManager.load(FontID::Alkhemikal, dirPath + "Alkhemikal.ttf");
   }

   void Resources::loadTextures(const std::string& dirPath)
   {
   }

   void Resources::loadSoundBuffers(const std::string& dirPath)
   {
   }
}