#pragma once

#include "../inc/Language.hpp"
#include "../inc/Properties.hpp"

#include "../../algorithm/inc/Algorithm.hpp"

#include "../../math/inc/Vector2.hpp"

#include "../../graphics/inc/Resources.hpp"
#include "../../graphics/inc/Window.hpp"

#include "../../logic/inc/Statistics.hpp"

namespace jp::game
{
   constexpr char LOGS_DIR[] = "data/logs/";
   constexpr char OPTIONS_DIR[] = "data/options/";
   constexpr char RESOURCES_DIR[] = "data/resources/";
   constexpr char SAVES_DIR[] = "data/saves/";
   constexpr char STATISTICS_DIR[] = "data/statistics/";
   constexpr char WORLDS_DIR[] = "data/worlds/";

   struct Context
   {
      Context();

      graphics::Resources resources;
      graphics::Window window;

      Language language;
      Properties properties;
      algorithm::AlgorithmName algorithm = algorithm::AlgorithmName::Human;

      std::vector<std::string> worlds;

      std::string world = "";
      bool newGame = false;
      
      logic::Statistics statistics;

      void setLanguage(const std::string& language);

      void loadWorlds();
   };
}