#pragma once

#include "State.hpp"

#include "../../logic/inc/Updatable.hpp"

#include <memory>
#include <vector>

namespace jp::game
{
   class StateStack : public sf::Drawable, public Eventable, public logic::Updatable
   {
   public:
      StateStack(StateID id, Context& context);

      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
      void event(const std::optional<sf::Event>& event) override;
      void update(float dt) override;

      void popState();
      void pushState(StateID id);
      void updateLanguage();

   private:
      void applyPendingActions();

      struct PendingAction
      {
         enum class Type : unsigned long long
         {
            Pop = 0,
            Push
         } type;
         StateID stateId = StateID::None;
      };

      Context& mContext;

      std::vector<PendingAction> mPendingActions;
      std::vector<std::shared_ptr<State>> mStack;
   };
}