#include "../inc/State.hpp"
#include "../inc/StateStack.hpp"

namespace jp::game
{
   State::State(StateStack* stack, Context& context)
      : mStack(stack), mContext(context)
   {
      if (mStack == nullptr)
      {
         throw std::runtime_error("jp::game::State::State - Stack is nullptr");
      }
   }

   void State::popState()
   {
      mStack->popState();
   }

   void State::pushState(StateID id)
   {
      mStack->pushState(id);
   }
}