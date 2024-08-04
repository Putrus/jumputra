#include "../inc/Greedy.hpp"

namespace jp::agents
{
   void Greedy::control(const std::shared_ptr<logic::Engine>& engine)
   {
      if (o)
      {
      engine->removeCharacter(0);
      o = false;
      }
   }
}