#include "Platform.hpp"

namespace jp::game::physics
{
    class HorizontalPlatform final : public Platform
    {
    public:
        HorizontalPlatform(const math::Segment<float>& segment, PlatformSurface surface);
        HorizontalPlatform(const math::Vector2<float>& a,
            const math::Vector2<float>& b, PlatformSurface surface);

        virtual PlatformCollision checkCollision(const math::Rect<float>& oldRect,
            const math::Rect<float>& newRect) const override;

    private:
        bool checkCollision(math::Vector2<float> a, math::Vector2<float> b) const;
    };
}