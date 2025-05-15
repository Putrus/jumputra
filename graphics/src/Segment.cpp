#include "../inc/Segment.hpp"

#include "../../math/inc/Vector2.hpp"

namespace jp::graphics
{
   Segment::Segment(float aX, float aY, float bX, float bY,
      const sf::Color& color/* = sf::Color::White*/) : mVertices(sf::PrimitiveType::Lines, 2)
   {
      mVertices[0].position = { aX, aY };
      mVertices[0].color = color;
      mVertices[1].position = { bX, bY };
      mVertices[1].color = color;
   }

   Segment::Segment(const math::Vector2<float>& a, const math::Vector2<float>& b,
      const sf::Color& color/* = sf::Color::White*/) : mVertices(sf::PrimitiveType::Lines, 2)
   {
      mVertices[0].position.x = a.x;
      mVertices[0].position.y = a.y;
      mVertices[0].color = color;
      mVertices[0].position.x = b.x;
      mVertices[0].position.y = b.y;
      mVertices[1].color = color;
   }
      
   Segment::Segment(const sf::Vector2f& a, const sf::Vector2f& b,
      const sf::Color& color/* = sf::Color::White*/) : mVertices(sf::PrimitiveType::Lines, 2)
   {
      mVertices[0].position = a;
      mVertices[0].color = color;
      mVertices[1].position = b;
      mVertices[1].color = color;
   }

   void Segment::setFillColor(const sf::Color &color)
   {
      mVertices[0].color = color;
      mVertices[1].color = color;
   }

   void Segment::draw(sf::RenderTarget &target, sf::RenderStates states) const
   {
      target.draw(mVertices);
   }
}