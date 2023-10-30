#include "../inc/Character.hpp"

#include "../../math/inc/Vector2.hpp"
#include "../../math/inc/Function.hpp"

namespace jp::game::engine
{
    Character::Character(const std::shared_ptr<physics::Character>& physicsCharacter,
        const Properties& properties)
        : mPhysicsCharacter(physicsCharacter), mProperties(properties)
    {}

    Character& Character::operator=(const Character& other)
    {
        mPhysicsCharacter = other.mPhysicsCharacter;
        mDirection = other.mDirection;
        mJumpPower = other.mJumpPower;
        return *this;
    }

    void Character::update(float dt)
    {
        if (mPhysicsCharacter->getState() == physics::CharacterState::Squatting)
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
        return mPhysicsCharacter->getState() == physics::CharacterState::Dying ||
            mPhysicsCharacter->getState() == physics::CharacterState::Running ||
            mPhysicsCharacter->getState() == physics::CharacterState::Sliding ||
            mPhysicsCharacter->getState() == physics::CharacterState::Standing ||
            mPhysicsCharacter->getState() == physics::CharacterState::Stopping;
    }

    bool Character::canSquat() const
    {
        return canRun() || mPhysicsCharacter->getState() == physics::CharacterState::Sticking;
    }

    bool Character::isDying() const
    {
        return mPhysicsCharacter->getState() == physics::CharacterState::Dying;
    }

    bool Character::isSquatting() const
    {
        return mPhysicsCharacter->getState() == physics::CharacterState::Squatting;
    }

    void Character::jump()
    {
        if (mPhysicsCharacter->getState() == physics::CharacterState::Squatting)
        {
            mPhysicsCharacter->setState(physics::CharacterState::Flying);
            mPhysicsCharacter->setAccelerationX(0.f);
            switch(mDirection)
            {
                case Direction::Up:
                {
                    mPhysicsCharacter->setVelocity(math::Vector2<float>(mPhysicsCharacter->getVelocity().x,
                        -std::min(mProperties.jumpMax.y, mJumpPower.y)));
                    break;
                }
                case Direction::Left:
                {
                    mPhysicsCharacter->setVelocity(math::Vector2<float>(-mProperties.jumpMax.x +
                        mPhysicsCharacter->getVelocity().x, -std::min(mProperties.jumpMax.y, mJumpPower.y)));
                    break;
                }
                case Direction::Right:
                {
                    mPhysicsCharacter->setVelocity(math::Vector2<float>(mProperties.jumpMax.x +
                        mPhysicsCharacter->getVelocity().x, -std::min(mProperties.jumpMax.y, mJumpPower.y)));
                    break;
                }
                default:
                break;
            }
            mJumpPower = math::Vector2<float>();
        }
    }

    void Character::run(Direction direction)
    {
        mDirection = direction;
        if (canRun() && direction != Direction::Up)
        {
            mPhysicsCharacter->setState(physics::CharacterState::Running);
            float directionSign = direction == Direction::Left ? -1.f : 1.f;
            if (math::sign(mPhysicsCharacter->getRunVelocity()) != directionSign)
            {
                mPhysicsCharacter->setVelocityX(mPhysicsCharacter->getVelocity().x +
                    mPhysicsCharacter->getRunVelocity());
            }

            mPhysicsCharacter->setRunVelocity(directionSign * mProperties.runVelocity);
        }
    }

    void Character::squat()
    {
        if (canSquat())
        {
            mPhysicsCharacter->setState(physics::CharacterState::Squatting);
        }
    }

    void Character::stop()
    {
        if (mPhysicsCharacter->getState() == physics::CharacterState::Running)
        {
            mPhysicsCharacter->setState(physics::CharacterState::Stopping);
            mPhysicsCharacter->setVelocity(
                math::Vector2<float>(mPhysicsCharacter->getVelocity().x +
                    mPhysicsCharacter->getRunVelocity(), 0.f));
            mPhysicsCharacter->setRunVelocity(0.f);
        }
    }

    const math::Rect<float>& Character::getRect() const
    {
        return mPhysicsCharacter->getRect();
    }

    math::Vector2<float> Character::getPosition() const
    {
        return mPhysicsCharacter->getPosition();
    }

    Character::Direction Character::getDirection() const
    {
        return mDirection;
    }

    float Character::getJumpPower() const
    {
        return mJumpPower.y;
    }

    void Character::setDirection(Direction direction)
    {
        mDirection = direction;
    }

    //to remove
    void Character::printInfo()
    {
        std::cout << "r: " << getRect() << std::endl;
        std::string state = "Standing";
        switch(mPhysicsCharacter->getState())
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
        std::cout << "v: " << mPhysicsCharacter->getVelocity() << std::endl;
        std::cout << "rv: " << mPhysicsCharacter->getRunVelocity() << std::endl;
        std::cout << "a: " << mPhysicsCharacter->getAcceleration() << std::endl;
        std::cout << "d: " << (int)mDirection << std::endl;
        std::cout << "uc: " << mPhysicsCharacter.use_count() << std::endl << std::endl;
    }

    void Bot::update(float dt)
    {
        Character::update(dt);
        mTime -= dt;
        switch (mState)
        {
        case State::Jumping:
            if (mJumpPower.y / mProperties.jumpMax.y > mJumpPercent)
            {
                Character::jump();
                mJumpPercent = 0.f;
                mState = State::Ready;
            }
            break;
        case State::Running:
            if (mTime <= 0.f)
            {
                Character::stop();
                mTime = 0.f;
                mState = State::Ready;
            }
            break;
        case State::Ready:
        default:
            break;
        }
    }

    void Bot::jump(Direction direction, float percent)
    {
        if (mState != State::Ready)
        {
            return;
        }

        mDirection = direction;
        mJumpPercent = percent;
        mState = State::Jumping;
        squat();
    }

    void Bot::run(Direction direction, float time)
    {
        if (mState != State::Ready)
        {
            return;
        }

        mTime = time;
        mState = State::Running;
        Character::run(direction);
    }
}