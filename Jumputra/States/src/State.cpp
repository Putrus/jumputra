#include "../inc/State.h"
#include "../inc/StateStack.h"

namespace jp::state
{
   State::State(std::shared_ptr<StateStack> stack, const Context& context) : mStack(stack), mContext(context) {}

   const Context& State::getContext() const
   {
      return mContext;
   }

   void State::pushState(StateID id)
   {
      mStack->pushState(id);
   }

   void State::popState()
   {
      mStack->popState();
   }
}