#include "../inc/Segment.hpp"

namespace jp::game::physics
{
   std::ostream& operator<<(std::ostream& os, SegmentSurface surface)
   {
      switch(surface)
      {
         case SegmentSurface::Ordinary:
         os << "Ordinary";
         break;
         case SegmentSurface::Slippery:
         os << "Slippery";
         break;
         case SegmentSurface::Sticky:
         os << "Sticky";
         break;
         default:
         os << "Unknown";
         break;
      }
      return os;
   }

   std::ostream& operator<<(std::ostream& os, SegmentCollision collision)
   {
      switch(collision)
      {
         case SegmentCollision::Attic:
         os << "Attic";
         break;
         case SegmentCollision::Bottom:
         os << "Bottom";
         break;
         case SegmentCollision::Left:
         os << "Left";
         break;
         case SegmentCollision::No:
         os << "No";
         break;
         case SegmentCollision::Right:
         os << "Right";
         break;
         case SegmentCollision::Roof:
         os << "Roof";
         break;
         case SegmentCollision::Top:
         os << "Top";
         default:
         os << "Unknown";
         break;
      }
      return os;
   }

   Segment::Segment(float aX, float aY, float bX, float bY,
      SegmentSurface surface/* = SegmentSurface::Ordinary*/)
      : math::Segment<float>(aX, aY, bX, bY), mSurface(surface) {}

   Segment::Segment(const math::Vector2<float>& a, const math::Vector2<float>& b,
      SegmentSurface surface/* = SegmentSurface::Ordinary*/)
      : math::Segment<float>(a, b), mSurface(surface) {}
      
   SegmentSurface Segment::getSurface() const
   {
      return mSurface;
   }

   void Segment::setSurface(SegmentSurface surface)
   {
      mSurface = surface;
   }
}