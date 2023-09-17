#include "../inc/PlatformVertical.hpp"

#include <algorithm>

namespace jp::game::physics
{
    PlatformVertical::PlatformVertical(const math::Segment<float>& segment, Surface surface) : Platform(segment, surface)
    {
        if (!mSegment.isVertical())
        {
            throw std::invalid_argument("Failed to create vertical platform, segment isn't vertical!");
        }

        if (mSegment.a.y > mSegment.b.y)
        {
            mSegment.swapPoints();
        }
    }

    Collision PlatformVertical::checkCollision(const math::Rect<float>& oldRect,
            const math::Rect<float>& newRect) const
    {
        if (checkCollision(newRect.getLeftTop(), newRect.getRightTop()) ||
            checkCollision(newRect.getLeftBottom(), newRect.getRightBottom()))
        {
            if (oldRect.top >= mSegment.b.y)
            {
                return Collision::Top;
            }
            else if (oldRect.getBottom() <= mSegment.a.y)
            {
                return Collision::Bottom;
            }
            else if (oldRect.getCenter().x > mSegment.b.x)
            {
                return Collision::Left;
            }
            else
            {
                return Collision::Right;
            }
        }
        return Collision::No;
    }

    bool PlatformVertical::checkCollision(math::Vector2<float> a, math::Vector2<float> b) const
    {
        const math::Vector2<float>& c = mSegment.a;
        const math::Vector2<float>& d = mSegment.b;
        return a.y > c.y && a.y < d.y && c.x > a.x && c.x < b.x;
    }
}