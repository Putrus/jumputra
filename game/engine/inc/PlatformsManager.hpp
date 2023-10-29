#pragma once

#include "../../physics/inc/Platform.hpp"

#include <vector>

namespace jp::game::engine
{
    struct IPlatformsManager
    {
        virtual std::vector<std::shared_ptr<physics::Platform>> load() = 0;
    };

    class PlatformsManager : public IPlatformsManager
    {
    public:
        PlatformsManager(const std::string& filename);
        std::vector<std::shared_ptr<physics::Platform>> load() override;

    private:
        std::shared_ptr<physics::Platform> createPlatform(const math::Vector2<float>& a,
            const math::Vector2<float>& b, physics::PlatformSurface surface);

        std::string mFilename;
    };
}