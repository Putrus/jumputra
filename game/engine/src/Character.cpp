#include "../inc/Character.hpp"

#include "../../math/inc/Vector2.hpp"
#include "../../math/inc/Function.hpp"

namespace jp::game::engine
{
    Character::Character(const std::shared_ptr<physics::Entity>& entity, const CharacterProperties& properties)
        : mEntity(entity), mProperties(properties)
    {}

    Character& Character::operator=(const Character& other)
    {
        mEntity = other.mEntity;
        mDirection = other.mDirection;
        mJumpPower = other.mJumpPower;
        return *this;
    }

    void Character::update(float dt)
    {
        if (mEntity->getState() == physics::EntityState::Squatting)
        {
            mJumpPower += mProperties.jumpGain * dt;
            if (mJumpPower.y >= mProperties.jumpGain.y)
            {
                jump();
            }
        }
    }

    bool Character::canRun() const
    {
        return mEntity->getState() == physics::EntityState::Dying ||
            mEntity->getState() == physics::EntityState::Running ||
            mEntity->getState() == physics::EntityState::Sliding ||
            mEntity->getState() == physics::EntityState::Standing ||
            mEntity->getState() == physics::EntityState::Stopping;
    }

    bool Character::canSquat() const
    {
        return canRun() || mEntity->getState() == physics::EntityState::Sticking;
    }

    bool Character::isDying() const
    {
        return mEntity->getState() == physics::EntityState::Dying;
    }

    bool Character::isSquatting() const
    {
        return mEntity->getState() == physics::EntityState::Squatting;
    }

    void Character::jump()
    {
        if (mEntity->getState() == physics::EntityState::Squatting)
        {
            mEntity->setState(physics::EntityState::Flying);
            mEntity->setAccelerationX(0.f);
            switch(mDirection)
            {
                case CharacterDirection::Up:
                {
                    mEntity->setVelocity(math::Vector2<float>(mEntity->getVelocity().x,
                        -std::min(mProperties.jumpMax.y, mJumpPower.y)));
                    break;
                }
                case CharacterDirection::Left:
                {
                    mEntity->setVelocity(math::Vector2<float>(-mProperties.jumpMax.x +
                        mEntity->getVelocity().x, -std::min(mProperties.jumpMax.y, mJumpPower.y)));
                    break;
                }
                case CharacterDirection::Right:
                {
                    mEntity->setVelocity(math::Vector2<float>(mProperties.jumpMax.x +
                        mEntity->getVelocity().x, -std::min(mProperties.jumpMax.y, mJumpPower.y)));
                    break;
                }
                default:
                break;
            }
            mJumpPower = math::Vector2<float>();
        }
    }

    void Character::run(CharacterDirection direction)
    {
        mDirection = direction;
        if (canRun() && direction != CharacterDirection::Up)
        {
            mEntity->setState(physics::EntityState::Running);
            float directionSign = direction == CharacterDirection::Left ? -1.f : 1.f;
            if (math::sign(mEntity->getRunVelocity()) != directionSign)
            {
                mEntity->setVelocityX(mEntity->getVelocity().x + mEntity->getRunVelocity());
            }

            mEntity->setRunVelocity(directionSign * mProperties.runVelocity);
        }
    }

    void Character::squat()
    {
        if (canSquat())
        {
            mEntity->setState(physics::EntityState::Squatting);
        }
    }

    void Character::stop()
    {
        if (mEntity->getState() == physics::EntityState::Running)
        {
            mEntity->setState(physics::EntityState::Stopping);
            mEntity->setVelocity(math::Vector2<float>(mEntity->getVelocity().x + mEntity->getRunVelocity(), 0.f));
            mEntity->setRunVelocity(0.f);
        }
    }

    const math::Rect<float>& Character::getRect() const
    {
        return mEntity->getRect();
    }

    const math::Vector2<float>& Character::getPosition() const
    {
        return mEntity->getPosition();
    }

    CharacterDirection Character::getDirection() const
    {
        return mDirection;
    }

    float Character::getJumpPower() const
    {
        return mJumpPower.y;
    }

    void Character::setDirection(CharacterDirection direction)
    {
        mDirection = direction;
    }

    //to remove
    void Character::printInfo()
    {
        std::cout << "r: " << getRect() << std::endl;
        std::string state = "Standing";
        switch(mEntity->getState())
        {
            case physics::EntityState::Dying:
                state = "Dying";
                break;
            case physics::EntityState::Falling:
                state = "Falling";
                break;
            case physics::EntityState::Flying:
                state = "Flying";
                break;
            case physics::EntityState::Running:
                state = "Running";
                break;
            case physics::EntityState::Sledding:
                state = "Sledding";
                break;
            case physics::EntityState::Sliding:
                state = "Sliding";
                break;
            case physics::EntityState::Squatting:
                state = "Squatting";
                break;
            case physics::EntityState::Standing:
                state = "Standing";
                break;
            case physics::EntityState::Sticking:
                state = "Sticking";
                break;
            case physics::EntityState::Stopping:
                state = "Stopping";
                break;
            default:
                state = "Undefined";
                break;
        }
        std::cout << "s: " << state << std::endl;
        std::cout << "v: " << mEntity->getVelocity() << std::endl;
        std::cout << "rv: " << mEntity->getRunVelocity() << std::endl;
        std::cout << "a: " << mEntity->getAcceleration() << std::endl;
        std::cout << "d: " << (int)mDirection << std::endl;
        std::cout << "uc: " << mEntity.use_count() << std::endl << std::endl;
    }
}