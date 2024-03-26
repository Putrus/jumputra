#pragma once

#include "../../math/inc/Vector2.hpp"

#include "../../graphic/inc/Resources.hpp"
#include "../../graphic/inc/Window.hpp"

#include "../../logic/inc/Properties.hpp"

namespace jp::game
{
   struct Context
   {
      Context();

      graphic::Resources resources;
      graphic::Window window;

      logic::Properties properties;
   };
}