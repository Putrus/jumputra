#include "../inc/Physics.hpp"

namespace jp::game::physics
{
   void Physics::update(float dt)
   {
      updateWinds(dt);
      updateBodies(dt);
   }

   void Physics::addBody(const std::shared_ptr<Body>& body)
   {
      mBodies.push_back(body);
   }

   void Physics::addSegment(const std::shared_ptr<Segment>& segment)
   {
      mSegments.push_back(segment);
   }
   
   void Physics::addWind(const std::shared_ptr<Wind>& wind)
   {
      mWinds.push_back(wind);
   }

   const std::vector<std::shared_ptr<Body>>& Physics::getBodies() const
   {
      return mBodies;
   }

   const std::vector<std::shared_ptr<Segment>>& Physics::getSegments() const
   {
      return mSegments;
   }

   const std::vector<std::shared_ptr<Wind>>& Physics::getWinds() const
   {
      return mWinds;
   }

   void Physics::updateBodies(float dt)
   {
      for (auto& body : mBodies)
      {
         mBodyUpdater.update(dt, *body, mProperties, mSegments, mWinds);
      }
   }

   void Physics::updateWinds(float dt)
   {
      for (auto& wind : mWinds)
      {
         mWindUpdater.update(dt, *wind);
      }
   }
}