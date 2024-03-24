#pragma once

#include "../logic/inc/Properties.hpp"
#include "../physics/inc/Properties.hpp"

namespace jp::game
{
   struct Properties
   {
      logic::Properties logic;
      physics::Properties physics;
   };
}