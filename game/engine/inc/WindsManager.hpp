#pragma once

namespace jp::game::engine
{
    struct IWindsManager
    {
        virtual std::vector<std::shared_ptr<physics::Platform>> load() = 0;
    };

    class WindsManager : public IWindsManager
    {
    public:
        WindsManager(const std::string& filename);
        std::vector<std::shared_ptr<physics::Wind>> load() override;
    }
}