#pragma once

#include "State.h"

namespace jp::state
{
   class MenuText : public sf::Text
   {
   public:
      MenuText(const sf::Vector2f& position, const std::string& text, const sf::Font& font);
   }; 

   class StateMenu final : public State
   {
   public:
      StateMenu(StateStack* stack, const Context& context);

      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
      bool event(const sf::Event& event) override;
      bool update(const sf::Time& dt) override;

   private:
      void updateSelected(int val);

      std::vector<MenuText> mItems; 
      int mSelected = 0;
   };
}