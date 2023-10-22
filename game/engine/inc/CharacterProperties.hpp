#pragma once

#include "../../math/inc/Vector2.hpp"

namespace jp::game::engine
{

    class CharacterProperties
    {
    public:
        CharacterProperties();
        CharacterProperties(const math::Vector2<float>& jumpGain,
            const math::Vector2<float>& jumpMax, float runVelocity);

        const math::Vector2<float>& getJumpGain() const;
        const math::Vector2<float>& getJumpMax() const;
        float getRunVelocity() const;

        void setJumpGain(const math::Vector2<float>& jumpGain);
        void setJumpMax(const math::Vector2<float>& jumpMax);
        void setRunVelocity(float runVelocity);
        
    private:
        math::Vector2<float> mJumpGain;
        math::Vector2<float> mJumpMax;
        float mRunVelocity;
    };
}