#include "../inc/Engine.hpp"

namespace jp::game::physics
{
    /*
    void Engine::update(float dt)
    {
        updateWind(dt);
        for (auto& entity : mEntities)
        {
            Entity newEntity = *entity;
            updateEntity(dt, newEntity);
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
                        if (entity->getState() == EntityState::Flying ||
                            entity->getState() == EntityState::Sliding)
                        {
                            newEntity.setVelocityX(-entity->getVelocity().x * mBounceFactor);
                        }
                        break;
                    }
                    case Collision::Right:
                    {
                        newEntity.setRectRight(platform->getSegment().a.x);
                        if (entity->getState() == EntityState::Flying ||
                            entity->getState() == EntityState::Sliding)
                        {
                            newEntity.setVelocityX(-entity->getVelocity().x * mBounceFactor);
                        }
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

    void Engine::updateEntity(float dt, Entity& entity) const
    {
        math::Vector2<float> oldVelocity = entity.getVelocity();
        entity.setVelocity(entity.getVelocity() + (entity.getAcceleration() + math::Vector2<float>(0.f, mGravity)) * dt);
        entity.move((oldVelocity + entity.getVelocity() + mWind->getVelocity()) * dt / 2.f);
    }

    void Engine::updateWind(float dt)
    {
        mWind->setVelocity(mWind->getVelocity() + mWind->getAcceleration() * dt);
        float absVelocity = std::abs(mWind->getVelocity().x);
        if (absVelocity >= mWind->getMaxVelocity().x)
        {
            mWind->setVelocity(mWind->getMaxVelocity() * (mWind->getVelocity().x / absVelocity));
            mWind->setAcceleration(mWind->getAcceleration() * -1.f);
        }
    }
    */
}