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

        const math::Vector2<float>& getControlledVelocity() const;
        math::Vector2<float> getPosition() const;
        const math::Rect<float>& getRect() const;
        EntityState getState() const;

        void setControlledVelocity(const math::Vector2<float>& velocity);
        void setControlledVelocityX(float x);
        void setControlledVelocityY(float y);
        void setPosition(const math::Vector2<float>& position);
        void setRect(const math::Rect<float>& rect);
        void setRectTop(float y);
        void setRectBottom(float y);
        void setRectLeft(float x);
        void setRectRight(float x);
        void setState(EntityState state);

    protected:
        math::Vector2<float> mControlledVelocity;
        math::Rect<float> mRect;
        EntityState mState = EntityState::Flying;
    };
}