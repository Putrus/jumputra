#include "../inc/Segment.hpp"

namespace jp::game
{
   Segment::Segment(const std::shared_ptr<logic::Segment>& logicSegment) : mLogicSegment(logicSegment),
      mGraphicSegment(logicSegment->a.x, logicSegment->a.y, logicSegment->b.x, logicSegment->b.y)
   {
      switch (logicSegment->getSurface())
      {
      case logic::SegmentSurface::Ordinary:
         mGraphicSegment.setFillColor(sf::Color::White);
         break;
      case logic::SegmentSurface::Slippery:
         mGraphicSegment.setFillColor(sf::Color::Cyan);
         break;
      case logic::SegmentSurface::Sticky:
         mGraphicSegment.setFillColor(sf::Color::Blue);
         break;
      default:
         throw std::invalid_argument("Segment::Segment - Wrong segment surface");
         break;
      }
   }

   void Segment::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
   {
      target.draw(mGraphicSegment);
   }
}