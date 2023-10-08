#include "../inc/Function.hpp"

namespace jp::game::engine::math
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