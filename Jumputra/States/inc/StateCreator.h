#pragma once

#include "State.h"

#include "../../Game/Physics/inc/StaticObject.h"

namespace jp::state
{
   class StateCreator final : public State
   {
   public:
      StateCreator(StateStack* stack, const Context& context);

      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
      bool event(const sf::Event& event) override;
      bool update(const sf::Time& dt) override;

   private:
      void moveView(float offset);
      void resetView();
      void saveJson(int num) const;
      void loadLastJson();

      std::vector<game::physics::StaticObject> mObjects;
      sf::View mView;
      float mViewVerticalOffset = 0.f;

      bool mSelected = false;
      sf::RectangleShape mSelectedRect;
   };
}