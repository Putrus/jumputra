#include "../inc/CharacterProperties.hpp"

namespace jp::game::engine
{
    CharacterProperties::CharacterProperties()
        : mJumpGain(math::Vector2<float>()), mJumpMax(math::Vector2<float>()), mRunVelocity(0.f)
    {}

    CharacterProperties::CharacterProperties(const math::Vector2<float>& jumpGain,
        const math::Vector2<float>& jumpMax, float runVelocity)
        : mJumpGain(jumpGain), mJumpMax(jumpMax), mRunVelocity(runVelocity)
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

    void CharacterProperties::setJumpGain(const math::Vector2<float>& jumpGain)
    {
        mJumpGain = jumpGain;
    }

    void CharacterProperties::setJumpMax(const math::Vector2<float>& jumpMax)
    {
        mJumpMax = jumpMax;
    }

    void CharacterProperties::setRunVelocity(float runVelocity)
    {
        mRunVelocity = runVelocity;
    }
}