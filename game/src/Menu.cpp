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

   void Menu::addItem(const std::string& text, const sf::Font& font,
      const sf::Color& deselectColor/* = sf::Color::White*/,
      const sf::Color& selectColor/* = sf::Color::Yellow*/)
   {
      std::shared_ptr<MenuItem> newItem = std::make_shared<MenuItem>(position, text, font, deselectColor, selectColor);
      position.y += newItem->getCharacterSize() + offset;
      mItems.push_back(newItem);
      addSelectable(newItem);
      setSelected(0);
   }

   void Menu::setItemText(int id, const std::string& text)
   {
      mItems.at(id)->setTextString(text);
   }

   std::string Menu::getSelectedTextString() const
   {
      if (getSelected() < mItems.size())
      {
         return mItems[getSelected()]->getTextString();
      }
      return "";
   }

   const std::vector<std::shared_ptr<MenuItem>>& Menu::getItems() const
   {
      return mItems;
   }
}