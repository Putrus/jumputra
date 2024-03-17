#pragma once

#include "../inc/State.hpp"

#include "../../menu/inc/SelectableItem.hpp"

namespace jp::game::states
{
   class StateMenu final : public State
   {
   public:
      StateMenu(StateStack* stack);

      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
      void event(const sf::Event& event) override;
      void update(float dt) override;

   private:
      void changeSelected(int direction);
      void performSelected();

      int mSelected = 0;
      std::vector<std::unique_ptr<menu::SelectableItem>> mItems;
   };
}