#pragma once

#include "../inc/SelectableItem.hpp"
#include "../inc/State.hpp"

namespace jp::game
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
      std::vector<std::unique_ptr<SelectableItem>> mItems;
   };
}