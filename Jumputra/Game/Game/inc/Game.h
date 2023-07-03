#pragma once

#include "World.h"

#include "../../../Common/inc/Eventable.h"
#include "../../../Common/inc/Updatable.h"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class Game : public sf::Drawable, public Eventable, public Updatable
   {
   public:
      Game(const Context& context);
      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
      bool event(const sf::Event& event) override;
      bool update(const sf::Time& dt) override;

   private:
      World mWorld;
   };
}