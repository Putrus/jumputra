#include "../inc/SegmentTest.hpp"

namespace jp::ut::logic
{
   using namespace jp::logic;

   class MockSegment final : public Segment
   {
   public:
      MockSegment() : Segment(0.f, 0.f, 0.f, 0.f) {}

      MockSegment(float aX, float aY, float bX, float bY,
         SegmentSurface surface = SegmentSurface::Ordinary)
         : Segment(aX, aY, bX, bY, surface) {}
      
      MockSegment(const math::Vector2<float>& a, const math::Vector2<float>& b,
         SegmentSurface surface = SegmentSurface::Ordinary)
         : Segment(a, b, surface) {}

      SegmentCollision checkCollision(const math::Rect<float>&, const math::Rect<float>&) const
      {
         return SegmentCollision::No;
      };
   };

   TEST_F(SegmentTest, ConstructorFourArguments)
   {
      mSegment = new MockSegment(10.f, 15.f, 20.f, 25.f);

      EXPECT_EQ(10.f, mSegment->a.x);
      EXPECT_EQ(15.f, mSegment->a.y);
      EXPECT_EQ(20.f, mSegment->b.x);
      EXPECT_EQ(25.f, mSegment->b.y);
   }

   TEST_F(SegmentTest, ConstructorThreeArguments)
   {
      mSegment = new MockSegment(math::Vector2<float>(10.f, 15.f),
         math::Vector2<float>(20.f, 25.f));

      EXPECT_EQ(10.f, mSegment->a.x);
      EXPECT_EQ(15.f, mSegment->a.y);
      EXPECT_EQ(20.f, mSegment->b.x);
      EXPECT_EQ(25.f, mSegment->b.y);
   }

   TEST_F(SegmentTest, FromJson)
   {
      nlohmann::json json = nlohmann::json::parse(R"(
         {
            "a": {
               "x": 3.5,
               "y": 4.5
            },
            "b": {
               "x": 5.5,
               "y": 6.5
            },
            "surface": 0
         }
         )");

      mSegment = new MockSegment();
      ASSERT_NO_THROW(mSegment->fromJson(json));

      EXPECT_EQ(math::Vector2<float>(3.5f, 4.5f), mSegment->a);
      EXPECT_EQ(math::Vector2<float>(5.5f, 6.5f), mSegment->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegment->getSurface());
   }

   TEST(SegmentSurfaceTest, OstreamOperatorOrdinary)
   {
      SegmentSurface surface = SegmentSurface::Ordinary;

      std::stringstream ss;
      ss << surface;
      EXPECT_EQ("Ordinary", ss.str());
   }

   TEST(SegmentSurfaceTest, OstreamOperatorSlippery)
   {
      SegmentSurface surface = SegmentSurface::Slippery;

      std::stringstream ss;
      ss << surface;
      EXPECT_EQ("Slippery", ss.str());
   }

   TEST(SegmentSurfaceTest, OstreamOperatorSticky)
   {
      SegmentSurface surface = SegmentSurface::Sticky;

      std::stringstream ss;
      ss << surface;
      EXPECT_EQ("Sticky", ss.str());
   }

   TEST(SegmentSurfaceTest, OstreamOperatorUnknown)
   {
      SegmentSurface surface = static_cast<SegmentSurface>(99);

      std::stringstream ss;
      ss << surface;
      EXPECT_EQ("Unknown", ss.str());
   }

   TEST(SegmentCollisionTest, OstreamOperatorAttic)
   {
      SegmentCollision collision = SegmentCollision::Attic;

      std::stringstream ss;
      ss << collision;
      EXPECT_EQ("Attic", ss.str());
   }

   TEST(SegmentCollisionTest, OstreamOperatorBottom)
   {
      SegmentCollision collision = SegmentCollision::Bottom;

      std::stringstream ss;
      ss << collision;
      EXPECT_EQ("Bottom", ss.str());
   }

   TEST(SegmentCollisionTest, OstreamOperatorLeft)
   {
      SegmentCollision collision = SegmentCollision::Left;

      std::stringstream ss;
      ss << collision;
      EXPECT_EQ("Left", ss.str());
   }

   TEST(SegmentCollisionTest, OstreamOperatorNo)
   {
      SegmentCollision collision = SegmentCollision::No;

      std::stringstream ss;
      ss << collision;
      EXPECT_EQ("No", ss.str());
   }

   TEST(SegmentCollisionTest, OstreamOperatorRight)
   {
      SegmentCollision collision = SegmentCollision::Right;

      std::stringstream ss;
      ss << collision;
      EXPECT_EQ("Right", ss.str());
   }

   TEST(SegmentCollisionTest, OstreamOperatorRoof)
   {
      SegmentCollision collision = SegmentCollision::Roof;

      std::stringstream ss;
      ss << collision;
      EXPECT_EQ("Roof", ss.str());
   }

   TEST(SegmentCollisionTest, OstreamOperatorTop)
   {
      SegmentCollision collision = SegmentCollision::Top;

      std::stringstream ss;
      ss << collision;
      EXPECT_EQ("Top", ss.str());
   }

   TEST(SegmentCollisionTest, OstreamOperatorUnknown)
   {
      SegmentCollision collision = static_cast<SegmentCollision>(99);

      std::stringstream ss;
      ss << collision;
      EXPECT_EQ("Unknown", ss.str());
   }
}