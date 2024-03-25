#include "../inc/Engine.hpp"

#include <chrono>

namespace jp::logic
{
   constexpr float NANOSECONDS_IN_ONE_SECOND = 1000000000;

   Engine::Engine(const std::string& dataPath/* = "data"*/)
   {
      mProperties.loadFromFile(dataPath + "/jsons/properties.json");
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

   void Engine::update(float dt) {}

   void Engine::draw() const {}

   void Engine::event() {}
}