#include "../inc/EntityUpdater.hpp"

#include "../../math/inc/Function.hpp"

namespace jp::game::physics
{
    EntityUpdater::EntityUpdater(const PhysicsProperties& properties)
        : Updater<PhysicsProperties>(properties)
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
                leftPlatformCollision(platform.getSegment().b.x);
                break;
            }
            case PlatformCollision::Right:
            {
                rightPlatformCollision(platform.getSegment().a.x);
                break;
            }
            case PlatformCollision::Top:
            {
                topPlatformCollision(platform.getSegment().b.y, platform.getSurface());
                break;
            }
            case PlatformCollision::Bottom:
            {
                bottomPlatformCollision(platform.getSegment().a.y, platform.getSurface());
                break;
            }
            case PlatformCollision::Attic:
            {
                //to do
                float slope = (platform.getSegment().b.y - platform.getSegment().a.y) / (platform.getSegment().b.x - platform.getSegment().a.x);
                float intercept = platform.getSegment().b.y - slope * platform.getSegment().b.x;
                if (slope > 0.f)
                {
                    mUpdatedEntity.setRectTop(std::min(platform.getSegment().b.y,
                        std::max(mUpdatedEntity.getRect().left, mUpdatedEntity.getRect().getRight()) + slope * intercept));
                }
                else
                {
                    mUpdatedEntity.setRectTop(std::min(platform.getSegment().a.y, (std::min(mUpdatedEntity.getRect().left,
                        mUpdatedEntity.getRect().getRight()) + slope * intercept) * slope));
                }

                if (getProperties().gravity < 0.f)
                {
                    mUpdatedEntity.setVelocityX(slope * mUpdatedEntity.getVelocity().y);
                }
                else
                {
                    mUpdatedEntity.setVelocity(math::Vector2<float>());
                }
                mUpdatedEntity.setState(EntityState::Sledding);
                break;
            }
            case PlatformCollision::Roof:
            {
                //to do
                float slope = (platform.getSegment().b.y - platform.getSegment().a.y) /
                    (platform.getSegment().b.x - platform.getSegment().a.x);
                float intercept = platform.getSegment().b.y - slope * platform.getSegment().b.x;
                if (slope > 0.f)
                {
                    mUpdatedEntity.setRectBottom(std::max(platform.getSegment().a.y, std::min(mUpdatedEntity.getRect().left,
                        mUpdatedEntity.getRect().getRight()) + slope * intercept));
                }
                else
                {
                    mUpdatedEntity.setRectBottom(std::max(platform.getSegment().b.y, (std::max(mUpdatedEntity.getRect().left,
                        mUpdatedEntity.getRect().getRight()) + slope * intercept) * slope));
                }

                if (getProperties().gravity > 0.f)
                {
                    mUpdatedEntity.setVelocityX(slope * mUpdatedEntity.getVelocity().y);
                }
                else
                {
                    mUpdatedEntity.setVelocity(math::Vector2<float>());
                }
                mUpdatedEntity.setState(EntityState::Sledding);
            }
            default:
            break;
        }
    }

    void EntityUpdater::handleNoCollision()
    {
        //if there is no collision (entity is still in the air) reset acceleration
        if (mUpdatedEntity.getState() == EntityState::Falling ||
            mUpdatedEntity.getState() == EntityState::Flying)
        {
            mUpdatedEntity.setAcceleration(0.f);
        }
    }

    void EntityUpdater::update()
    {
        *mEntity = mUpdatedEntity;
    }

    void EntityUpdater::updatePosition(float dt, const Wind& wind)
    {
        //distance/spatium = v * t + a * t^2 / 2 
        math::Vector2<float> distance = getResultantVelocity(*mEntity) * dt +
            getResultantAcceleration(*mEntity, wind) * dt * dt / 2.f;
        mUpdatedEntity.move(distance);
    }

    void EntityUpdater::updateVelocity(float dt, const Wind& wind)
    {
        math::Vector2<float> updatedVelocity = mEntity->getVelocity() + getResultantAcceleration(*mEntity, wind) * dt;
        math::Vector2<float> updatedAcceleration = mEntity->getAcceleration();
        if (mEntity->getState() != EntityState::Running)
        {
            updatedVelocity.x += mEntity->getRunVelocity();
            mUpdatedEntity.setRunVelocity(0.f);
        }

        if (updatedVelocity.x < 1.f && updatedVelocity.x > -1.f)
        {
            updatedAcceleration.x = 0.f;
            updatedVelocity.x = 0.f;
        }

        if (updatedVelocity.y >= getProperties().fallVelocity)
        {
            mUpdatedEntity.setState(EntityState::Falling);
            updatedVelocity.y = getProperties().fallVelocity;
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

    void EntityUpdater::sideBounce()
    {
        mUpdatedEntity.setAccelerationX(-mUpdatedEntity.getAcceleration().x);
        mUpdatedEntity.setVelocityX(-mEntity->getVelocity().x * getProperties().bounceFactor);
    }

    void EntityUpdater::topBounce()
    {
        mUpdatedEntity.setState(EntityState::Flying);
        mUpdatedEntity.setVelocityX(mEntity->getVelocity().x * getProperties().bounceFactor);
    }

    void EntityUpdater::topBottomCollision(bool top, PlatformSurface platformSurface)
    {
        bool landing = top ? getProperties().gravity < 0.f : getProperties().gravity > 0.f;
        mUpdatedEntity.setVelocityY(0.f);
        if (landing)
        {
            switch (platformSurface)
            {
            case PlatformSurface::Ordinary:
                mUpdatedEntity.setVelocityX(0.f);
                break;
            case PlatformSurface::Slippery:
                mUpdatedEntity.setAccelerationX(-math::sign(mUpdatedEntity.getVelocity().x) * getProperties().friction);
                break;
            case PlatformSurface::Sticky:
                mUpdatedEntity.setVelocityX(0.f);
                mUpdatedEntity.setRunVelocity(0.f);
                mUpdatedEntity.setRectLeft(mEntity->getRect().left);
                break;
            default:
                mUpdatedEntity.setState(mEntity->getState());
                break;
            }

            if (mEntity->getState() == EntityState::Falling)
            {
                mUpdatedEntity.setState(EntityState::Dying);
            }
            else if (mEntity->getState() == EntityState::Flying ||
                mEntity->getState() == EntityState::Stopping)
            {
                switch (platformSurface)
                {
                case PlatformSurface::Ordinary:
                    mUpdatedEntity.setState(EntityState::Standing);
                    break;
                case PlatformSurface::Slippery:
                    mUpdatedEntity.setState(EntityState::Sliding);
                    break;
                case PlatformSurface::Sticky:
                    mUpdatedEntity.setState(EntityState::Sticking);
                    break;
                default:
                    mUpdatedEntity.setState(mEntity->getState());
                    break;
                }
            }
            else
            {
                mUpdatedEntity.setState(mEntity->getState());
            }
        }
        else
        {
            topBounce();
        }
    }

    void EntityUpdater::leftPlatformCollision(float x)
    {
        mUpdatedEntity.setRectLeft(x);
        sideBounce();
    }

    void EntityUpdater::rightPlatformCollision(float x)
    {
        mUpdatedEntity.setRectRight(x);
        sideBounce();
    }

    void EntityUpdater::topPlatformCollision(float y, PlatformSurface platformSurface)
    {
        mUpdatedEntity.setRectTop(y);
        topBottomCollision(true, platformSurface);
    }

    void EntityUpdater::bottomPlatformCollision(float y, PlatformSurface platformSurface)
    {
        mUpdatedEntity.setRectBottom(y);
        topBottomCollision(false, platformSurface);
    }

    math::Vector2<float> EntityUpdater::getResultantAcceleration(const Entity& entity, const Wind& wind) const
    {
        //entityA + windV * factor + gravityA
        math::Vector2<float> resultantAcceleration = entity.getAcceleration() +
            math::Vector2<float>(0.f, getProperties().gravity);
        if (mUpdatedEntity.getRect().top >= wind.getStartPosition() &&
            mUpdatedEntity.getRect().top <= wind.getEndPosition())
        {
            resultantAcceleration += wind.getVelocity() * getProperties().wind.factor;
        }
        return resultantAcceleration;
    }

    math::Vector2<float> EntityUpdater::getResultantVelocity(const Entity& entity) const
    {
        //entityV + runV
        return entity.getVelocity() + math::Vector2<float>(entity.getRunVelocity(), 0.f);
    }
}