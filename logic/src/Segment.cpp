#include "../inc/Segment.hpp"

#include "../inc/DiagonalSegment.hpp"
#include "../inc/HorizontalSegment.hpp"
#include "../inc/VerticalSegment.hpp"

namespace jp::logic
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
         break;
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

   void Segment::fromJson(const nlohmann::json& json)
   {
      mSurface = static_cast<SegmentSurface>(json.at("surface"));
      math::Segment<float>::fromJson(json);
   }

   nlohmann::json Segment::toJson() const
   {
      nlohmann::json json = math::Segment<float>::toJson();
      json["surface"] = static_cast<unsigned long long>(mSurface);
      return json;
   }

   std::shared_ptr<Segment> Segment::create(float aX, float aY, float bX, float bY,
      SegmentSurface surface/* = SegmentSurface::Ordinary*/)
   {
      math::Segment<float> segment(aX, aY, bX, bY);
      if (segment.isDiagonal())
      {
         return std::make_shared<DiagonalSegment>(aX, aY, bX, bY, surface);
      }
      else if (segment.isHorizontal())
      {
         return std::make_shared<HorizontalSegment>(aX, aY, bX, bY, surface);
      }
      else if (segment.isVertical())
      {
         return std::make_shared<VerticalSegment>(aX, aY, bX, bY, surface);
      }
      else
      {
         std::stringstream ss;
         ss << "jp::logic::Segment::create - Failed to create segment, wrong arguments a = (" << aX << ", " << aY << "), b = (" << bX << ", " << bY << ")";
         throw std::invalid_argument(ss.str());
      }
   }

   std::shared_ptr<Segment> Segment::create(const math::Vector2<float>& a, const math::Vector2<float>& b,
      SegmentSurface surface/* = SegmentSurface::Ordinary*/)
   {
      return Segment::create(a.x, a.y, b.x, b.y);
   }
      
   SegmentSurface Segment::getSurface() const
   {
      return mSurface;
   }

   void Segment::setSurface(SegmentSurface surface)
   {
      mSurface = surface;
   }
}