#include "../inc/GameEngine.hpp"

#include "../../physics/inc/DiagonalPlatform.hpp"
#include "../../physics/inc/HorizontalPlatform.hpp"
#include "../../physics/inc/VerticalPlatform.hpp"

#include <chrono>

namespace jp::game::engine
{
    GameEngine::GameEngine() : mCharacterProperties(math::Vector2<float>(24.f, 24.f), math::Vector2<float>(500.f, 1000.f), math::Vector2<float>(500.f, 1000.f), 200.f)
    {
        physics::PhysicsProperties properties(0.4f, 600.f, 700.f, 100.f, 1000.f, 0.4f, 0.f);
        properties.setWindAcceleration(math::Vector2<float>(100.f, 0.f));
        auto entity = std::make_shared<physics::Entity>(math::Rect<float>(10.f, 20.f, 24.f, 24.f));
        mCharacters.push_back(Character(entity, mCharacterProperties));
        std::vector<std::shared_ptr<physics::Entity>> entities;
        entities.push_back(entity);
        std::vector<std::shared_ptr<physics::Platform>> platforms;
        platforms.push_back(std::make_shared<physics::HorizontalPlatform>(
            math::Segment<float>(1.f, 0.f, 400.f, 0.f), physics::PlatformSurface::Ordinary));
        platforms.push_back(std::make_shared<physics::VerticalPlatform>(
            math::Segment<float>(1.f, 0.f, 1.f, 100.f), physics::PlatformSurface::Ordinary));
        platforms.push_back(std::make_shared<physics::DiagonalPlatform>(
            math::Segment<float>(1.f, 100.f, 50.f, 149.f), physics::PlatformSurface::Ordinary));
        platforms.push_back(std::make_shared<physics::VerticalPlatform>(
            math::Segment<float>(50.f, 149.f, 50.f, 350.f), physics::PlatformSurface::Ordinary));
        platforms.push_back(std::make_shared<physics::HorizontalPlatform>(
            math::Segment<float>(1.f, 350.f, 300.f, 350.f), physics::PlatformSurface::Slippery));
        platforms.push_back(std::make_shared<physics::VerticalPlatform>(
            math::Segment<float>(300.f, 350.f, 300.f, 150.f), physics::PlatformSurface::Ordinary));
        platforms.push_back(std::make_shared<physics::HorizontalPlatform>(
            math::Segment<float>(300.f, 150.f, 400.f, 150.f), physics::PlatformSurface::Ordinary));
        platforms.push_back(std::make_shared<physics::VerticalPlatform>(
            math::Segment<float>(400.f, 150.f, 400.f, 0.f), physics::PlatformSurface::Ordinary));
        auto wind = std::make_shared<physics::Wind>(properties.getWindAcceleration());
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