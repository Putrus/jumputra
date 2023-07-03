#pragma once

#include "Character.h"

#include "../../../Common/inc/Eventable.h"
#include "../../../Common/inc/Updatable.h"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class World final : public sf::Drawable, public Eventable, public Updatable
   {
   public:
      World(const Context& context);

      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
      bool event(const sf::Event& event) override;
      bool update(const sf::Time& dt) override;

   private:
      void loadJson();

      std::vector<Character> mCharacters;
      std::vector<physics::StaticObject> mObjects;
   };
}