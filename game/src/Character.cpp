#include "../inc/Character.hpp"

namespace jp::game
{
   Character::Character(const math::Vector2<float> &position, const math::Vector2<float> &size,
      const logic::Properties &properties,
      logic::Statistics& totalStatistics,
      const std::vector<std::shared_ptr<logic::Segment>>& segments,
      const std::vector<std::shared_ptr<logic::Wind>>& winds)
      : graphics::Character(position, size), logic::Character(position, size, properties, totalStatistics, segments, winds) {}

   Character::Character(const math::Rect<float>& rect,
      const logic::Properties &properties,
      logic::Statistics& totalStatistics,
      const std::vector<std::shared_ptr<logic::Segment>>& segments,
      const std::vector<std::shared_ptr<logic::Wind>>& winds)
      : graphics::Character(rect), logic::Character(rect, properties, totalStatistics, segments, winds) {}

   Character::Character(const nlohmann::json& json,
      const logic::Properties &properties,
      logic::Statistics& totalStatistics,
      const std::vector<std::shared_ptr<logic::Segment>>& segments,
      const std::vector<std::shared_ptr<logic::Wind>>& winds)
      : graphics::Character(json), logic::Character(json, properties, totalStatistics, segments, winds) {}

   Character::Character(const logic::Character& character)
      : graphics::Character(character.getRect()), logic::Character(character) {}

   std::shared_ptr<Character> Character::create(const nlohmann::json& json,
      const logic::Properties &properties,
      logic::Statistics& totalStatistics,
      const std::vector<std::shared_ptr<logic::Segment>>& segments,
      const std::vector<std::shared_ptr<logic::Wind>>& winds)
   {
      return std::make_shared<Character>(json, properties, totalStatistics, segments, winds);
   }

   void Character::setPosition(float x, float y)
   {
      graphics::Character::setPosition(x, y);
      logic::Character::setPosition(x, y);
   }

   void Character::setPosition(const math::Vector2<float>& position)
   {
      graphics::Character::setPosition(position);
      logic::Character::setPosition(position);
   }

   void Character::setRect(const math::Rect<float>& rect)
   {
      graphics::Character::setRect(rect);
      logic::Character::setRect(rect);
   }

   void Character::setRectTop(float y)
   {
      graphics::Character::setRectTop(y);
      logic::Character::setRectTop(y);
   }

   void Character::setRectBottom(float y)
   {
      graphics::Character::setRectBottom(y);
      logic::Character::setRectBottom(y);
   }

   void Character::setRectLeft(float x)
   {
      graphics::Character::setRectLeft(x);
      logic::Character::setRectLeft(x);
   }

   void Character::setRectRight(float x)
   {
      graphics::Character::setRectRight(x);
      logic::Character::setRectRight(x);
   }

   void Character::setState(logic::CharacterState state)
   {
      switch (state)
      {
         case logic::CharacterState::Squatting:
            graphics::Character::setFlattening(mRect.height * 1.f / 3.f);
            break;
         case logic::CharacterState::Burying:
         case logic::CharacterState::Dying:
         case logic::CharacterState::Lying:
            graphics::Character::setFlattening(mRect.height * 2.f / 3.f);
            break;
         default:
            graphics::Character::setFlattening(0.f);
            break;
      }
      logic::Character::setState(state);
   }
}