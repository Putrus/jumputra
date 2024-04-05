#include "../inc/Character.hpp"

namespace jp::game
{
   Character::Character(const math::Vector2<float> &position, const math::Vector2<float> &size,
      const logic::Properties &properties,
      const std::vector<std::shared_ptr<logic::Segment>>& segments,
      const std::vector<std::shared_ptr<logic::Wind>>& winds)
      : graphic::Character(position, size), logic::Character(position, size, properties, segments, winds) {}

   Character::Character(const math::Rect<float>& rect,
      const logic::Properties &properties,
      const std::vector<std::shared_ptr<logic::Segment>>& segments,
      const std::vector<std::shared_ptr<logic::Wind>>& winds)
      : graphic::Character(rect), logic::Character(rect, properties, segments, winds) {}

   void Character::setPosition(float x, float y)
   {
      graphic::Character::setPosition(x, y);
      logic::Character::setPosition(x, y);
   }

   void Character::setPosition(const math::Vector2<float>& position)
   {
      graphic::Character::setPosition(position);
      logic::Character::setPosition(position);
   }

   void Character::setRect(const math::Rect<float>& rect)
   {
      graphic::Character::setRect(rect);
      logic::Character::setRect(rect);
   }

   void Character::setRectTop(float y)
   {
      graphic::Character::setRectTop(y);
      logic::Character::setRectTop(y);
   }

   void Character::setRectBottom(float y)
   {
      graphic::Character::setRectBottom(y);
      logic::Character::setRectBottom(y);
   }

   void Character::setRectLeft(float x)
   {
      graphic::Character::setRectLeft(x);
      logic::Character::setRectLeft(x);
   }

   void Character::setRectRight(float x)
   {
      graphic::Character::setRectRight(x);
      logic::Character::setRectRight(x);
   }

   void Character::setState(logic::CharacterState state)
   {
      switch (state)
      {
         case logic::CharacterState::Squatting:
            graphic::Character::setFlattening(mRect.height * 1.f / 3.f);
            break;
         case logic::CharacterState::Dying:
            graphic::Character::setFlattening(mRect.height * 2.f / 3.f);
            break;
         default:
            graphic::Character::setFlattening(0.f);
            break;
      }
      logic::Character::setState(state);
   }
}