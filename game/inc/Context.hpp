#pragma once

#include "../inc/Language.hpp"
#include "../inc/Properties.hpp"

#include "../../math/inc/Vector2.hpp"

#include "../../graphic/inc/Resources.hpp"
#include "../../graphic/inc/Window.hpp"

#include "../../logic/inc/Statistics.hpp"

#include "../../algorithm/inc/Algorithm.hpp"

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

      std::vector<std::string> worlds;

      std::string world = "";
      bool newGame = false;
      
      logic::Statistics statistics;

      algorithm::AlgorithmName algorithm = algorithm::AlgorithmName::Dummy;

      void setLanguage(const std::string& language);

      void loadWorlds();
   };
}