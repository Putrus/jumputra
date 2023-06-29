#pragma once

#include "State.h"

#include <vector>

namespace jp::state
{
   class StateStack final : public sf::Drawable, public Eventable,
      public Updatable
   {
   public:
      StateStack(const Context& context);

      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
      bool event(const sf::Event& event) override;
      bool update(const sf::Time& dt) override;

      void popState();
      void pushState(StateID id);

   private:
      void applyPendingActions();

      struct PendingAction
      {
         enum class Action : int
         {
            Push = 0,
            Pop = 1
         } action;
         StateID id = StateID::None;
      };

      std::vector<std::shared_ptr<State>> mStack;
      std::vector<PendingAction> mPendingActions;
      Context mContext;
   };
}