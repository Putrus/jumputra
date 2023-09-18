#pragma once

#include "Kinematics.hpp"

#include "../../math/inc/Rect.hpp"

namespace jp::game::physics
{
    class KinematicRect : public Kinematics
    {
    public:
        KinematicRect(const math::Rect<float>& rect,
            const math::Vector2<float>& velocity, const math::Vector2<float>& acceleration);

        const math::Rect<float>& getRect() const;

    protected:
        math::Rect<float> mRect;
    };
}