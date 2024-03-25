#pragma once

#include "../inc/Eventable.hpp"

#include "../../logic/inc/Updatable.hpp"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class StateStack;

   enum class StateID : int
   {
      None = 0,
      Game,
      Menu
   };

   class State : public sf::Drawable, public Eventable, public logic::Updatable
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