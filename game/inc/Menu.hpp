#pragma once

#include "../inc/Eventable.hpp"
#include "../inc/MenuItem.hpp"

#include "../../logic/inc/SelectionManager.hpp"

namespace jp::game
{
   class Menu : public sf::Drawable, public logic::SelectionManager
   {
   public:
      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

      void addItem(const std::string& text, const sf::Font& font,
         const sf::Color& deselectColor = sf::Color::White,
         const sf::Color& selectColor = sf::Color::Yellow);
      void setItemText(int id, const std::string& text);

      std::string getSelectedTextString() const;
      const std::vector<std::shared_ptr<MenuItem>>& getItems() const;

   private:
      std::vector<std::shared_ptr<MenuItem>> mItems;
      sf::Vector2f position = { 10.f, 10.f };
      float offset = 20.f;
   };
}