#include "../inc/Menu.h"

namespace jumputra
{
   MenuText::MenuText(const sf::Vector2f& position, const std::string& text, const sf::Font& font) : sf::Text(text, font)
   {
      setPosition(position);
   }

   Menu::Menu(const sf::Vector2u& windowSize, const sf::Font& font)
   {
      const float xPos = windowSize.x / 2.f - 30.f;
      float yPos = 50;
      items.push_back(MenuText(sf::Vector2f(xPos, yPos), "Play", font));
      yPos += 50;
      items.push_back(MenuText(sf::Vector2f(xPos, yPos), "Quit", font));
   }

   void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      for (const MenuText& item : items)
      {
         target.draw(item, states);
      }
   }
}