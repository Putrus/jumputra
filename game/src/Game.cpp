#include "../inc/Game.hpp"

#include "../../logic/inc/SegmentsLoader.hpp"
#include "../../logic/inc/WindsLoader.hpp"

namespace jp::game
{
   Game::Game(const logic::Properties& properties) : logic::Engine(properties)
   {
      addCharacter(std::make_shared<Character>(math::Rect(50.f, 50.f, 24.f, 24.f), mProperties, mSegments, mWinds));
      logic::SegmentsLoader loader;
      addSegment(std::make_shared<Segment>(0.f, 100.f, 100.f, 100.f));
   }

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