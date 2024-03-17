#include "../inc/Body.hpp"

namespace jp::game::physics
{
   std::ostream& operator<<(std::ostream& os, BodyState state)
   {
      switch (state)
      {
         case BodyState::Dying:
         os << "Dying";
         break;
         case BodyState::Falling:
         os << "Falling";
         break;
         case BodyState::Flying:
         os << "Flying";
         break;
         case BodyState::Running:
         os << "Running";
         break;
         case BodyState::Sledding:
         os << "Sledding";
         break;
         case BodyState::Squatting:
         os << "Squatting";
         break;
         case BodyState::Standing:
         os << "Standing";
         break;
         case BodyState::Sticking:
         os << "Sticking";
         break;
         case BodyState::Stopping:
         os << "Stopping";
         break;
         default:
         os << "Unknown";
         break;
      }
      return os;
   }

   Body::Body() {}

   Body::Body(const math::Rect<float>& rect) : Entity(rect) {}

   BodyState Body::getState() const
   {
      return mState;
   }

   void Body::setState(BodyState state)
   {
      mState = state;
   }  
}