#include "../inc/Platform.hpp"

namespace jp::game::physics
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