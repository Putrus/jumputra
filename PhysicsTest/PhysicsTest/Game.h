#pragma once

#include "Object.h"
#include "Segment.h"

#include <SFML/Graphics.hpp>

#include <vector>

class Game final
{
public:
   Game();

   void run();

private:
   void processEvents();
   void render();
   void update(sf::Time& dt);

   sf::RenderWindow mWindow;
   sf::Time mTimePerFrame;

   std::vector<jp::physics::PlatformSegment> mSegments;
   std::vector<jp::physics::Platform> mPlatforms;
   std::vector<Object> mObjects;
};
