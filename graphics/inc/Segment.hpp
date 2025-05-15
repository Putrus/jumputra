#pragma once

#include "../../math/inc/Vector2.hpp"

#include <SFML/Graphics.hpp>

namespace jp::graphics
{
   class Segment : public sf::Drawable
   {
   public:
      Segment(float aX, float aY, float bX, float bY,
         const sf::Color& color = sf::Color::White);
      Segment(const math::Vector2<float>& a, const math::Vector2<float>& b,
         const sf::Color& color = sf::Color::White);
      Segment(const sf::Vector2f& a, const sf::Vector2f& b,
         const sf::Color& color = sf::Color::White);
      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

      void setFillColor(const sf::Color &color);

   private:
      sf::VertexArray mVertices;
   };
}