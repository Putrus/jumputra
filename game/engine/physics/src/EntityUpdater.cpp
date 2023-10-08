#include "../inc/EntityUpdater.hpp"

#include "../../math/inc/Function.hpp"

namespace jp::game::engine::physics
{
    EntityUpdater::EntityUpdater(const PhysicsProperties& properties, const jp::game::engine::physics::Wind& wind)
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
        //distance/spatium = v * t + a * t^2 / 2 
        math::Vector2<float> distance = getResultantVelocity(*mEntity) * dt +
            getResultantAcceleration(*mEntity) * dt * dt / 2.f;
        mUpdatedEntity.move(distance);
    }

    void EntityUpdater::updateVelocity(float dt)
    {
        math::Vector2<float> updatedVelocity = mEntity->getVelocity() + getResultantAcceleration(*mEntity) * dt;
        math::Vector2<float> updatedAcceleration = mEntity->getAcceleration();
        if (mEntity->getState() != EntityState::Running)
        {
            updatedVelocity += mEntity->getControlledVelocity();
            mUpdatedEntity.setControlledVelocity(math::Vector2<float>(0.f));
        }

        if (updatedVelocity.x < 1.f && updatedVelocity.x > -1.f)
        {
            updatedAcceleration.x = 0.f;
            updatedVelocity.x = 0.f;
        }
        else
        {
            if (mEntity->getState() == EntityState::Dying || 
                mEntity->getState() == EntityState::Running ||
                mEntity->getState() == EntityState::Sliding ||
                mEntity->getState() == EntityState::Squatting)
            {
                updatedAcceleration.x = -math::sign(updatedVelocity.x) * getProperties().getFriction();
            }
        }

        if (updatedVelocity.y >= getProperties().getFallVelocity())
        {
            mUpdatedEntity.setState(EntityState::Falling);
            updatedVelocity.y = getProperties().getFallVelocity();
        }

        mUpdatedEntity.setAcceleration(updatedAcceleration); 
        mUpdatedEntity.setVelocity(updatedVelocity);
    }

    const Entity& EntityUpdater::getUpdatedEntity() const
    {
        return mUpdatedEntity;
    }

    void EntityUpdater::setEntity(std::shared_ptr<Entity> entity)
    {
        mEntity = entity;
        mUpdatedEntity = *entity;
        mUpdatedEntity.setState(mEntity->getState() == EntityState::Falling ? EntityState::Falling : EntityState::Flying);
    }

    void EntityUpdater::bounce()
    {
        if (mEntity->getState() == EntityState::Flying ||
            mEntity->getState() == EntityState::Sliding)
        {
            if (mUpdatedEntity.getControlledVelocity() != math::Vector2<float>())
            {
                //to do error handling
                std::cout << "Something wrong! Controlled velocity isn't empty!" << std::endl;
            }
            std::cout << "EntityUpdater::bounce" << std::endl;
            mUpdatedEntity.setAccelerationX(-mUpdatedEntity.getAcceleration().x);
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
        mUpdatedEntity.setVelocityY(0.f);
        if (landing)
        {
            if (mEntity->getState() == EntityState::Running)
            {
                mUpdatedEntity.setState(EntityState::Running);
                return;
            }

            if (platformSurface == PlatformSurface::Slippery)
            {
                if (mEntity->getState() == EntityState::Squatting)
                {
                    mUpdatedEntity.setState(EntityState::Squatting); 
                }    
                else
                {
                    mUpdatedEntity.setState(EntityState::Sliding);
                }
                return;
            }
            else if (mEntity->getState() == EntityState::Falling)
            {
                mUpdatedEntity.setState(EntityState::Dying);
            }
            else if (mEntity->getState() == EntityState::Flying)
            {
                mUpdatedEntity.setState(EntityState::Standing);
            }
            else
            {
                mUpdatedEntity.setState(mEntity->getState());
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

    math::Vector2<float> EntityUpdater::getResultantAcceleration(const Entity& entity) const
    {
        return entity.getAcceleration() + mWind.getVelocity() * getProperties().getWindFactor() +
            math::Vector2<float>(0.f, getProperties().getGravity());
    }

    math::Vector2<float> EntityUpdater::getResultantVelocity(const Entity& entity) const
    {
        return entity.getControlledVelocity() + entity.getVelocity();
    }
}