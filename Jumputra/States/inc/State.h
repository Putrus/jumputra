#pragma once

#include "States.h"

#include "../../Common/inc/Eventable.h"
#include "../../Common/inc/Resources.h"
#include "../../Common/inc/Updatable.h"

namespace jp::state
{
   struct Context
   {
      std::shared_ptr<sf::RenderWindow> window;
      std::shared_ptr<res::FontManager> fontManager;
   };

   class StateStack;

   class State : public sf::Drawable, public Eventable, public Updatable
   {
   public:
      State(std::shared_ptr<StateStack> stack, const Context& context);

      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
      virtual bool event(const sf::Event& event) override = 0;
      virtual bool update(const sf::Time& dt) override = 0;

   protected:
      const Context& getContext() const;

      void pushState(StateID id);
      void popState();

   private:
      std::shared_ptr<StateStack> mStack;
      Context mContext;
   };
}