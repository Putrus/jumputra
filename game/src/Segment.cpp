#include "../inc/Segment.hpp"

namespace jp::game
{
   Segment::Segment(float aX, float aY, float bX, float bY,
      logic::SegmentSurface surface/* = logic::SegmentSurface::Ordinary*/)
      : mLogicSegment(logic::Segment::create(aX, aY, bX, bY, surface)),
      graphics::Segment(aX, aY, bX, bY)
   {
      switch (mLogicSegment->getSurface())
      {
      case logic::SegmentSurface::Ordinary:
         setFillColor(sf::Color::White);
         break;
      case logic::SegmentSurface::Slippery:
         setFillColor(sf::Color::Cyan);
         break;
      case logic::SegmentSurface::Sticky:
         setFillColor(sf::Color::Blue);
         break;
      default:
         throw std::invalid_argument("jp::game::Segment::Segment - Wrong segment surface");
         break;
      }
   }

   Segment::Segment(const math::Vector2<float>& a, const math::Vector2<float>& b,
      logic::SegmentSurface surface/* = logic::SegmentSurface::Ordinary*/)
      : Segment(a.x, a.y, b.x, b.y, surface) {}
   
   std::shared_ptr<Segment> Segment::create(const math::Vector2<float>& a, const math::Vector2<float>& b,
      logic::SegmentSurface surface/* = logic::SegmentSurface::Ordinary*/)
   {
      return std::make_shared<Segment>(a, b, surface);
   }

   std::shared_ptr<logic::Segment> Segment::getLogicSegment() const
   {
      return mLogicSegment;
   }
}