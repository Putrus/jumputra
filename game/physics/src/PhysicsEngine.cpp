#include "../inc/PhysicsEngine.hpp"

namespace jp::game::physics
{
    PhysicsEngine::PhysicsEngine(const PhysicsProperties& properties, std::vector<std::shared_ptr<Character>>&& characters,
        std::vector<std::shared_ptr<Platform>>&& platforms, std::vector<std::shared_ptr<Wind>>&& winds)
        : mProperties(properties), mCharacters(std::move(characters)), mPlatforms(std::move(platforms)), mWinds(std::move(winds)),
            mCharacterUpdater(new CharacterUpdater(mProperties)), mWindUpdater(new WindUpdater())
    {}

    void PhysicsEngine::addCharacter(const std::shared_ptr<Character>& entity)
    {
        mCharacters.push_back(entity);
    }

    void PhysicsEngine::addCharacter(std::shared_ptr<Character>&& entity)
    {
        mCharacters.push_back(std::move(entity));
    }
    
    void PhysicsEngine::update(float dt)
    {
        updateWinds(dt);
        updateCharacters(dt);
    }

    const std::vector<std::shared_ptr<Platform>>& PhysicsEngine::getPlatforms() const
    {
        return mPlatforms;
    }

    const std::vector<std::shared_ptr<Wind>>& PhysicsEngine::getWinds() const
    {
        return mWinds;
    }

    void PhysicsEngine::updateCharacters(float dt)
    {
        for (auto characterIt = mCharacters.begin(); characterIt != mCharacters.end(); ++characterIt)
        {
            mCharacterUpdater->setEntity(*characterIt);
            //remove entity if it only exists in the physics engine
            if (characterIt->use_count() == 2)
            {
                characterIt = mCharacters.erase(characterIt);
                if (characterIt == mCharacters.end())
                {
                    break;
                }
            }
            for (const auto& wind : mWinds)
            {
                mCharacterUpdater->updatePosition(dt, *wind);
                mCharacterUpdater->updateVelocity(dt, *wind);
            }
            for (const auto& platform : mPlatforms)
            {
                if (platform->getSegment().a.y > mCharacterUpdater->getUpdatedEntity().getPosition().y + mProperties.checkCollisionDistance)
                {
                    continue;
                }

                if (platform->getSegment().a.y < mCharacterUpdater->getUpdatedEntity().getPosition().y - mProperties.checkCollisionDistance)
                {
                    break;
                }
                mCharacterUpdater->handlePlatformCollision(*platform);
            }
            mCharacterUpdater->handleNoCollision();
            mCharacterUpdater->update();
        }
    }

    void PhysicsEngine::updateWinds(float dt)
    {
        for (auto windIt = mWinds.begin(); windIt != mWinds.end(); ++windIt)
        {
            mWindUpdater->setWind(*windIt);
            if (windIt->use_count() == 2)
            {
                windIt = mWinds.erase(windIt);
                if (windIt == mWinds.end())
                {
                    break;
                }
            }
            mWindUpdater->update(dt);
        }
    }
}