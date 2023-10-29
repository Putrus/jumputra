#include "../inc/Character.hpp"

#include "../../math/inc/Vector2.hpp"
#include "../../math/inc/Function.hpp"

namespace jp::game::engine
{
    Character::Character(const std::shared_ptr<physics::Character>& entity, const CharacterProperties& properties)
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
        if (mEntity->getState() == physics::CharacterState::Squatting)
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
        return mEntity->getState() == physics::CharacterState::Dying ||
            mEntity->getState() == physics::CharacterState::Running ||
            mEntity->getState() == physics::CharacterState::Sliding ||
            mEntity->getState() == physics::CharacterState::Standing ||
            mEntity->getState() == physics::CharacterState::Stopping;
    }

    bool Character::canSquat() const
    {
        return canRun() || mEntity->getState() == physics::CharacterState::Sticking;
    }

    bool Character::isDying() const
    {
        return mEntity->getState() == physics::CharacterState::Dying;
    }

    bool Character::isSquatting() const
    {
        return mEntity->getState() == physics::CharacterState::Squatting;
    }

    void Character::jump()
    {
        if (mEntity->getState() == physics::CharacterState::Squatting)
        {
            mEntity->setState(physics::CharacterState::Flying);
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
            mEntity->setState(physics::CharacterState::Running);
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
            mEntity->setState(physics::CharacterState::Squatting);
        }
    }

    void Character::stop()
    {
        if (mEntity->getState() == physics::CharacterState::Running)
        {
            mEntity->setState(physics::CharacterState::Stopping);
            mEntity->setVelocity(math::Vector2<float>(mEntity->getVelocity().x + mEntity->getRunVelocity(), 0.f));
            mEntity->setRunVelocity(0.f);
        }
    }

    const math::Rect<float>& Character::getRect() const
    {
        return mEntity->getRect();
    }

    math::Vector2<float> Character::getPosition() const
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
            case physics::CharacterState::Dying:
                state = "Dying";
                break;
            case physics::CharacterState::Falling:
                state = "Falling";
                break;
            case physics::CharacterState::Flying:
                state = "Flying";
                break;
            case physics::CharacterState::Running:
                state = "Running";
                break;
            case physics::CharacterState::Sledding:
                state = "Sledding";
                break;
            case physics::CharacterState::Sliding:
                state = "Sliding";
                break;
            case physics::CharacterState::Squatting:
                state = "Squatting";
                break;
            case physics::CharacterState::Standing:
                state = "Standing";
                break;
            case physics::CharacterState::Sticking:
                state = "Sticking";
                break;
            case physics::CharacterState::Stopping:
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