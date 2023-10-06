#include "../inc/GameEngine.hpp"

#include "../physics/inc/HorizontalPlatform.hpp"
#include "../physics/inc/VerticalPlatform.hpp"

#include <chrono>

namespace jp::game::engine
{
    GameEngine::GameEngine()
    {
        physics::PhysicsProperties properties(0.4f, 600.f, 700.f, 100.f, 1000.f, 0.4f, 0.f);
        auto entity = std::make_shared<physics::Entity>(math::Rect<float>(10.f, 20.f, 24.f, 24.f)); 
        mCharacters.push_back(Character(entity));
        std::vector<std::shared_ptr<physics::Entity>> entities;
        entities.push_back(entity);
        std::vector<std::shared_ptr<physics::Platform>> platforms;
        platforms.push_back(std::make_shared<physics::HorizontalPlatform>(
            math::Segment<float>(1.f, 100.f, 50.f, 100.f), physics::PlatformSurface::Ordinary));
        platforms.push_back(std::make_shared<physics::VerticalPlatform>(
            math::Segment<float>(50.f, 100.f, 50.f, 350.f), physics::PlatformSurface::Ordinary));
        platforms.push_back(std::make_shared<physics::HorizontalPlatform>(
            math::Segment<float>(50.f, 350.f, 300.f, 350.f), physics::PlatformSurface::Ordinary));
        platforms.push_back(std::make_shared<physics::VerticalPlatform>(
            math::Segment<float>(300.f, 350.f, 300.f, 150.f), physics::PlatformSurface::Ordinary));
        platforms.push_back(std::make_shared<physics::HorizontalPlatform>(
            math::Segment<float>(300.f, 150.f, 400.f, 150.f), physics::PlatformSurface::Ordinary));
        auto wind = std::make_shared<physics::Wind>(0.f);
        mPhysicsEngine = std::make_unique<physics::PhysicsEngine>(
            std::move(properties), std::move(entities), std::move(platforms),
            std::move(wind));
        //to do, now code is for testing
    }

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

    void GameEngine::update(float dt)
    {
        mPhysicsEngine->update(dt);
    }
}