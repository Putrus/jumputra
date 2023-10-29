#pragma once

#include "Kinematics.hpp"

#include "../../math/inc/Rect.hpp"

namespace jp::game::physics
{
    class Entity : public Kinematics
    {
    public:
        Entity();
        Entity(const math::Rect<float>& rect,
            const math::Vector2<float>& acceleration = 0.f,
            const math::Vector2<float>& velocity = 0.f);

        math::Vector2<float> getPosition() const;
        const math::Rect<float>& getRect() const;

        void setPosition(const math::Vector2<float>& position);
        void setRect(const math::Rect<float>& rect);
        void setRectTop(float y);
        void setRectBottom(float y);
        void setRectLeft(float x);
        void setRectRight(float x);

    protected:
        math::Rect<float> mRect;
    };
}