#include "../inc/PlatformHorizontal.hpp"

#include <algorithm>

namespace jp::game::physics
{
    PlatformHorizontal::PlatformHorizontal(const math::Segment<float>& segment, Surface surface) : Platform(segment, surface)
    {
        if (!mSegment.isHorizontal())
        {
            throw std::invalid_argument("Failed to create horizontal platform, segment isn't horizontal!");
        }

        if (mSegment.a.x > mSegment.b.x)
        {
            mSegment.swapPoints();
        }
    }

    Collision PlatformHorizontal::checkCollision(const math::Rect<float>& oldRect,
            const math::Rect<float>& newRect) const
    {
        if (checkCollision(newRect.getLeftTop(), newRect.getLeftBottom()) ||
            checkCollision(newRect.getRightTop(), newRect.getRightBottom()))
        {
            if (oldRect.left >= mSegment.b.x)
            {
                return Collision::Left;
            }
            else if (oldRect.getRight() <= mSegment.a.x)
            {
                return Collision::Right;
            }
            else if (oldRect.getCenter().y > mSegment.b.y)
            {
                return Collision::Top;
            }
            else
            {
                return Collision::Bottom;
            }
        }
        return Collision::No;
    }

    bool PlatformHorizontal::checkCollision(math::Vector2<float> a, math::Vector2<float> b) const
    {
        const math::Vector2<float>& c = mSegment.a;
        const math::Vector2<float>& d = mSegment.b;
        return a.x > c.x && a.x < d.x && c.y > a.y && c.y < b.y;
    }
}