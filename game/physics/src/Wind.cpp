#include "../inc/Wind.hpp"

namespace jp::game::physics
{
    Wind::Wind() : Kinematics()
    {}
    
    Wind::Wind(const math::Vector2<float>& acceleration, const math::Vector2<float>& velocity/* = math::Vector2<float>(0.f)*/)
        : Kinematics(acceleration, velocity)
    {}
}