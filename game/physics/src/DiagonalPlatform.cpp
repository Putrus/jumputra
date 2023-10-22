#include "../inc/DiagonalPlatform.hpp"

#include <algorithm>
#include <sstream>

namespace jp::game::physics
{
    DiagonalPlatform::DiagonalPlatform(const math::Segment<float>& segment, PlatformSurface surface) : Platform(segment, surface)
    {
        if (!mSegment.isDiagonal())
        {
            std::stringstream ss;
            ss << "Failed to create diagonal platform, segment " << segment << " isn't diagonal!";
            throw std::invalid_argument(ss.str());
        }

        if (mSegment.a.x > mSegment.b.x)
        {
            mSegment.swapPoints();
        }
    }

    DiagonalPlatform::DiagonalPlatform(const math::Vector2<float>& a,
        const math::Vector2<float>& b, PlatformSurface surface)
        : DiagonalPlatform(math::Segment<float>(a, b), surface)
    {}

    PlatformCollision DiagonalPlatform::checkCollision(const math::Rect<float>& oldRect,
            const math::Rect<float>& newRect) const
    {
        if (checkCollision(newRect.getLeftTop(), newRect.getRightTop()) ||
            checkCollision(newRect.getLeftBottom(), newRect.getRightBottom()))
        {
            return newRect.getCenter().y > oldRect.getCenter().y ? PlatformCollision::Roof : PlatformCollision::Attic;
        }
        return PlatformCollision::No;
    }

    bool DiagonalPlatform::checkCollision(math::Vector2<float> a, math::Vector2<float> b) const
    {
        float slope = (mSegment.b.y - mSegment.a.y) / (mSegment.b.x - mSegment.a.x);
        float intercept = mSegment.b.y - slope * mSegment.b.x;
        float commonX = (a.y - intercept) / slope;
        return commonX > a.x && commonX < b.x && commonX > mSegment.a.x && commonX < mSegment.b.x;
    }
}