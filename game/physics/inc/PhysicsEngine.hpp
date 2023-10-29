#pragma once

#include "CharacterUpdater.hpp"
#include "PhysicsProperties.hpp"
#include "Platform.hpp"
#include "WindUpdater.hpp"

#include <map>
#include <memory>
#include <vector>

namespace jp::game::physics
{
    class PhysicsEngine
    {
    public:
        PhysicsEngine(const PhysicsProperties& properties, std::vector<std::shared_ptr<Character>>&& entities,
            std::vector<std::shared_ptr<Platform>>&& platforms, std::vector<std::shared_ptr<Wind>>&& winds);

        void addCharacter(const std::shared_ptr<Character>& character);
        void addCharacter(std::shared_ptr<Character>&& character);
        void update(float dt);

        const std::vector<std::shared_ptr<Character>>& getCharacters() const;
        const std::vector<std::shared_ptr<Platform>>& getPlatforms() const;
        const std::vector<std::shared_ptr<Wind>>& getWinds() const;

    private:
        void updateCharacters(float dt);
        void updateWinds(float dt);

        const PhysicsProperties& mProperties;

        std::vector<std::shared_ptr<Character>> mCharacters;
        std::vector<std::shared_ptr<Platform>> mPlatforms;
        std::vector<std::shared_ptr<Wind>> mWinds;

        std::unique_ptr<CharacterUpdater> mCharacterUpdater;
        std::unique_ptr<WindUpdater> mWindUpdater;
    };
}