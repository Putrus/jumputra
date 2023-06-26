#include "ResourceManager.h"

namespace jumputra
{
   struct Context
   {
      std::shared_ptr<sf::RenderWindow> window;
      std::shared_ptr<FontManager> fontManager;
   };

   class StateStack;

   class State
   {
   public:
      virtual bool handleEvent(const sf::Event& event) = 0;
      virtual void render() = 0;
      virtual bool update(const sf::Time& dt) = 0;

   private:
      std::shared_ptr<StateStack> stack;
   };
}