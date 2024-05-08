#include "../inc/Goal.hpp"

namespace jp::graphic
{
   Goal::Goal(const math::Rect<float>& rect) : mShape(sf::Vector2f(rect.width, rect.height))
   {
      mShape.setPosition(sf::Vector2f(rect.left, rect.top));
      mShape.setFillColor(sf::Color::Transparent);
      mShape.setOutlineThickness(2.f);
      mShape.setOutlineColor(sf::Color::Yellow);
   }

   void Goal::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
   {
      target.draw(mShape);
   }
}