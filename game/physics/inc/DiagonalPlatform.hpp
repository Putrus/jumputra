#include "Platform.hpp"

namespace jp::game::physics
{
    class DiagonalPlatform final : public Platform
    {
    public:
        DiagonalPlatform(const math::Segment<float>& segment, PlatformSurface surface);

        virtual PlatformCollision checkCollision(const math::Rect<float>& oldRect,
            const math::Rect<float>& newRect) const override;

    private:
        bool checkCollision(math::Vector2<float> a, math::Vector2<float> b) const;
    };
}