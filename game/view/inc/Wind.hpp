#pragma once

#include <SFML/Graphics.hpp>

#include "../../physics/inc/Wind.hpp"

namespace jp::game::view
{
    class Wind : public sf::Drawable
    {
    public:
        Wind(const std::shared_ptr<physics::Wind>& physicsWind);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void update(float dt);

    private:
        sf::Sprite mSprite;
        std::unique_ptr<sf::Texture> mTexture;
        std::shared_ptr<physics::Wind> mPhysicsWind;
    };
}