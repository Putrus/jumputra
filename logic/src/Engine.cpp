#include "../inc/Engine.hpp"

#include <chrono>

namespace jp::logic
{
   constexpr float NANOSECONDS_IN_ONE_SECOND = 1000000000;

   Engine::Engine(const std::string& dataPath/* = "data"*/)
   {
      if (!mProperties.loadFromFile(dataPath + "/jsons/properties.json"))
      {
         throw std::invalid_argument("Engine::Engine - Failed to load properties");
      }
   }

   Engine::Engine(const Properties& properties) : mProperties(properties) {}

   void Engine::run()
   {
      auto begin = std::chrono::steady_clock::now();
      float time = 0.f;
      while (true)
      {
         auto end = std::chrono::steady_clock::now();
         time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / NANOSECONDS_IN_ONE_SECOND;
         begin = std::move(end);
         while (time >= mProperties.secondsPerUpdate)
         {
            time -= mProperties.secondsPerUpdate;
            update(mProperties.secondsPerUpdate);
         }
         draw();
         event();
      }
   }

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

   void Engine::draw() const {}

   void Engine::event() {}
}