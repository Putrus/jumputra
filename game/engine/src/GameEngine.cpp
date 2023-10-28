#include "../inc/GameEngine.hpp"
#include "../inc/PlatformsManager.hpp"

#include "../../physics/inc/DiagonalPlatform.hpp"
#include "../../physics/inc/HorizontalPlatform.hpp"
#include "../../physics/inc/VerticalPlatform.hpp"

#include <chrono>

namespace jp::game::engine
{
    GameEngine::GameEngine() : mPlatformsManager("data/platforms.json"), mPropertiesManager("data/properties.json"),
        mPhysicsEngine(new physics::PhysicsEngine(mPropertiesManager.physicsProperties, mPlatformsManager.load(),
            std::make_shared<physics::Wind>(mPropertiesManager.physicsProperties.wind)))
    {}

    void GameEngine::run()
    {
        //to do, now for testing
        auto begin = std::chrono::steady_clock::now();
        auto end = std::chrono::steady_clock::now();
        float time = 0.f;
        //60 frames per second
        float UPDATE_NANOSECONDS = 16666666;
        while(true)
        {
            end = std::chrono::steady_clock::now();
            time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
            begin = std::move(end);
            while (time > UPDATE_NANOSECONDS)
            {
                time -= UPDATE_NANOSECONDS;
                update(time);
            }
        }
    }

    void GameEngine::addCharacter(const math::Vector2<float>& position)
    {
        auto entity = std::make_shared<physics::Entity>(math::Rect<float>(position,
            mPropertiesManager.physicsProperties.entitySize));
        mCharacters.push_back(Character(entity, mPropertiesManager.characterProperties));
        mPhysicsEngine->addEntity(std::move(entity));
    }

    void GameEngine::update(float dt)
    {
        mPhysicsEngine->update(dt);
    }
}