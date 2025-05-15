#pragma once

#include "Character.hpp"
#include "Context.hpp"
#include "Goal.hpp"
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

      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
      void event(const std::optional<sf::Event>& event) override;
      void update(float dt) override;

      void addCharacter(const math::Rect<float>& rect) override;
      void addCharacterCopy(const logic::Character& character) override;
      void removeCharacter(const std::shared_ptr<logic::Character>& character) override;
      void removeAllCharacters() override;
      void removeAllCharactersExcept(const std::shared_ptr<logic::Character>& character) override;
      
      void load();
      void save() const;
      void resetView();

   private:
      void updateView();
      void removeRedundantDrawables();
      void humanCharacterControl(const std::optional<sf::Event>& event);
      void changeView(float y);

      void setGoal(const nlohmann::json& json) override;
      void addCharacter(const nlohmann::json& json) override;
      void addSegment(const math::Vector2<float>& a, const math::Vector2<float>& b,
         logic::SegmentSurface surface = logic::SegmentSurface::Ordinary) override;
      void addWind(const nlohmann::json& json) override;

      std::string makeSavePath() const;

      Context& mContext;
      std::vector<std::shared_ptr<sf::Drawable>> mDrawables;
      bool mViewFollowCharacter = true;
   };
}