#include "../inc/HorizontalPlatform.hpp"

#include <algorithm>
#include <sstream>

namespace jp::game::physics
{
    HorizontalPlatform::HorizontalPlatform(const math::Segment<float>& segment, Surface surface) : Platform(segment, surface)
    {
        if (!mSegment.isHorizontal())
        {
            std::stringstream ss;
            ss << "Failed to create horizontal platform, segment " << segment << " isn't horizontal!";
            throw std::invalid_argument(ss.str());
        }

        if (mSegment.a.x > mSegment.b.x)
        {
            mSegment.swapPoints();
        }
    }

    Collision HorizontalPlatform::checkCollision(const math::Rect<float>& oldRect,
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

    bool HorizontalPlatform::checkCollision(math::Vector2<float> a, math::Vector2<float> b) const
    {
        return a.x > mSegment.a.x && a.x < mSegment.b.x && mSegment.a.y > a.y && mSegment.a.y < b.y;
    }
}