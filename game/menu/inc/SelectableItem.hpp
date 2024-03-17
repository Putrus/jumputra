#pragma once

#include <SFML/Graphics.hpp>

namespace jp::game::menu
{
   class SelectableItem : public sf::Drawable
   {
   public:
      SelectableItem(const sf::Vector2f& position,
         const std::string& text, const sf::Font& font,
         const sf::Color& deselectColor = sf::Color::White,
         const sf::Color& selectColor = sf::Color::Yellow);

      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

      void deselect();
      void select();

      bool isSelected() const;

      std::string getTextString() const;

   private:
      sf::Text mText;
      sf::Color mSelectColor;
      sf::Color mDeselectColor;
   };
}