#pragma once

#include "../inc/Context.hpp"
#include "../inc/Eventable.hpp"

#include "../../logic/inc/Updatable.hpp"

#include <SFML/Graphics.hpp>

namespace jp::game
{
   class StateStack;

   enum class StateID : unsigned long long
   {
      None = 0,
      Game,
      Language,
      MainMenu,
      Pause,
      Win,
      WorldChoice
   };

   class State : public sf::Drawable, public Eventable, public logic::Updatable
   {
   public:
      State(StateStack* stack, Context& context);

   protected:
      void popState();
      void pushState(StateID id);

      Context& mContext;

   private:
      StateStack* mStack;
   };
}