#pragma once

#include "../../logic/inc/Character.hpp"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class Character : public sf::Drawable, public logic::Character
   {
   public:
      Character(const math::Vector2<float> &position, const math::Vector2<float> &size,
         const logic::Properties &properties,
         const std::vector<std::shared_ptr<logic::Segment>>& segments,
         const std::vector<std::shared_ptr<logic::Wind>>& winds);
      Character(const math::Rect<float>& rect,
         const logic::Properties &properties,
         const std::vector<std::shared_ptr<logic::Segment>>& segments,
         const std::vector<std::shared_ptr<logic::Wind>>& winds);
      
      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
   };
}