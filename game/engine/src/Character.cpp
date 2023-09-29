#include "../inc/Character.hpp"

namespace jp::game::engine
{
    Character::Character(std::shared_ptr<physics::Entity> entity) : mEntity(entity)
    {}

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
                    mEntity->setVelocity({ -100.f, -mJumpPower });
                }
                case CharacterJumpDirection::Right:
                {
                    mEntity->setVelocity({ 100.f, -mJumpPower });
                }
                default:
                break;
            }
        }
    }

    void Character::squat()
    {
        mEntity->setState(physics::EntityState::Squatting);
    }

    void Character::runLeft()
    {
        mEntity->setState(physics::EntityState::Running);
        mEntity->setVelocityX(-100.f);
    }

    void Character::runRight()
    {
        mEntity->setState(physics::EntityState::Running);
        mEntity->setVelocityX(100.f);
    }

    const math::Rect<float>& Character::getRect() const
    {
        return mEntity->getRect();
    }

    void Character::setJumpDirection(CharacterJumpDirection jumpDirection)
    {
        mJumpDirection = jumpDirection;
    }
}