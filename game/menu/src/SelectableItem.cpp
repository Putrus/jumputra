#include "../inc/SelectableItem.hpp"

namespace jp::game::menu
{
   SelectableItem::SelectableItem(const sf::Vector2f& position,
      const std::string& text, const sf::Font& font,
      const sf::Color& deselectColor/* = sf::Color::White*/,
      const sf::Color& selectColor/* = sf::Color::Yellow*/)
      : mText(font, text)
   {  
      mText.setPosition(position);
      mText.setFillColor(deselectColor);
   }

   void SelectableItem::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
   {
      target.draw(mText);
   }

   void SelectableItem::deselect()
   {
      mText.setFillColor(mDeselectColor);
   }

   void SelectableItem::select()
   {
      mText.setFillColor(mSelectColor);
   }

   bool SelectableItem::isSelected() const
   {
      return mText.getFillColor() == mSelectColor;
   }

   std::string SelectableItem::getTextString() const
   {
      return mText.getString();
   }
}