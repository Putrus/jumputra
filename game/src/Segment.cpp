#include "../inc/Segment.hpp"

namespace jp::game
{
   Segment::Segment(const std::shared_ptr<logic::Segment>& logicSegment) : mLogicSegment(logicSegment),
      graphic::Segment(logicSegment->a.x, logicSegment->a.y, logicSegment->b.x, logicSegment->b.y)
   {
      switch (logicSegment->getSurface())
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
         throw std::invalid_argument("Segment::Segment - Wrong segment surface");
         break;
      }
   }
}