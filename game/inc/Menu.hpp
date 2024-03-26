#pragma once

#include "../inc/MenuItem.hpp"

#include "../../logic/inc/SelectionManager.hpp"

namespace jp::game
{
   class Menu : public sf::Drawable, public logic::SelectionManager
   {
   public:
      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

      void addItem(const std::shared_ptr<MenuItem>& item);

      std::string getSelectedTextString() const;

   private:
      std::vector<std::shared_ptr<MenuItem>> mItems;
   };
}