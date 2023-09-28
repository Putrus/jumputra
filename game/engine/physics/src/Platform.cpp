#include "../inc/Platform.hpp"

namespace jp::game::engine::physics
{
    Platform::Platform(const math::Segment<float>& segment, PlatformSurface surface)
    : mSegment(segment), mSurface(surface)
    {}

    const math::Segment<float>& Platform::getSegment() const
    {
        return mSegment;
    }

    PlatformSurface Platform::getSurface() const
    {
        return mSurface;
    }
}