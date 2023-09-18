#pragma once

#include "Kinematics.hpp"

#include "../../math/inc/Rect.hpp"

namespace jp::game::physics
{
    class Entity : public Kinematics
    {
    public:
        Entity(const math::Rect<float>& rect,
            const math::Vector2<float>& velocity, const math::Vector2<float>& acceleration);

        void move(const math::Vector2<float>& vec);

        const math::Rect<float>& getRect() const;
        math::Vector2<float> getPosition() const;

        void setRect(const math::Rect<float>& rect);
        void setRectTop(float y);
        void setRectBottom(float y);
        void setRectLeft(float x);
        void setRectRight(float x);

    protected:
        math::Rect<float> mRect;
    };
}