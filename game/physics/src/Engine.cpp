#include "../inc/Engine.hpp"

namespace jp::game::physics
{
    void Engine::update(float dt)
    {
        mParameters->update(dt);
        
    }
}