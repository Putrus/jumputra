#pragma once

#include "../inc/Controller.hpp"
#include "../inc/Language.hpp"
#include "../inc/Properties.hpp"

#include "../../math/inc/Vector2.hpp"

#include "../../graphic/inc/Resources.hpp"
#include "../../graphic/inc/Window.hpp"

#include "../../logic/inc/Statistics.hpp"


namespace jp::game
{
   constexpr char OPTIONS_DIR[] = "data/options/";
   constexpr char RESOURCES_DIR[] = "data/resources/";
   constexpr char SAVES_DIR[] = "data/saves/";
   constexpr char STATISTICS_DIR[] = "data/statistics/";
   constexpr char WORLDS_DIR[] = "data/worlds/";

   struct Context
   {
      Context();

      graphic::Resources resources;
      graphic::Window window;

      Language language;
      Properties properties;
      Controller controller = Controller::Human;

      std::vector<std::string> worlds;

      std::string world = "";
      bool newGame = false;
      
      logic::Statistics statistics;


      void setLanguage(const std::string& language);

      void loadWorlds();
   };
}