#pragma once

#include "Character.hpp"

#include "../physics/inc/PhysicsEngine.hpp"

namespace jp::game::engine
{
    class GameEngine
    {
    public:
        GameEngine();
        void run();

    private:
        void update(float dt);
        
        std::unique_ptr<physics::PhysicsEngine> mPhysicsEngine;
        std::vector<Character> mCharacters;
    };
}