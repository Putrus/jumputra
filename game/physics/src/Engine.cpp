#include "../inc/Engine.hpp"

namespace jp::game::physics
{
    void Engine::update(float dt)
    {
        mWind->update(dt);
        for(auto& body : mBodies)
        {

        }
    }
}