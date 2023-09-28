#include "../inc/EntityUpdater.hpp"

namespace jp::game::engine::physics
{
    EntityUpdater::EntityUpdater(const jp::game::engine::physics::Properties& properties, const jp::game::engine::physics::Wind& wind)
    : Updater(properties), mWind(wind)
    {}

    void EntityUpdater::handlePlatformCollision(const Platform* platform)
    {
        if (platform == nullptr)
        {
            return;
        }

        PlatformCollision platformCollision = platform->checkCollision(mEntity->getRect(), mUpdatedEntity.getRect());
        switch(platformCollision)
        {
            case PlatformCollision::No:
            break;
            case PlatformCollision::Left:
            {
                leftPlatformCollision(platform->getSegment().b.x);
                break;
            }
            case PlatformCollision::Right:
            {
                rightPlatformCollision(platform->getSegment().a.x);
                break;
            }
            case PlatformCollision::Top:
            {
                topPlatformCollision(platform->getSegment().b.y, platform->getSurface());
                break;
            }
            case PlatformCollision::Bottom:
            {
                bottomPlatformCollision(platform->getSegment().a.y, platform->getSurface());
                break;
            }
            case PlatformCollision::Attic:
            {
                std::cout << "Collision attic!" << std::endl;
                break;
            }
            case PlatformCollision::Roof:
            {
                std::cout << "Collision roof!" << std::endl;
                break;
            }
            default:
            break;
        }
    }

    void EntityUpdater::update()
    {
        *mEntity = mUpdatedEntity;
    }

    void EntityUpdater::updatePosition(float dt)
    {
        mUpdatedEntity.move((mEntity->getVelocity() + mEntity->getSlideVelocity()) * dt + math::Vector2<float>(mWind.getVelocity() * 
            getProperties().getWindFactor() + mEntity->getSlideAcceleration(), getProperties().getGravity()) * dt * dt / 2.f);
    }

    void EntityUpdater::updateVelocity(float dt)
    {
        mUpdatedEntity.setSlideVelocity(mEntity->getSlideVelocity() + mEntity->getSlideAcceleration() * dt);
        if (mUpdatedEntity.getSlideVelocity() < 1.f)
        {
            mUpdatedEntity.setSlideVelocity(0.f);
            mUpdatedEntity.setSlideAcceleration(0.f);
        }
        mUpdatedEntity.setVelocity(mUpdatedEntity.getVelocity() +
            (math::Vector2<float>(mWind.getVelocity() * 
            getProperties().getWindFactor(), getProperties().getGravity())) * dt);
    }

    const Entity& EntityUpdater::getUpdatedEntity() const
    {
        return mUpdatedEntity;
    }

    void EntityUpdater::setEntity(std::shared_ptr<Entity> entity)
    {
        mEntity = entity;
        mUpdatedEntity = *entity;
    }

    void EntityUpdater::bounce()
    {
        if (mEntity->getState() == EntityState::Flying ||
            mEntity->getState() == EntityState::Sliding)
        {
            mUpdatedEntity.setVelocityX(-mEntity->getVelocity().x * getProperties().getBounceFactor());
        }
    }

    void EntityUpdater::leftPlatformCollision(float x)
    {
        mUpdatedEntity.setRectLeft(x);
        bounce();
    }

    void EntityUpdater::rightPlatformCollision(float x)
    {
        mUpdatedEntity.setRectRight(x);
        bounce();
    }

    void EntityUpdater::land(bool top, PlatformSurface platformSurface)
    {
        bool landing = top ? getProperties().getGravity() < 0.f : getProperties().getGravity() > 0.f;
        if (landing)
        {
            if (mEntity->getState() == EntityState::Running)
            {
                return;
            }

            if (platformSurface == PlatformSurface::Slippery)
            {
                mUpdatedEntity.setState(EntityState::Sliding);
                if (mEntity->getVelocity().x != 0.f)
                {
                    float resultantVelocity = mUpdatedEntity.getVelocity().x + mUpdatedEntity.getSlideVelocity();
                    mUpdatedEntity.setSlideVelocity(resultantVelocity);
                    mUpdatedEntity.setSlideAcceleration(getProperties().getFriction() * (resultantVelocity / std::abs(resultantVelocity)));
                }
            }
            else
            {
                mUpdatedEntity.setState(mEntity->getState() == EntityState::Falling ? EntityState::Dying : EntityState::Standing);
            }
            mUpdatedEntity.setVelocityX(0.f);
        }
        else
        {
            mUpdatedEntity.setState(EntityState::Flying);
        }
    }


    void EntityUpdater::topPlatformCollision(float y, PlatformSurface platformSurface)
    {
        mUpdatedEntity.setRectTop(y);
        land(true, platformSurface);
    }

    void EntityUpdater::bottomPlatformCollision(float y, PlatformSurface platformSurface)
    {
        mUpdatedEntity.setRectBottom(y);
        land(false, platformSurface);
    }
}