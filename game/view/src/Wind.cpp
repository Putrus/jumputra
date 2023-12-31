#include "../inc/Wind.hpp"

namespace jp::game::view
{
    Wind::Wind(const std::shared_ptr<physics::Wind>& physicsWind)
        : mPhysicsWind(physicsWind)
    {
        //hardcoded todo
        unsigned int width = 16384;
        unsigned int height = static_cast<unsigned int>(physicsWind->getRect().getBottom() - physicsWind->getRect().top);
        std::unique_ptr<sf::Image> img = std::make_unique<sf::Image>();
        img->create(width, height, sf::Color::Transparent);
        for (unsigned int i = 0; i < height; i += 33)
        {
            unsigned int j = 0;
            if (i % 2 == 0)
            {
                j = 32;
            }
            for (; j < width; j += 64)
            {
                img->setPixel(j, i, sf::Color::White);
            }
        }
        mTexture = std::make_unique<sf::Texture>();
        mTexture->loadFromImage(*img);
        mSprite.setTexture(*mTexture);
        mSprite.setPosition(-static_cast<float>(width / 2), mPhysicsWind->getRect().top);
    }
    void Wind::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mSprite);
    }

    void Wind::update(float dt)
    {
        sf::Vector2f moveVector;
        moveVector.x = mPhysicsWind->getVelocity().x * dt;
        mSprite.move(moveVector);
    }
}