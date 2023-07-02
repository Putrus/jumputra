#pragma once

#include <SFML/Graphics.hpp>

namespace jp::game::physics
{
   class StaticObject : public sf::Drawable
   {
   public:
      StaticObject();
      StaticObject(const sf::FloatRect& rect);
      StaticObject(const sf::Vector2f& position, const sf::Vector2f& size);

      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

      sf::FloatRect getRect() const;
      sf::Vector2f getPosition() const;
      sf::Vector2f getSize() const;
      float getLeft() const;
      float getTop() const;
      float getWidth() const;
      float getHeight() const;
      float getRight() const;
      float getBottom() const;

      void setPosition(const sf::Vector2f& position);
      void setSize(const sf::Vector2f& size);
      void setRect(const sf::FloatRect& rect);

   protected:
      void draw(sf::RenderTarget& target, sf::RenderStates states, const sf::Color& color) const;

   private:
      sf::FloatRect mRect;
   };
}