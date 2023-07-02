#include "../inc/State.h"
#include "../inc/StateStack.h"

namespace jp::state
{
   State::State(StateStack* stack, const Context& context) : mStack(stack), mContext(context) {}

   void State::pushState(StateID id)
   {
      mStack->pushState(id);
   }

   void State::popState()
   {
      mStack->popState();
   }
}