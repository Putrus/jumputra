#pragma once

#include "CharacterProperties.hpp"

#include "../../physics/inc/Entity.hpp"

#include <memory>

namespace jp::game::engine
{
    enum class CharacterJumpDirection
    {
        Up = 0,
        Left,
        Right
    };

    class Character
    {
    public:
        Character(const std::shared_ptr<physics::Entity>& entity, const CharacterProperties& properties);
        Character& operator=(const Character& other);

        void update(float dt);

        bool canMove() const;
        bool isDying() const;
        bool isSquating() const;

        void jump();
        void squat();
        void stop();
        void runLeft();
        void runRight();

        const math::Rect<float>& getRect() const;
        const math::Vector2<float>& getPosition() const;
        CharacterJumpDirection getJumpDirection() const;

        void setJumpDirection(CharacterJumpDirection jumpDirection);

        void printInfo();
    private:
        std::shared_ptr<physics::Entity> mEntity;
        CharacterJumpDirection mJumpDirection = CharacterJumpDirection::Up;
        math::Vector2<float> mJumpPower = math::Vector2<float>();
        const CharacterProperties& mProperties;
    };
}