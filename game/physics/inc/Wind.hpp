#pragma once

#include "Kinematics.hpp"
#include "WindProperties.hpp"

namespace jp::game::physics
{
    class Wind final : public Kinematics
    {
    public:
        Wind();
        Wind(const WindProperties& windProperties);

        float getStartPosition() const;
        float getEndPosition() const;

    private:
        float mStartPosition = 0.f;
        float mEndPosition = 0.f;
    };
}