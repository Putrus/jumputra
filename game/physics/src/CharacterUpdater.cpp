#include "../inc/CharacterUpdater.hpp"

#include "../../math/inc/Function.hpp"

namespace jp::game::physics
{
    CharacterUpdater::CharacterUpdater(const Properties& properties)
        : mPhysicsProperties(properties)
    {}

    void CharacterUpdater::handlePlatformCollision(const Platform& platform)
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

                if (mPhysicsProperties.gravity < 0.f)
                {
                    mUpdatedEntity.setVelocityX(slope * mUpdatedEntity.getVelocity().y);
                }
                else
                {
                    mUpdatedEntity.setVelocity(math::Vector2<float>());
                }
                mUpdatedEntity.setState(CharacterState::Sledding);
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

                if (mPhysicsProperties.gravity > 0.f)
                {
                    mUpdatedEntity.setVelocityX(slope * mUpdatedEntity.getVelocity().y);
                }
                else
                {
                    mUpdatedEntity.setVelocity(math::Vector2<float>());
                }
                mUpdatedEntity.setState(CharacterState::Sledding);
            }
            default:
            break;
        }
    }

    void CharacterUpdater::handleNoCollision()
    {
        //if there is no collision (entity is still in the air) reset acceleration
        if (mUpdatedEntity.getState() == CharacterState::Falling ||
            mUpdatedEntity.getState() == CharacterState::Flying)
        {
            mUpdatedEntity.setAcceleration(0.f);
        }
    }

    void CharacterUpdater::update()
    {
        *mEntity = mUpdatedEntity;
    }

    void CharacterUpdater::updatePosition(float dt, const Wind* wind/* = nullptr*/)
    {
        //distance/spatium = v * t + a * t^2 / 2 
        math::Vector2<float> distance = getResultantVelocity(*mEntity) * dt +
            getResultantAcceleration(*mEntity, wind) * dt * dt / 2.f;
        mUpdatedEntity.move(distance);
    }

    void CharacterUpdater::updateVelocity(float dt, const Wind* wind/* = nullptr*/)
    {
        math::Vector2<float> updatedVelocity = mEntity->getVelocity() + getResultantAcceleration(*mEntity, wind) * dt;
        math::Vector2<float> updatedAcceleration = mEntity->getAcceleration();
        if (mEntity->getState() != CharacterState::Running)
        {
            updatedVelocity.x += mEntity->getRunVelocity();
            mUpdatedEntity.setRunVelocity(0.f);
        }

        if (updatedVelocity.x < 1.f && updatedVelocity.x > -1.f)
        {
            updatedAcceleration.x = 0.f;
            updatedVelocity.x = 0.f;
        }

        if (updatedVelocity.y >= mPhysicsProperties.fallVelocity)
        {
            mUpdatedEntity.setState(CharacterState::Falling);
            updatedVelocity.y = mPhysicsProperties.fallVelocity;
        }

        mUpdatedEntity.setAcceleration(updatedAcceleration); 
        mUpdatedEntity.setVelocity(updatedVelocity);
    }

    const Character& CharacterUpdater::getUpdatedEntity() const
    {
        return mUpdatedEntity;
    }

    void CharacterUpdater::setEntity(std::shared_ptr<Character> entity)
    {
        mEntity = entity;
        mUpdatedEntity = *entity;
        mUpdatedEntity.setState(mEntity->getState() == CharacterState::Falling ? CharacterState::Falling : CharacterState::Flying);
    }

    void CharacterUpdater::sideBounce()
    {
        mUpdatedEntity.setAccelerationX(-mUpdatedEntity.getAcceleration().x);
        mUpdatedEntity.setVelocityX(-mEntity->getVelocity().x * mPhysicsProperties.bounceFactor);
    }

    void CharacterUpdater::topBounce()
    {
        mUpdatedEntity.setState(CharacterState::Flying);
        mUpdatedEntity.setVelocityX(mEntity->getVelocity().x * mPhysicsProperties.bounceFactor);
    }

    void CharacterUpdater::topBottomCollision(bool top, PlatformSurface platformSurface)
    {
        bool landing = top ? mPhysicsProperties.gravity < 0.f : mPhysicsProperties.gravity > 0.f;
        mUpdatedEntity.setVelocityY(0.f);
        if (landing)
        {
            switch (platformSurface)
            {
            case PlatformSurface::Ordinary:
                mUpdatedEntity.setVelocityX(0.f);
                break;
            case PlatformSurface::Slippery:
                mUpdatedEntity.setAccelerationX(-math::sign(mUpdatedEntity.getVelocity().x) *
                    mPhysicsProperties.friction);
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

            if (mEntity->getState() == CharacterState::Falling)
            {
                mUpdatedEntity.setState(CharacterState::Dying);
            }
            else if (mEntity->getState() == CharacterState::Flying ||
                mEntity->getState() == CharacterState::Stopping)
            {
                switch (platformSurface)
                {
                case PlatformSurface::Ordinary:
                    mUpdatedEntity.setState(CharacterState::Standing);
                    break;
                case PlatformSurface::Slippery:
                    mUpdatedEntity.setState(CharacterState::Sliding);
                    break;
                case PlatformSurface::Sticky:
                    mUpdatedEntity.setState(CharacterState::Sticking);
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

    void CharacterUpdater::leftPlatformCollision(float x)
    {
        mUpdatedEntity.setRectLeft(x);
        sideBounce();
    }

    void CharacterUpdater::rightPlatformCollision(float x)
    {
        mUpdatedEntity.setRectRight(x);
        sideBounce();
    }

    void CharacterUpdater::topPlatformCollision(float y, PlatformSurface platformSurface)
    {
        mUpdatedEntity.setRectTop(y);
        topBottomCollision(true, platformSurface);
    }

    void CharacterUpdater::bottomPlatformCollision(float y, PlatformSurface platformSurface)
    {
        mUpdatedEntity.setRectBottom(y);
        topBottomCollision(false, platformSurface);
    }

    math::Vector2<float> CharacterUpdater::getResultantAcceleration(const Character& entity,
        const Wind* wind/* = nullptr*/) const
    {
        //entityA + windV * factor + gravityA
        math::Vector2<float> resultantAcceleration = entity.getAcceleration() +
            math::Vector2<float>(0.f, mPhysicsProperties.gravity);
        if (wind != nullptr)
        {
            resultantAcceleration += wind->getVelocity() * wind->getFactor();
        }
        return resultantAcceleration;
    }

    math::Vector2<float> CharacterUpdater::getResultantVelocity(const Character& entity) const
    {
        //entityV + runV
        return entity.getVelocity() + math::Vector2<float>(entity.getRunVelocity(), 0.f);
    }
}