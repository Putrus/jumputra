#include <SFML/Graphics.hpp>

namespace jumputra
{
   class MenuText : public sf::Text
   {
   public:
      MenuText(const sf::Vector2f& position, const std::string& text, const sf::Font& font);
   }; 

   class Menu final : public sf::Drawable
   {
   public:
      Menu(const sf::Vector2u& windowSize, const sf::Font& font);

      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
      std::vector<MenuText> items; 
   };
}