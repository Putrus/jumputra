#include "../inc/StateMenu.h"

namespace jp::state
{
   MenuText::MenuText(const sf::Vector2f& position, const std::string& text, const sf::Font& font) : sf::Text(text, font)
   {
      setPosition(position);
   }

   StateMenu::StateMenu(StateStack* stack, const Context& context) : State(stack, context)
   {
      const float xPos = mContext.window.getSize().x / 2.f - 30.f;
      float yPos = 50;
      mItems.push_back(MenuText(sf::Vector2f(xPos, yPos), "Play", context.resources.getFont("Pixel")));
      yPos += 50;
      mItems.push_back(MenuText(sf::Vector2f(xPos, yPos), "Creator", context.resources.getFont("Pixel")));
      yPos += 50;
      mItems.push_back(MenuText(sf::Vector2f(xPos, yPos), "Quit", context.resources.getFont("Pixel")));
      updateSelected(0);
   }

   void StateMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
   {
      for (const MenuText& item : mItems)
      {
         target.draw(item, states);
      }
   }

   bool StateMenu::event(const sf::Event& event)
   {
      if (event.type == sf::Event::KeyReleased)
      {
         switch (event.key.code)
         {
         case sf::Keyboard::Up:
            updateSelected(-1);
            break;
         case sf::Keyboard::Down:
            updateSelected(1);
            break;
         case sf::Keyboard::Enter:
            if (mSelected == 2)
            {
               mContext.window.close();
            }
            else if (mSelected == 1)
            {
               popState();
               pushState(StateID::Creator);
            }
            else
            {
               popState();
               pushState(StateID::Game);
            }
            break;
         }
      }
      return true;
   }

   bool StateMenu::update(const sf::Time& dt)
   {
      return true;
   }

   void StateMenu::updateSelected(int val)
   {
      int previousSelected = mSelected;
      mSelected = (mSelected + val) % mItems.size();
      mItems[previousSelected].setFillColor(sf::Color::White);
      mItems[mSelected].setFillColor(sf::Color::Green);
   }
}