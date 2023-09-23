#include "../inc/EntityUpdater.hpp"

namespace jp::game::physics
{
    EntityUpdater::EntityUpdater(std::shared_ptr<Entity> entity, const Properties& properties, const Wind& wind)
    : mEntity(entity), mUpdatedEntity(*entity), Updater(properties), mWind(wind)
    {}

    void EntityUpdater::handlePlatformCollision(const Platform& platform)
    {
        PlatformCollision platformCollision = platform.checkCollision(mEntity->getRect(), mUpdatedEntity.getRect());
        switch(platformCollision)
        {
            case PlatformCollision::No:
            break;
            case PlatformCollision::Left:
            {
                bounceLeft(platform.getSegment().b.x);
                break;
            }
            case PlatformCollision::Right:
            {
                bounceRight(platform.getSegment().a.x);
                break;
            }
            case PlatformCollision::Top:
            {
                mUpdatedEntity.setRectTop(platform.getSegment().b.y);
                if (getProperties().getGravity() < 0.f)
                {
                    if (mEntity->getState() == EntityState::Running)
                    {
                        break;
                    }

                    if (platform.getSurface() == PlatformSurface::Slippery)
                    {
                        mUpdatedEntity.setState(EntityState::Sliding);
                    }
                    else
                    {
                        mUpdatedEntity.setState(mEntity->getState() == EntityState::Falling ? EntityState::Dying : EntityState::Standing);
                        mUpdatedEntity.setVelocityX(0.f);
                    }
                }
                else
                {
                    mUpdatedEntity.setState(EntityState::Flying);
                }
                break;
            }
            case PlatformCollision::Bottom:
            {
                mUpdatedEntity.setRectBottom(platform.getSegment().a.y);
                mUpdatedEntity.setVelocityY(0.f);
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

    void EntityUpdater::updatePosition(float dt)
    {
        //to do
    }

    void EntityUpdater::updateVelocity(float dt)
    {
        mUpdatedEntity.setSlideVelocity(mEntity->getSlideVelocity() + mEntity->getSlideAcceleration());
        if (mUpdatedEntity.getSlideVelocity() < 1.f)
        {
            mUpdatedEntity.setSlideVelocity(0.f);
            mUpdatedEntity.setSlideAcceleration(0.f);
        }
        mUpdatedEntity.setVelocity(mUpdatedEntity.getVelocity() +
            (math::Vector2<float>(mWind.getVelocity() *
            getProperties().getWindFactor(), getProperties().getGravity())) * dt);
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

    void EntityUpdater::bounceLeft(float x)
    {
        mUpdatedEntity.setRectLeft(x);
        bounce();
    }

    void EntityUpdater::bounceRight(float x)
    {
        mUpdatedEntity.setRectRight(x);
        bounce();
    }
}