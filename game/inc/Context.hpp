#pragma once

#include "../inc/Language.hpp"
#include "../inc/Properties.hpp"

#include "../../math/inc/Vector2.hpp"

#include "../../graphic/inc/Resources.hpp"
#include "../../graphic/inc/Window.hpp"

namespace jp::game
{
   constexpr char OPTIONS_DIR[] = "data/options/";
   constexpr char RESOURCES_DIR[] = "data/resources/";
   constexpr char SAVES_DIR[] = "data/saves/";
   constexpr char WORLDS_DIR[] = "data/worlds/";

   struct Context
   {
      Context();

      graphic::Resources resources;
      graphic::Window window;

      Language language;
      Properties properties;

      std::string world = "babiac";
      
      void setLanguage(const std::string& language);
   };
}