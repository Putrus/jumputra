#pragma once

#include "States.h"

#include "../../Common/inc/Context.h"
#include "../../Common/inc/Eventable.h"
#include "../../Common/inc/Updatable.h"

namespace jp::state
{
   class StateStack;

   class State : public sf::Drawable, public Eventable, public Updatable
   {
   public:
      State(StateStack* stack, const Context& context);

      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
      virtual bool event(const sf::Event& event) override = 0;
      virtual bool update(const sf::Time& dt) override = 0;

   protected:
      const Context& getContext() const;

      void pushState(StateID id);
      void popState();

   private:
      StateStack* mStack;
      Context mContext;
   };
}