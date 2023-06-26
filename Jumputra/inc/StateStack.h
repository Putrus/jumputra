#include "State.h"

#include <stack>

namespace jumputra
{
   class StateStack : private sf::NonCopyable
   {
   private:
      std::stack<State> stack;
   };
}