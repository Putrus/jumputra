#pragma once

#include <SFML/Graphics.hpp>

#include <nlohmann/json.hpp>

namespace jp::graphics
{
   class Wind : public sf::Drawable
   {
   public:
      Wind(const sf::FloatRect& rect);
      Wind(const nlohmann::json& json);

      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

   protected:
      void move(const sf::Vector2f& offset);

      std::unique_ptr<sf::Texture> mTexture = std::make_unique<sf::Texture>();
      sf::Sprite mSprite;
   };
}