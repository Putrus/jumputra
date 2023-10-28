#include "../inc/CharacterProperties.hpp"

namespace jp::game::engine
{
    CharacterProperties::CharacterProperties()
    {}

    CharacterProperties::CharacterProperties(const math::Vector2<float>& jumpGain,
        const math::Vector2<float>& jumpMax, float runVelocity)
        : jumpGain(jumpGain), jumpMax(jumpMax), runVelocity(runVelocity)
    {}
}