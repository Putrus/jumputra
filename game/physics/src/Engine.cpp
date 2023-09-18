#include "../inc/Engine.hpp"

namespace jp::game::physics
{
    void Engine::update(float dt)
    {
        math::Vector2<float> globalAcceleration = math::Vector2<float>(mWind->getAcceleration() +
            math::Vector2<float>(0.f, mGravity));
        for (auto& entity : mEntities)
        {
            Entity newEntity = *entity;
            newEntity.setVelocity(newEntity.getVelocity() + (newEntity.getAcceleration() + globalAcceleration) * dt);
            newEntity.move((entity->getVelocity() + newEntity.getVelocity()) * dt / 2.f);
            for (const auto& platform : mPlatforms)
            {
                if (platform->getSegment().a.y > newEntity.getPosition().y + mCheckCollisionDistance)
                {
                    continue;
                }

                if(platform->getSegment().a.y < newEntity.getPosition().y - mCheckCollisionDistance)
                {
                    break;
                }

                Collision collision = platform->checkCollision(entity->getRect(), newEntity.getRect());
                switch(collision)
                {
                    case Collision::No:
                    break;
                    case Collision::Left:
                    {
                        newEntity.setRectLeft(platform->getSegment().b.x);
                        newEntity.setVelocityX(-entity->getVelocity().x * mBounce);
                        break;
                    }
                    case Collision::Right:
                    {
                        newEntity.setRectRight(platform->getSegment().a.x);
                        newEntity.setVelocityX(-entity->getVelocity().x * mBounce);
                        break;
                    }
                    case Collision::Top:
                    {
                        newEntity.setRectTop(platform->getSegment().b.y);
                        newEntity.setVelocityY(0.f);
                        break;
                    }
                    case Collision::Bottom:
                    {
                        newEntity.setRectBottom(platform->getSegment().a.y);
                        newEntity.setVelocityY(0.f);
                        break;
                    }
                    case Collision::Attic:
                    {
                        std::cout << "Collision attic!" << std::endl;
                        break;
                    }
                    case Collision::Roof:
                    {
                        std::cout << "Collision roof!" << std::endl;
                        break;
                    }
                }
            }
        }
    }
}