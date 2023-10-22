#include "../inc/VerticalPlatform.hpp"

#include <algorithm>
#include <sstream>

namespace jp::game::physics
{
    VerticalPlatform::VerticalPlatform(const math::Segment<float>& segment, PlatformSurface surface) : Platform(segment, surface)
    {
        if (!mSegment.isVertical())
        {
            std::stringstream ss;
            ss << "Failed to create vertical platform, segment " << segment << " isn't vertical!";
            throw std::invalid_argument(ss.str());
        }

        if (mSegment.a.y > mSegment.b.y)
        {
            mSegment.swapPoints();
        }
    }

    VerticalPlatform::VerticalPlatform(const math::Vector2<float>& a,
        const math::Vector2<float>& b, PlatformSurface surface)
        : VerticalPlatform(math::Segment<float>(a, b), surface)
    {}

    PlatformCollision VerticalPlatform::checkCollision(const math::Rect<float>& oldRect,
            const math::Rect<float>& newRect) const
    {
        if (checkCollision(newRect.getLeftTop(), newRect.getRightTop()) ||
            checkCollision(newRect.getLeftBottom(), newRect.getRightBottom()))
        {
            if (oldRect.top >= mSegment.b.y)
            {
                return PlatformCollision::Top;
            }
            else if (oldRect.getBottom() <= mSegment.a.y)
            {
                return PlatformCollision::Bottom;
            }
            else if (oldRect.getCenter().x > mSegment.b.x)
            {
                return PlatformCollision::Left;
            }
            else
            {
                return PlatformCollision::Right;
            }
        }
        return PlatformCollision::No;
    }

    bool VerticalPlatform::checkCollision(math::Vector2<float> a, math::Vector2<float> b) const
    {
        return a.y > mSegment.a.y && a.y < mSegment.b.y && mSegment.a.x > a.x && mSegment.a.x < b.x;
    }
}