#include "../inc/State.hpp"
#include "../inc/StateStack.hpp"

namespace jp::states
{
   State::State(StateStack* stack) : mStack(stack)
   {
      if (mStack == nullptr)
      {
         throw std::runtime_error("State::State - Stack is nullptr");
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