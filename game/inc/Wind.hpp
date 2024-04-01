#pragma once

#include "../../graphic/inc/Wind.hpp"
#include "../../logic/inc/Wind.hpp"

namespace jp::game
{
   class Wind : public graphic::Wind, public logic::Wind
   {
   public:
      Wind();
      // TODO      
   };
}