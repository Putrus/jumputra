#include "../inc/StateGame.h"
#include "../inc/StateMenu.h"
#include "../inc/StateStack.h"

namespace jp::state
{
   StateStack::StateStack(const Context& context) : mContext(context) {}

   void StateStack::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      for (const auto& state : mStack)
      {
         target.draw(*state, states);
      }
   }

   bool StateStack::event(const sf::Event& event)
   {
      for (auto it = mStack.rbegin(); it != mStack.rend(); ++it)
      {
         if (!it->get()->event(event))
         {
            return false;
         }
      }
      applyPendingActions();
      return true;
   }

   bool StateStack::update(const sf::Time& dt)
   {
      for (auto it = mStack.rbegin(); it != mStack.rend(); ++it)
      {
         if (!it->get()->update(dt))
         {
            return false;
         }
      }
      applyPendingActions();
      return true;
   }

   void StateStack::popState()
   {
      mPendingActions.push_back({ PendingAction::Action::Pop });
   }

   void StateStack::pushState(StateID id)
   {
      mPendingActions.push_back({ PendingAction::Action::Push, id});
   }

   void StateStack::applyPendingActions()
   {
      for (const auto& action : mPendingActions)
      {
         switch (action.action)
         {
         case PendingAction::Action::Pop:
            mStack.pop_back();
            break;
         case PendingAction::Action::Push:
            switch (action.id)
            {
            case StateID::Menu:
               mStack.push_back(std::make_shared<StateMenu>(this, mContext));
               break;
            case StateID::Game:
               mStack.push_back(std::make_shared<StateGame>(this, mContext));
               break;
            }
            break;
         }
      }
      mPendingActions.clear();
   }
}