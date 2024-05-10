#include "../inc/Menu.hpp"

namespace jp::game
{
   void Menu::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
   {
      for (const auto& item : mItems)
      {
         target.draw(*item);
      }
   }

   void Menu::addItem(const std::string& text, const sf::Font& font)
   {
      std::shared_ptr<MenuItem> newItem = std::make_shared<MenuItem>(position, text, font);
      position.y += newItem->getCharacterSize() + offset;
      mItems.push_back(newItem);
      addSelectable(newItem);
      setSelected(0);
   }

   std::string Menu::getSelectedTextString() const
   {
      if (getSelected() < mItems.size())
      {
         return mItems[getSelected()]->getTextString();
      }
      return "";
   }
}