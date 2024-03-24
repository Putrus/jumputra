#include "../inc/Character.hpp"

namespace jp::game::logic
{
   Character::Character(const math::Vector2<float>& position, const math::Vector2<float>& size)
      : physics::Body(position, size) {}
   
   Character::Character(const math::Rect<float>& rect) : physics::Body(rect) {}
}