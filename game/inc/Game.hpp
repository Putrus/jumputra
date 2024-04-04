#pragma once

#include "Character.hpp"
#include "Context.hpp"
#include "Eventable.hpp"
#include "Properties.hpp"
#include "Segment.hpp"
#include "Wind.hpp"

#include "../../logic/inc/Engine.hpp"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class Game : public logic::Engine, public sf::Drawable, public Eventable
   {
   public:
      Game(Context& context);
      virtual ~Game();

      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
      void event(const sf::Event& event) override;
      void update(float dt) override;

      void addCharacter(const std::shared_ptr<Character>& character);
      void addSegment(const std::shared_ptr<Segment>& segment);
      void addWind(const std::shared_ptr<Wind>& wind);

   private:
      void resetView();
      void updateView();

      Context& mContext;
      std::vector<std::shared_ptr<sf::Drawable>> mDrawables;
      size_t mControlledCharacterId = 0;
      size_t mFollowedCharacterId = 0;
   };
}