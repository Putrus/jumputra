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
        mJumpDirection = other.mJumpDirection;
        mJumpPower = other.mJumpPower;
        return *this;
    }

    void Character::update(float dt)
    {
        if (mEntity->getState() == physics::EntityState::Squatting)
        {
            //to do 1000.f can't be hardcoded
            mJumpPower += mProperties.getJumpGain() * dt;
            if (mJumpPower.x > mProperties.getJumpMax().x && mJumpPower.y > mProperties.getJumpMax().y)
            {
                mJumpPower = mProperties.getJumpMax();
                jump();
            }
        }
    }

    bool Character::canMove() const
    {
        return mEntity->getState() == physics::EntityState::Dying ||
            mEntity->getState() == physics::EntityState::Running ||
            mEntity->getState() == physics::EntityState::Sliding ||
            mEntity->getState() == physics::EntityState::Standing;
    }

    bool Character::isSquating() const
    {
        return mEntity->getState() == physics::EntityState::Squatting;
    }

    void Character::jump()
    {
        if (mEntity->getState() == physics::EntityState::Squatting)
        {
            switch(mJumpDirection)
            {
                case CharacterJumpDirection::Up:
                {
                    mEntity->setVelocity(math::Vector2<float>(mEntity->getVelocity().x, -mJumpPower.y));
                    break;
                }
                case CharacterJumpDirection::Left:
                {
                    mEntity->setVelocity(math::Vector2<float>(-mProperties.getJumpMax().x + mEntity->getVelocity().x, -mJumpPower.y));
                    break;
                }
                case CharacterJumpDirection::Right:
                {
                   mEntity->setVelocity(math::Vector2<float>(mProperties.getJumpMax().x + mEntity->getVelocity().x, -mJumpPower.y));
                    break;
                }
                default:
                break;
            }
            mJumpPower = math::Vector2<float>();
            mEntity->setAccelerationX(0.f);
            mEntity->setState(physics::EntityState::Flying);
        }
    }

    void Character::squat()
    {
        if (canMove())
        {
            mEntity->setState(physics::EntityState::Squatting);
        }
    }

    void Character::stop()
    {
        if (mEntity->getState() == physics::EntityState::Running)
        {
            mEntity->setState(physics::EntityState::Standing);
        }
    }

    void Character::runLeft()
    {
        if (canMove())
        {
            if (mEntity->getRunVelocity() > 0.f)
            {
                mEntity->setVelocityX(std::max(0.f, mEntity->getVelocity().x + mEntity->getRunVelocity()));
            }
            mEntity->setState(physics::EntityState::Running);
            mEntity->setRunVelocity(-mProperties.getRunVelocity());
        }
    }

    void Character::runRight()
    {
        if (canMove())
        {
            if (mEntity->getRunVelocity() < 0.f)
            {
                mEntity->setVelocityX(std::min(0.f, mEntity->getVelocity().x + mEntity->getRunVelocity()));
            }
            mEntity->setState(physics::EntityState::Running);
            mEntity->setRunVelocity(mProperties.getRunVelocity());
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

    CharacterJumpDirection Character::getJumpDirection() const
    {
        return mJumpDirection;
    }

    void Character::setJumpDirection(CharacterJumpDirection jumpDirection)
    {
        mJumpDirection = jumpDirection;
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
            default:
                state = "Undefined";
                break;
        }
        std::cout << "s: " << state << std::endl;
        std::cout << "v: " << mEntity->getVelocity() << std::endl;
        std::cout << "rv: " << mEntity->getRunVelocity() << std::endl;
        std::cout << "a: " << mEntity->getAcceleration() << std::endl;
        std::cout << "d: " << (int)mJumpDirection << std::endl;
        std::cout << "uc: " << mEntity.use_count() << std::endl << std::endl;
    }
}