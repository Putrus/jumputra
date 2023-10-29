#pragma once

#include "Entity.hpp"

#include "../../math/inc/Rect.hpp"

namespace jp::game::physics
{
    enum class CharacterState : unsigned int
    {
        Dying = 0,
        Falling,
        Flying,
        Running,
        Sledding,
        Sliding,
        Squatting,
        Standing,
        Sticking,
        Stopping
    };

    class Character : public Entity
    {
    public:
        Character();
        Character(const math::Rect<float>& rect);

        void move(const math::Vector2<float>& vec);

        float getRunVelocity() const;
        CharacterState getState() const;

        void setRunVelocity(float runVelocity);
        void setState(CharacterState state);

    protected:
        float mRunVelocity = 0.f;
        CharacterState mState = CharacterState::Flying;
    };
}