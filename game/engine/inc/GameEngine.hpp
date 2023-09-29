#pragma once

#include "Character.hpp"

#include "../physics/inc/PhysicsEngine.hpp"

namespace jp::game::engine
{
    class GameEngine
    {
    public:
        GameEngine();
        virtual void run();

    protected:
        void update(float dt);

        std::unique_ptr<physics::PhysicsEngine> mPhysicsEngine;
        std::vector<Character> mCharacters;
    };
}