#pragma once

#include "../../graphic/inc/Segment.hpp"
#include "../../logic/inc/Segment.hpp"

namespace jp::game
{
   class Segment : public sf::Drawable
   {
   public:
      Segment(const std::shared_ptr<logic::Segment>& logicSegment);

      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

   private:
      graphic::Segment mGraphicSegment;
      std::shared_ptr<logic::Segment> mLogicSegment;
   };
}