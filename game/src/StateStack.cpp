#include "../inc/StateGame.hpp"
#include "../inc/StateLanguage.hpp"
#include "../inc/StateMainMenu.hpp"
#include "../inc/StateStack.hpp"
#include "../inc/StateWin.hpp"
#include "../inc/StateWorldChoice.hpp"

namespace jp::game
{
   StateStack::StateStack(StateID id, Context& context) : mContext(context)
   {
      pushState(id);
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
            switch (pendingAction.stateId)
            {
            case StateID::Game:
               mStack.push_back(std::make_shared<StateGame>(this, mContext));
               break;
            case StateID::Language:
               mStack.push_back(std::make_shared<StateLanguage>(this, mContext));
               break;
            case StateID::MainMenu:
               mStack.push_back(std::make_shared<StateMainMenu>(this, mContext));
               break;
            case StateID::Win:
               mStack.push_back(std::make_shared<StateWin>(this, mContext));
               break;
            case StateID::WorldChoice:
               mStack.push_back(std::make_shared<StateWorldChoice>(this, mContext));
               break;
            default:
               throw std::runtime_error("jp::game::StateStack::applyPendingActions - Wrong stack id");
               break;
            }
            break;
         default:
            throw std::runtime_error("jp::game::StateStack::applyPendingActions - Wrong pending action");
            break;
         }
      }
      mPendingActions.clear();
   }
}