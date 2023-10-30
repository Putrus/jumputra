#pragma once

#include "Character.hpp"
#include "PlatformsManager.hpp"
#include "PropertiesManager.hpp"

#include "../../physics/inc/Physics.hpp"

namespace jp::game::engine
{
    class Engine
    {
    public:
        Engine();
        virtual void run();

        void addCharacter(const math::Vector2<float>& position);
        void removeAllCharacters();
        void removeCharacter(size_t id);

    protected:
        void update(float dt);

        std::vector<Character> mCharacters;
        PlatformsManager mPlatformsManager;
        PropertiesManager mPropertiesManager;
        std::unique_ptr<physics::Physics> mPhysics;
    };
}