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
                    mEntity->setVelocityY(-mJumpPower);
                    break;
                }
                case CharacterJumpDirection::Left:
                {
                    mEntity->setVelocity({ -mJumpPower / 2.f, -mJumpPower });
                    break;
                }
                case CharacterJumpDirection::Right:
                {
                    mEntity->setVelocity({ mJumpPower / 2.f, -mJumpPower });
                    break;
                }
                default:
                break;
            }
            mJumpPower = 0.f;
            mEntity->setState(physics::EntityState::Flying);
        }
    }

    void Character::squat()
    {
        if (mEntity->getState() == physics::EntityState::Running ||
            mEntity->getState() == physics::EntityState::Sliding ||
            mEntity->getState() == physics::EntityState::Standing)
        {
            mEntity->setState(physics::EntityState::Squatting);
        }
    }

    void Character::stop()
    {
        if (mEntity->getState() == physics::EntityState::Running)
        {
            mEntity->setVelocityX(0.f);
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
        std::cout << getRect() << std::endl;
        std::cout << (int)mEntity->getState() << std::endl;
    }
}