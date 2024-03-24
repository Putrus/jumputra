#pragma once

#include "BodyUpdater.hpp"
#include "Properties.hpp"
#include "WindUpdater.hpp"

#include "../../inc/Updatable.hpp"

namespace jp::game::physics
{
   class Physics : public Updatable
   {
   public:
      Physics(const Properties& properties);
      Physics(const Properties& properties, std::vector<std::shared_ptr<Body>>&& bodies,
         std::vector<std::shared_ptr<Segment>>&& segments, std::vector<std::shared_ptr<Wind>>&& winds);

      void update(float dt) override;

      void addBody(const std::shared_ptr<Body>& body);
      void addSegment(const std::shared_ptr<Segment>& segment);
      void addWind(const std::shared_ptr<Wind>& wind);

      const std::vector<std::shared_ptr<Body>>& getBodies() const;
      const std::vector<std::shared_ptr<Segment>>& getSegments() const;
      const std::vector<std::shared_ptr<Wind>>& getWinds() const;

   private:
      void updateBodies(float dt);
      void updateWinds(float dt);

      const Properties& mProperties;

      std::vector<std::shared_ptr<Body>> mBodies;
      std::vector<std::shared_ptr<Segment>> mSegments;
      std::vector<std::shared_ptr<Wind>> mWinds;

      BodyUpdater mBodyUpdater;
      WindUpdater mWindUpdater;
   };
}