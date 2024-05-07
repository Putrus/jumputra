#pragma once

#include "../../graphic/inc/Properties.hpp"
#include "../../logic/inc/Properties.hpp"

namespace jp::game
{
   struct Properties : public logic::Loadable
   {
      void loadFromJson(const nlohmann::json& json) override;

      std::string language;

      graphic::Properties graphic;
      logic::Properties logic;
   };
}