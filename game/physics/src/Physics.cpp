#include "../inc/Physics.hpp"

namespace jp::game::physics
{
    Physics::Physics(const Properties& properties, std::vector<std::shared_ptr<Character>>&& characters,
        std::vector<std::shared_ptr<Platform>>&& platforms, std::vector<std::shared_ptr<Wind>>&& winds)
        : mProperties(properties), mCharacters(std::move(characters)), mPlatforms(std::move(platforms)), mWinds(std::move(winds)),
            mCharacterUpdater(new CharacterUpdater(mProperties)), mWindUpdater(new WindUpdater())
    {}

    void Physics::addCharacter(const std::shared_ptr<Character>& character)
    {
        mCharacters.push_back(character);
    }

    void Physics::addCharacter(std::shared_ptr<Character>&& character)
    {
        mCharacters.push_back(std::move(character));
    }
    
    void Physics::update(float dt)
    {
        updateWinds(dt);
        updateCharacters(dt);
    }

    const std::vector<std::shared_ptr<Character>>& Physics::getCharacters() const
    {
        return mCharacters;
    }

    const std::vector<std::shared_ptr<Platform>>& Physics::getPlatforms() const
    {
        return mPlatforms;
    }

    const std::vector<std::shared_ptr<Wind>>& Physics::getWinds() const
    {
        return mWinds;
    }

    void Physics::updateCharacters(float dt)
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
                continue;
            }
            auto windIt = std::find_if(mWinds.begin(), mWinds.end(),
                [characterIt](const auto& wind)
                {
                    return characterIt->get()->getRect().insersects(wind->getRect());
                });
            if (windIt != mWinds.end())
            {
                mCharacterUpdater->updatePosition(dt, windIt->get());
                mCharacterUpdater->updateVelocity(dt, windIt->get());
            }
            else
            {
                mCharacterUpdater->updatePosition(dt);
                mCharacterUpdater->updateVelocity(dt);
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

    void Physics::updateWinds(float dt)
    {
        for (auto windIt = mWinds.begin(); windIt != mWinds.end(); ++windIt)
        {
            mWindUpdater->setWind(*windIt);
            //remove entity if it only exists in the physics engine
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