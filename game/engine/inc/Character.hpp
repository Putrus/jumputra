#pragma once

#include "CharacterProperties.hpp"

#include "../physics/inc/Entity.hpp"

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
        Character(std::shared_ptr<physics::Entity> entity, const CharacterProperties& properties);

        void update(float dt);

        bool canMove() const;

        void jump();
        void squat();
        void stop();
        void runLeft();
        void runRight();

        const math::Rect<float>& getRect() const;
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