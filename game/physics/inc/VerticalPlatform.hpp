#include "Platform.hpp"

namespace jp::game::physics
{
    class VerticalPlatform final : public Platform
    {
    public:
        VerticalPlatform(const math::Segment<float>& segment, Surface surface);
        virtual Collision checkCollision(const math::Rect<float>& oldRect,
            const math::Rect<float>& newRect) const override;

    private:
        bool checkCollision(math::Vector2<float> a, math::Vector2<float> b) const;
    };
}