#include "../inc/Wind.hpp"

#include <iostream>

namespace jp::graphics
{
   Wind::Wind(const sf::FloatRect& rect) : mSprite(*mTexture)
   {
      //temporary, sf::Sprite default constructor is deleted...
      std::unique_ptr<sf::Image> img = std::make_unique<sf::Image>(sf::Vector2u(static_cast<unsigned int>(rect.size.x * 2),
         static_cast<unsigned int>(rect.size.y)), sf::Color::Transparent);
      unsigned int yInterspace = 32;
      unsigned int xInterspace = yInterspace * 2;
      for (unsigned int y = 0; y < img->getSize().y; y += yInterspace)
      {
         unsigned int xStart = y % xInterspace == 0 ? 0 : yInterspace;
         for (unsigned int x = xStart; x < img->getSize().x; x += xInterspace)
         {
            img->setPixel(sf::Vector2u(x, y), sf::Color::White);
         }
      }
      if (!mTexture->loadFromImage(*img))
      {
         throw std::runtime_error("jp::graphics::Wind::createTexture - Failed to load texture from image");
      }

      mSprite = sf::Sprite(*mTexture);
      mSprite.setPosition(sf::Vector2f(rect.position.x - mTexture->getSize().x, rect.position.y));
   }

   Wind::Wind(const nlohmann::json& json)
      : Wind(sf::FloatRect(sf::Vector2f(json["rect"]["left"], json["rect"]["top"]), sf::Vector2f(json["rect"]["width"], json["rect"]["height"]))) {}

   void Wind::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(mSprite);
   }

   void Wind::move(const sf::Vector2f& offset)
   {
      sf::Vector2f newPosition = mSprite.getPosition();
      newPosition += offset;
      if (newPosition.x > 0)
      {
         newPosition.x -= mTexture->getSize().x;
      }
      else
      {
         newPosition.x += mTexture->getSize().x;
      }
      mSprite.setPosition(newPosition);
   }
}