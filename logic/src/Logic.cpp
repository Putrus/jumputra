#include "../inc/Logic.hpp"

#include <chrono>

constexpr float NANOSECONDS_IN_SECOND = 1000000000;

namespace jp::game::logic
{
   Logic::Logic(const ::jp::game::Properties& properties)
      : mProperties(properties.logic), mPhysics(std::make_unique<physics::Physics>(properties.physics))
   {
      std::vector<std::shared_ptr<physics::Segment>> segments = 
   }

   void Logic::run()
   {
      auto begin = std::chrono::steady_clock::now();
      float time = 0.f;
      while (true)
      {
         auto end = std::chrono::steady_clock::now();
         time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / NANOSECONDS_IN_SECOND;
         begin = std::move(end);
         while (time >= mProperties.secondsPerFrame)
         {
            time -= mProperties.secondsPerFrame;
            update(mProperties.secondsPerFrame);
         }
         event();
         draw();
      }
   }

   void Logic::update(float dt)
   {
      mPhysics->update(dt);
   }

   void Logic::addCharacter(const std::shared_ptr<Character>& character)
   {
      mCharacters.push_back(character);
      mPhysics->addBody(character);
   }

   void Logic::draw() const {}

   void Logic::event() {}
}