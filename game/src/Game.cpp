#include "../inc/Game.hpp"

namespace jp::game
{
   void Game::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
   {
      for (const auto& drawable : mDrawables)
      {
         target.draw(*drawable);
      }
   }

   void Game::addCharacter(const std::shared_ptr<Character>& character)
   {
      mDrawables.push_back(character);
      Engine::addCharacter(character);
   }

   void Game::addSegment(const std::shared_ptr<Segment>& segment)
   {
      mDrawables.push_back(segment);
      Engine::addSegment(segment->getLogicSegment());
   }

   void Game::addWind(const std::shared_ptr<Wind>& wind)
   {
      mDrawables.push_back(wind);
      Engine::addWind(wind);
   }
}