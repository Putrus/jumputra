#pragma once

#include "../../engine/inc/CharacterProperties.hpp"
#include "../../physics/inc/PhysicsProperties.hpp"

namespace jp::game::engine
{
    struct APropertiesManager
    {
        virtual void load() = 0;
        virtual void save() = 0;

        engine::CharacterProperties characterProperties;
        physics::PhysicsProperties physicsProperties;
    };

    class PropertiesManager : public APropertiesManager
    {
    public:
        PropertiesManager(const std::string& filename);
        void load() override;
        void save() override;

    private:
        std::string mFilename;
    };
}