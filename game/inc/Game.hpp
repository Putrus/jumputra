#pragma once

#include "../inc/Character.hpp"
#include "../inc/Segment.hpp"
#include "../inc/Wind.hpp"

#include "../../logic/inc/Engine.hpp"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class Game : public logic::Engine, public sf::Drawable
   {
   public:
      Game();
      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

      void addCharacter(const std::shared_ptr<Character>& character);
      void addSegment(const std::shared_ptr<Segment>& segment);
      void addWind(const std::shared_ptr<Wind>& wind);

   private:
      std::vector<std::shared_ptr<sf::Drawable>> mDrawables;
   };
}