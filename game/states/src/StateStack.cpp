#include "../inc/StateStack.hpp"

namespace jp::game::states
{
   StateStack::StateStack() {}

   StateStack::StateStack(StateID startState)
   {
      pushState(startState);
   }

   void StateStack::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
   {
      if (!mStack.empty())
      {
         target.draw(*mStack.back(), states);
      }
   }

   void StateStack::event(const sf::Event& event)
   {
      if (!mStack.empty())
      {
         mStack.back()->event(event);
      }
      applyPendingActions();
   }

   void StateStack::update(float dt)
   {
      if (!mStack.empty())
      {
         mStack.back()->update(dt);
      }
      applyPendingActions();
   }

   void StateStack::popState()
   {
      mPendingActions.push_back({ PendingAction::Type::Pop });
   }

   void StateStack::pushState(StateID id)
   {
      mPendingActions.push_back({ PendingAction::Type::Push, id });
   }

   void StateStack::applyPendingActions()
   {
      for (const auto& pendingAction : mPendingActions)
      {
         switch (pendingAction.type)
         {
         case PendingAction::Type::Pop:
            mStack.pop_back();
            break;
         case PendingAction::Type::Push:
            switch (pendingAction.StateID)
            {
            default:
               throw std::runtime_error("StateStack::applyPendingActions - Wrong stack id");
               break;
            }
            break;
         default:
            throw std::runtime_error("StateStack::applyPendingActions - Wrong pending action");
            break;
         }
      }
      mPendingActions.clear();
   }
}