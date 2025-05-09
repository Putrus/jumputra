#pragma once

#include "../../math/inc/Rect.hpp"
#include "../../math/inc/Vector2.hpp"

#include <SFML/Graphics.hpp>

namespace jp::graphics
{
   class Character : public sf::Drawable
   {
   public:
      Character(const math::Vector2<float> &position, const math::Vector2<float> &size);
      Character(const math::Rect<float>& rect);
      Character(const nlohmann::json& json);

      void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

   protected:
      void setFlattening(float flattening);
      void setPosition(float x, float y);
      void setPosition(const math::Vector2<float>& position);
      void setRect(const math::Rect<float>& rect);
      void setRectTop(float y);
      void setRectBottom(float y);
      void setRectLeft(float x);
      void setRectRight(float x);

   private:
      sf::RectangleShape mShape;
      float mFlattening = 0.f;
   };
}