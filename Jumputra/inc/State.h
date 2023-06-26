#include <SFML/Graphics.hpp>

class State
{
public:
   virtual bool handleEvent(const sf::Event& event) = 0;
   virtual void render() = 0;
   virtual bool update(const sf::Time& dt) = 0;
};