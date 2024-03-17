#pragma once

#include "../../inc/Eventable.hpp"
#include "../../inc/Updatable.hpp"

#include <SFML/Graphics.hpp>

namespace jp::states
{
   class StateStack;

   enum class StateID : int
   {
      None = 0
   };

   class State : public sf::Drawable, public Eventable, public Updatable
   {
   public:
      State(StateStack* stack);

   protected:
      void popState();
      void pushState(StateID id);

   private:
      StateStack* mStack;
   };
}