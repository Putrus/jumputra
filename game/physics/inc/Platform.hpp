#pragma once

#include "../../math/inc/Rect.hpp"
#include "../../math/inc/Segment.hpp"

namespace jp::game::physics
{
    enum class PlatformSurface : unsigned int
    {
        Ordinary = 0,
        Slippery,
        Sticky
    };

    enum class PlatformCollision : unsigned int
    {
        No = 0,
        Top,
        Bottom,
        Left,
        Right,
        Attic,
        Roof
    };

    class Platform
    {
    public:
        Platform(const math::Segment<float>& segment, PlatformSurface surface);
        virtual PlatformCollision checkCollision(const math::Rect<float>& oldRect,
            const math::Rect<float>& newRect) const = 0;

        const math::Segment<float>& getSegment() const;
        PlatformSurface getSurface() const;

    protected:
        math::Segment<float> mSegment;
        PlatformSurface mSurface;
    };
}