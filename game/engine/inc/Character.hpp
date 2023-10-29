#pragma once

#include "CharacterProperties.hpp"

#include "../../physics/inc/Character.hpp"

#include <memory>

namespace jp::game::engine
{
    enum class CharacterDirection : int
    {
        Up = 0,
        Left,
        Right
    };

    class Character
    {
    public:
        Character(const std::shared_ptr<physics::Character>& entity, const CharacterProperties& properties);
        Character& operator=(const Character& other);

        void update(float dt);

        bool canRun() const;
        bool canSquat() const;
        bool isDying() const;
        bool isSquatting() const;

        void jump();
        void run(CharacterDirection direction);
        void squat();
        void stop();

        const math::Rect<float>& getRect() const;
        const math::Vector2<float>& getPosition() const;
        CharacterDirection getDirection() const;
        float getJumpPower() const;

        void setDirection(CharacterDirection direction);

        void printInfo();
    private:
        std::shared_ptr<physics::Character> mEntity;
        CharacterDirection mDirection = CharacterDirection::Up;
        math::Vector2<float> mJumpPower = math::Vector2<float>();
        const CharacterProperties& mProperties;
    };
}