#pragma once

#include <SFML/Graphics.hpp>

namespace jp::graphic
{
   class Wind : public sf::Drawable
   {
   public:
      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
   };
}