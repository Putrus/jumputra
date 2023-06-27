#pragma once

#include "ResourceManager.h"

namespace jp::res
{
   enum class Font : int
   {
      Pixel = 0
   };

   typedef ResourceManager<Font, sf::Font> FontManager;

   enum class Texture : int
   {

   };

   enum class Sound : int
   {

   };
}