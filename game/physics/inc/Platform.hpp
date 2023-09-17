#pragma once

#include "../../math/inc/Rect.hpp"
#include "../../math/inc/Segment.hpp"

namespace jp::game::physics
{
    enum class Surface : unsigned int
    {
        Ordinary = 0,
        Slippery,
        Sticky
    };

    enum class Collision : unsigned int
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
        Platform(const math::Segment<float>& segment, Surface surface);
        virtual Collision checkCollision(const math::Rect<float>& oldRect,
            const math::Rect<float>& newRect) const = 0;

        const math::Segment<float>& getSegment() const;
        Surface getSurface() const;

    protected:
        math::Segment<float> mSegment;
        Surface mSurface;
    };
}