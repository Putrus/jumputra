#pragma once

#include "../inc/Language.hpp"
#include "../inc/Properties.hpp"

#include "../../math/inc/Vector2.hpp"

#include "../../graphic/inc/Resources.hpp"
#include "../../graphic/inc/Window.hpp"

namespace jp::game
{
   struct Context
   {
      Context();

      graphic::Resources resources;
      graphic::Window window;

      Language language;
      Properties properties;
   };
}