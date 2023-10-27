#pragma once

#include "Kinematics.hpp"

#include "../../math/inc/Rect.hpp"

namespace jp::game::physics
{
    enum class EntityState : unsigned int
    {
        Dying = 0,
        Falling,
        Flying,
        Running,
        Sledding,
        Sliding,
        Squatting,
        Standing
    };

    class Entity : public Kinematics
    {
    public:
        Entity();
        Entity(const math::Rect<float>& rect);

        void move(const math::Vector2<float>& vec);

        float getRunVelocity() const;
        math::Vector2<float> getPosition() const;
        const math::Rect<float>& getRect() const;
        EntityState getState() const;

        void setPosition(const math::Vector2<float>& position);
        void setRect(const math::Rect<float>& rect);
        void setRectTop(float y);
        void setRectBottom(float y);
        void setRectLeft(float x);
        void setRectRight(float x);
        void setRunVelocity(float runVelocity);
        void setState(EntityState state);

    protected:
        math::Rect<float> mRect;
        float mRunVelocity = 0.f;
        EntityState mState = EntityState::Flying;
    };
}