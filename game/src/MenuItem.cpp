#include "../inc/MenuItem.hpp"
#include <iostream>
namespace jp::game
{
   MenuItem::MenuItem(const sf::Vector2f& position,
      const std::string& text, const sf::Font& font,
      const sf::Color& deselectColor/* = sf::Color::White*/,
      const sf::Color& selectColor/* = sf::Color::Yellow*/)
      : mText(font, text), mDeselectColor(deselectColor), mSelectColor(selectColor)
   {  
      mText.setPosition(position);
      mText.setFillColor(deselectColor);
   }

   void MenuItem::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
   {
      target.draw(mText);
   }

   void MenuItem::deselect()
   {
      mText.setFillColor(mDeselectColor);
      Selectable::deselect();
   }

   void MenuItem::select()
   {
      mText.setFillColor(mSelectColor);
      Selectable::select();
   }

   std::string MenuItem::getTextString() const
   {
      return mText.getString();
   }

   unsigned int MenuItem::getCharacterSize() const
   {
      return mText.getCharacterSize();
   }
}