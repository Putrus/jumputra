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

   void Menu::addItem(const std::shared_ptr<MenuItem>& item)
   {
      mItems.push_back(item);
      addSelectable(item);
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