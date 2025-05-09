#include "../inc/Character.hpp"

namespace jp::graphics
{
   Character::Character(const math::Vector2<float>& position, const math::Vector2<float>& size)
      : mShape(sf::Vector2f(size.x, size.y))
   {
      mShape.setPosition(sf::Vector2f(position.x, position.y));
      mShape.setFillColor(sf::Color::Red);
   }

   Character::Character(const math::Rect<float>& rect) : mShape(sf::Vector2f(rect.width, rect.height))
   {
      mShape.setPosition(sf::Vector2f(rect.left, rect.top));
      mShape.setFillColor(sf::Color::Red);
   }

   Character::Character(const nlohmann::json& json)
      : Character(math::Rect<float>(json["rect"]["left"], json["rect"]["top"], json["rect"]["width"], json["rect"]["height"])) {}

   void Character::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
   {
      target.draw(mShape);
   }

   void Character::setFlattening(float flattening)
   {
      mFlattening = flattening;
   }

   void Character::setPosition(float x, float y)
   {
      mShape.setPosition(sf::Vector2f(x, y + mFlattening));
   }

   void Character::setPosition(const math::Vector2<float>& position)
   {
      mShape.setPosition(sf::Vector2f(position.x, position.y + mFlattening));
   }

   void Character::setRect(const math::Rect<float>& rect)
   {
      setPosition(rect.getPosition().x, rect.getPosition().y);
      mShape.setSize(sf::Vector2f(rect.width, rect.height - mFlattening));
   }

   void Character::setRectTop(float y)
   {
      mShape.setPosition(sf::Vector2f(mShape.getPosition().x, y + mFlattening));
   }

   void Character::setRectBottom(float y)
   {
      mShape.setPosition(sf::Vector2f(mShape.getPosition().x, y - mShape.getSize().y + mFlattening));
   }

   void Character::setRectLeft(float x)
   {
      mShape.setPosition(sf::Vector2f(x, mShape.getPosition().y + mFlattening));
   }

   void Character::setRectRight(float x)
   {
      mShape.setPosition(sf::Vector2f(x - mShape.getSize().x, mShape.getPosition().y + mFlattening));
   }
}