#include "../inc/Engine.hpp"

#include <chrono>

namespace jp::logic
{
   Engine::Engine(const logic::Properties& properties) 
      : mProperties(properties), Runnable(mProperties.logic.secondsPerUpdate) {}

   void Engine::update(float dt)
   {
      for (auto& wind : mWinds)
      {
         wind->update(dt);
      }
      
      for (auto& character : mCharacters)
      {
         character->update(dt);
      }
   }

   void Engine::draw() {}

   void Engine::event() {}

   void Engine::addCharacter(const std::shared_ptr<Character>& character)
   {
      mCharacters.push_back(character);
   }

   void Engine::addSegment(const std::shared_ptr<Segment>& segment)
   {
      mSegments.push_back(segment);
   }

   void Engine::addWind(const std::shared_ptr<Wind>& wind)
   {
      mWinds.push_back(wind);
   }
}