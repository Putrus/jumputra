#include "../inc/Character.hpp"

namespace jp::logic
{
   std::ostream& operator<<(std::ostream& os, CharacterState state)
   {
      switch (state)
      {
         case CharacterState::Dying:
         os << "Dying";
         break;
         case CharacterState::Falling:
         os << "Falling";
         break;
         case CharacterState::Flying:
         os << "Flying";
         break;
         case CharacterState::Running:
         os << "Running";
         break;
         case CharacterState::Sledding:
         os << "Sledding";
         break;
         case CharacterState::Squatting:
         os << "Squatting";
         break;
         case CharacterState::Standing:
         os << "Standing";
         break;
         case CharacterState::Sticking:
         os << "Sticking";
         break;
         case CharacterState::Stopping:
         os << "Stopping";
         break;
         default:
         os << "Unknown";
         break;
      }
      return os;
   }

   Character::Character(const math::Vector2<float> &position, const math::Vector2<float> &size,
      const Properties &properties,
      const std::vector<std::shared_ptr<Segment>>& segments,
      const std::vector<std::shared_ptr<Wind>>& winds)
      : mProperties(properties), mSegments(segments), mWinds(winds), Entity(math::Rect<float>(position, size)) {}

   Character::Character(const math::Rect<float>& rect,
      const Properties &properties,
      const std::vector<std::shared_ptr<Segment>>& segments,
      const std::vector<std::shared_ptr<Wind>>& winds)
      : mProperties(properties), mSegments(segments), mWinds(winds), Entity(rect) {}

   void Character::update(float dt)
   {
      //TODO
   }

   CharacterState Character::getState() const
   {
      return mState;
   }

   void Character::setState(CharacterState state)
   {
      mState = state;
   }  
}