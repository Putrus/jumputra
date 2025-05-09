#include "../inc/Goal.hpp"

namespace jp::graphics
{
   Goal::Goal(const math::Rect<float>& rect) : mShape(sf::Vector2f(rect.width, rect.height))
   {
      mShape.setPosition(sf::Vector2f(rect.left, rect.top));
      mShape.setFillColor(sf::Color::Transparent);
      mShape.setOutlineThickness(2.f);
      mShape.setOutlineColor(sf::Color::Yellow);
   }

   Goal::Goal(const nlohmann::json& json)
      : Goal(math::Rect<float>(json["rect"]["left"], json["rect"]["top"], json["rect"]["width"], json["rect"]["height"])) {}

   void Goal::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
   {
      target.draw(mShape);
   }
}