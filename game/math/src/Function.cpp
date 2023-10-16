#include "../inc/Function.hpp"

namespace jp::game::math
{
    float sign(float x)
    {
        if (x == 0.f)
        {
            return 0.f;
        }
        return x / std::abs(x);
    }
}