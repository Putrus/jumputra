#include "../inc/PlatformDiagonal.hpp"

#include <algorithm>

namespace jp::game::physics
{
    PlatformDiagonal::PlatformDiagonal(const math::Segment<float>& segment, Surface surface) : Platform(segment, surface)
    {
        if (!mSegment.isDiagonal())
        {
            throw std::invalid_argument("Failed to create diagonal platform, segment isn't diagonal!");
        }

        if (mSegment.a.x > mSegment.b.x)
        {
            mSegment.swapPoints();
        }
    }

    Collision PlatformDiagonal::checkCollision(const math::Rect<float>& oldRect,
            const math::Rect<float>& newRect) const
    {
        if (checkCollision(newRect.getLeftTop(), newRect.getRightTop()) ||
            checkCollision(newRect.getLeftBottom(), newRect.getRightBottom()))
        {
            return newRect.getCenter().y > oldRect.getCenter().y ? Collision::Roof : Collision::Attic;
        }
    }

    bool PlatformDiagonal::checkCollision(math::Vector2<float> a, math::Vector2<float> b) const
    {
        const math::Vector2<float>& c = mSegment.a;
        const math::Vector2<float>& d = mSegment.b;

        float slope = (d.y - c.y) / (d.x - c.x);
        float intercept = d.y - slope * d.x;
        float commonX = (a.y - intercept) / slope;
        return commonX >= a.x && commonX <= b.x && commonX >= c.x && commonX <= d.x;
    }
}