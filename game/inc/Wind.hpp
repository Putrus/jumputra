#pragma once

#include "../../logic/inc/Wind.hpp"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class Wind : public sf::Drawable, public logic::Wind
   {
   };
}