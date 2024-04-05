#pragma once

#include "../../graphic/inc/Character.hpp"
#include "../../logic/inc/Character.hpp"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class Character : public graphic::Character, public logic::Character
   {
   public:
      Character(const math::Vector2<float> &position, const math::Vector2<float> &size,
         const logic::Properties &properties,
         const std::vector<std::shared_ptr<logic::Segment>>& segments,
         const std::vector<std::shared_ptr<logic::Wind>>& winds);
      Character(const math::Rect<float>& rect,
         const logic::Properties &properties,
         const std::vector<std::shared_ptr<logic::Segment>>& segments,
         const std::vector<std::shared_ptr<logic::Wind>>& winds);
      
      void setPosition(float x, float y) override;
      void setPosition(const math::Vector2<float>& position) override;
      void setRect(const math::Rect<float>& rect) override;
      void setRectTop(float y) override;
      void setRectBottom(float y) override;
      void setRectLeft(float x) override;
      void setRectRight(float x) override;
      void setState(logic::CharacterState state) override;
   };
}