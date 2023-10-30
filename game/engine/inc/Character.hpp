#pragma once

#include "CharacterProperties.hpp"

#include "../../physics/inc/Character.hpp"

#include <memory>

namespace jp::game::engine
{
    class Character
    {
    public:
        enum class Direction : int
        {
            Up = 0,
            Left,
            Right
        };
        Character(const std::shared_ptr<physics::Character>& physicsCharacter,
            const CharacterProperties& properties);
        Character& operator=(const Character& other);

        virtual void update(float dt);

        bool canRun() const;
        bool canSquat() const;
        bool isDying() const;
        bool isSquatting() const;

        void jump();
        void run(Direction direction);
        void squat();
        void stop();

        const math::Rect<float>& getRect() const;
        math::Vector2<float> getPosition() const;
        Direction getDirection() const;
        float getJumpPower() const;

        void setDirection(Direction direction);

        void printInfo();
    protected:
        std::shared_ptr<physics::Character> mPhysicsCharacter;
        Direction mDirection = Direction::Up;
        math::Vector2<float> mJumpPower = math::Vector2<float>();
        const CharacterProperties& mProperties = CharacterProperties();
    };

    class Bot : public Character
    {
    public:
        enum class State : int
        {
            Ready = 0,
            Jumping,
            Running
        };

        virtual void update(float dt) override;

        void jump(Direction direction, float percent);
        void run(Direction direction, float time);

    private:
        float mJumpPercent = 0.f;
        float mTime = 0.f;
        State mState;
    };
}