#include "../inc/KinematicRect.hpp"

namespace jp::game::physics
{
    KinematicRect::KinematicRect(const math::Rect<float>& rect,
        const math::Vector2<float>& velocity, const math::Vector2<float>& acceleration)
        : mRect(rect), Kinematics(velocity, acceleration)
        {}
}