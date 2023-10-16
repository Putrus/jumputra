#include "../inc/CharacterProperties.hpp"

namespace jp::game::engine
{
    CharacterProperties::CharacterProperties(const math::Vector2<float>& entitySize,
        const math::Vector2<float>& jumpGain, const math::Vector2<float>& jumpMax, float runVelocity)
        : mEntitySize(entitySize), mJumpGain(jumpGain), mJumpMax(jumpMax), mRunVelocity(runVelocity)
    {}

    const math::Vector2<float>& CharacterProperties::getJumpGain() const
    {
        return mJumpGain;
    }

    const math::Vector2<float>& CharacterProperties::getJumpMax() const
    {
        return mJumpMax;
    }

    float CharacterProperties::getRunVelocity() const
    {
        return mRunVelocity;
    }
}