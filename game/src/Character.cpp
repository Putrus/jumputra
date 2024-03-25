#include "../inc/Character.hpp"

namespace jp::game
{
   Character::Character(const math::Vector2<float>& position,
      const math::Vector2<float>& size) : logic::Character(position, size) {}
      
   void Character::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
   {
      //TODO
      sf::RectangleShape shape(sf::Vector2f(getRect().width, getRect().height));
      shape.setPosition(sf::Vector2f(getPosition().x, getPosition().y));
      shape.setFillColor(sf::Color::Red);
      target.draw(shape);
   }

   void Character::event(const sf::Event& event)
   {
      
   }
}