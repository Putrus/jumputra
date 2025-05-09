#pragma once

#include "../../math/inc/Rect.hpp"
#include "../../math/inc/Vector2.hpp"

#include <SFML/Graphics.hpp>

namespace jp::graphics
{
   class Goal : public sf::Drawable
   {
   public:
      Goal(const math::Rect<float>& rect);
      Goal(const nlohmann::json& json);
      
      void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

   private:
      sf::RectangleShape mShape;
   };
}