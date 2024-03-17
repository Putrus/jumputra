#pragma once

#include "State.hpp"

#include "../../inc/Updatable.hpp"

#include <memory>
#include <vector>

namespace jp::game::states
{
   class StateStack : public sf::Drawable, public Eventable, public Updatable
   {
   public:
      StateStack();
      StateStack(StateID id);

      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
      void event(const sf::Event& event) override;
      void update(float dt) override;

      void popState();
      void pushState(StateID id);

   private:
      void applyPendingActions();

      struct PendingAction
      {
         enum class Type : int
         {
            Pop = 0,
            Push
         } type;
         StateID StateID = StateID::None;
      };

      std::vector<PendingAction> mPendingActions;
      std::vector<std::shared_ptr<State>> mStack;
   };
}