#include "../inc/Character.hpp"

namespace jp::game::engine
{
    Character::Character(std::shared_ptr<physics::Entity> entity) : mEntity(entity)
    {}

    void Character::update(float dt)
    {
        if (mEntity->getState() == physics::EntityState::Squatting)
        {
            //to do 1000.f can't be hardcoded
            mJumpPower += dt * 1000.f;
        }
    }

    bool Character::canMove() const
    {
        return mEntity->getState() == physics::EntityState::Dying ||
            mEntity->getState() == physics::EntityState::Running ||
            mEntity->getState() == physics::EntityState::Sliding ||
            mEntity->getState() == physics::EntityState::Standing;
    }

    void Character::jump()
    {
        if (mEntity->getState() == physics::EntityState::Squatting)
        {
            switch(mJumpDirection)
            {
                case CharacterJumpDirection::Up:
                {
                    mEntity->setVelocity({ mEntity->getSlideVelocity(), -mJumpPower });
                    break;
                }
                case CharacterJumpDirection::Left:
                {
                    mEntity->setVelocity({ -mJumpPower / 2.f + mEntity->getSlideVelocity(), -mJumpPower });
                    break;
                }
                case CharacterJumpDirection::Right:
                {
                    mEntity->setVelocity({ mJumpPower / 2.f + mEntity->getSlideVelocity(), -mJumpPower });
                    break;
                }
                default:
                break;
            }
            mJumpPower = 0.f;
            mEntity->setSlideVelocity(0.f);
            mEntity->setSlideAcceleration(0.f);
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
            mEntity->setState(physics::EntityState::Running);
            mEntity->setVelocityX(-100.f);
        }
    }

    void Character::runRight()
    {
        if (canMove())
        {
            mEntity->setState(physics::EntityState::Running);
            mEntity->setVelocityX(100.f);
        }
    }

    const math::Rect<float>& Character::getRect() const
    {
        return mEntity->getRect();
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
        std::cout << "rect: " << getRect() << std::endl;
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
        std::cout << "state: " << state << std::endl;
        std::cout << "velocity: " << mEntity->getVelocity() << std::endl;
        std::cout << "slide v: " << mEntity->getSlideVelocity() << " a: " << mEntity->getSlideAcceleration() << std::endl << std::endl;
    }
}