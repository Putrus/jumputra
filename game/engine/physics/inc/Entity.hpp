#pragma once

#include "../../math/inc/Rect.hpp"

namespace jp::game::engine::physics
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

    class Entity
    {
    public:
        Entity();
        Entity(const math::Rect<float>& rect);

        void move(const math::Vector2<float>& vec);

        const math::Rect<float>& getRect() const;
        math::Vector2<float> getPosition() const;
        float getSlideAcceleration() const;
        float getSlideVelocity() const;
        EntityState getState() const;
        const math::Vector2<float>& getVelocity() const;
        float getVelocityXSign() const;

        void setPosition(const math::Vector2<float>& position);
        void setRect(const math::Rect<float>& rect);
        void setRectTop(float y);
        void setRectBottom(float y);
        void setRectLeft(float x);
        void setRectRight(float x);
        void setSlideAcceleration(float acceleration);
        void setSlideVelocity(float velocity);
        void setState(EntityState state);
        void setVelocity(const math::Vector2<float>& velocity);
        void setVelocityX(float x);
        void setVelocityY(float y);

    protected:
        math::Rect<float> mRect;
        float mSlideAcceleration = 0.f;
        float mSlideVelocity = 0.f;
        EntityState mState = EntityState::Flying;
        math::Vector2<float> mVelocity = math::Vector2<float>();
    };
}