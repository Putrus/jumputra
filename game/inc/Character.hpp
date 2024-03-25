#pragma once

#include "Eventable.hpp"

#include "../logic/inc/Character.hpp"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class Character : public sf::Drawable, public Eventable, public logic::Character
   {
   public:
      Character(const math::Vector2<float>& position,
         const math::Vector2<float>& size);
      
      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
      void event(const sf::Event& event) override;
   };
}