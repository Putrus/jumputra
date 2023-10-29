#include "../inc/Character.hpp"

namespace jp::game::physics
{
    Character::Character()
    {}

    Character::Character(const math::Rect<float>& rect)
        : Entity(rect)
    {}

    void Character::move(const math::Vector2<float>& vec)
    {
        mRect += vec;
    }

    float Character::getRunVelocity() const
    {
        return mRunVelocity;
    }

    CharacterState Character::getState() const
    {
        return mState;
    }

    void Character::setRunVelocity(float runVelocity)
    {
        mRunVelocity = runVelocity;
    }

    void Character::setState(CharacterState state)
    {
        mState = state;
    }  
}