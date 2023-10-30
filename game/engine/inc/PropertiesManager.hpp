#pragma once

#include "../inc/Character.hpp"
#include "../../physics/inc/Physics.hpp"

namespace jp::game::engine
{
    struct APropertiesManager
    {
        virtual void load() = 0;
        virtual void save() = 0;

        engine::Character::Properties characterProperties;
        physics::Properties physicsProperties;
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