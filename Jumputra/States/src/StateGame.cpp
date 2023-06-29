#include "../inc/StateGame.h"

namespace jp::state
{
   StateGame::StateGame(StateStack* stack, const Context& context) : State(stack, context)
   {
      shape.setTexture(context.resources.getTexture(res::Texture::Penguin));
      shape.setScale(sf::Vector2f(3.f, 3.f));
      shape.setTextureRect(sf::IntRect(0, 0, 31, 31));
   }

   void StateGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      target.draw(shape);
      for (const auto& s : sprites)
      {
         target.draw(s);
      }
   }

   bool StateGame::event(const sf::Event& event)
   {
      if (event.type == sf::Event::KeyReleased)
      {
         switch (event.key.code)
         {
         case sf::Keyboard::Escape:
            popState();
            pushState(StateID::Menu);
            break;
         case sf::Keyboard::Up:
         case sf::Keyboard::Down:
         case sf::Keyboard::Left:
         case sf::Keyboard::Right:
            speed = { 0.f, 0.f };
            //view.zoom(0.1);
            break;
         case sf::Keyboard::Space:
            for (int i = 0; i < 300; ++i)
            {
               sf::Sprite sprite;
               sprite.setTexture(getContext().resources.getTexture(res::Texture::Penguin));
               int rx = std::rand() % 500 + 5;
               int ry = std::rand() % 500 + 5;
               sprite.setTextureRect(sf::IntRect(0, 0, 31, 31));
               sprite.setPosition(rx, ry);
               sprites.push_back(sprite);
            }
            break;
         }
      }
      else if (event.type == sf::Event::KeyPressed)
      {
         float v = 1.f;
         switch (event.key.code)
         {
         case sf::Keyboard::Up:
            speed.y = -v;
            break;
         case sf::Keyboard::Down:
            speed.y = v;
            break;
         case sf::Keyboard::Left:
            speed.x = -v;
            break;
         case sf::Keyboard::Right:
            speed.x = v;
            break;
         }
      }
      return true;
   }

   bool StateGame::update(const sf::Time& dt)
   {
      shape.move({ speed.x * dt.asMilliseconds(), speed.y * dt.asMilliseconds() });
      return true;
   }
}