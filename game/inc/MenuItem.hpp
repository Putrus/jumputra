#pragma once

#include "../../logic/inc/Selectable.hpp"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class MenuItem : public sf::Drawable, public logic::Selectable
   {
   public:
      MenuItem(const sf::Vector2f& position,
         const std::string& text, const sf::Font& font,
         const sf::Color& deselectColor = sf::Color::White,
         const sf::Color& selectColor = sf::Color::Yellow);

      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

      void deselect() override;
      void select() override;

      std::string getTextString() const;

   private:
      sf::Text mText;
      sf::Color mSelectColor;
      sf::Color mDeselectColor;
   };
}