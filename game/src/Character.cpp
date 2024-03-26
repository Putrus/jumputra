#include "../inc/Character.hpp"

namespace jp::game
{
   Character::Character(const math::Vector2<float> &position, const math::Vector2<float> &size,
      const logic::Properties &properties,
      const std::vector<std::shared_ptr<logic::Segment>>& segments,
      const std::vector<std::shared_ptr<logic::Wind>>& winds)
      : logic::Character(position, size, properties, segments, winds)
   {
      mShape.setFillColor(sf::Color::Red);
      mShape.setSize(sf::Vector2f(size.x, size.y));
      mShape.setPosition(sf::Vector2f(position.x, position.y));
   }

   Character::Character(const math::Rect<float>& rect,
      const logic::Properties &properties,
      const std::vector<std::shared_ptr<logic::Segment>>& segments,
      const std::vector<std::shared_ptr<logic::Wind>>& winds)
      : logic::Character(rect, properties, segments, winds)
   {
      mShape.setFillColor(sf::Color::Red);
      mShape.setSize(sf::Vector2f(rect.width, rect.height));
      mShape.setPosition(sf::Vector2f(rect.left, rect.top));
   }

   void Character::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
   {
      target.draw(mShape);
   }

   void Character::setPosition(float x, float y)
   {
      mShape.setPosition(sf::Vector2f(x, y));
      logic::Character::setPosition(x, y);
   }

   void Character::setPosition(const math::Vector2<float>& position)
   {
      mShape.setPosition(sf::Vector2f(position.x, position.y));
      logic::Character::setPosition(position);
   }

   void Character::setRect(const math::Rect<float>& rect)
   {
      setPosition(rect.getPosition());
      mShape.setSize(sf::Vector2f(rect.width, rect.height));
      logic::Character::setRect(rect);
   }

   void Character::setRectTop(float y)
   {
      mShape.setPosition(sf::Vector2f(mShape.getPosition().x, y));
      logic::Character::setRectTop(y);
   }

   void Character::setRectBottom(float y)
   {
      mShape.setPosition(sf::Vector2f(mShape.getPosition().x, y - mShape.getSize().y));
      logic::Character::setRectBottom(y);
   }

   void Character::setRectLeft(float x)
   {
      mShape.setPosition(sf::Vector2f(x, mShape.getPosition().y));
      logic::Character::setRectLeft(x);
   }

   void Character::setRectRight(float x)
   {
      mShape.setPosition(sf::Vector2f(x - mShape.getSize().x, mShape.getPosition().y));
      logic::Character::setRectRight(x);
   }
}