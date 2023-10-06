#pragma once

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
        Character(std::shared_ptr<physics::Entity> entity);

        void update(float dt);

        bool canMove() const;

        void jump();
        void squat();
        void runLeft();
        void runRight();

        const math::Rect<float>& getRect() const;
        CharacterJumpDirection getJumpDirection() const;

        void setJumpDirection(CharacterJumpDirection jumpDirection);

    private:
        std::shared_ptr<physics::Entity> mEntity;
        CharacterJumpDirection mJumpDirection = CharacterJumpDirection::Up;
        float mJumpPower = 0.f;
    };
}