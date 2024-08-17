#include "../inc/SegmentsConnectorTest.hpp"

namespace jp::ut::logic
{
   using namespace jp::logic;

   TEST_F(SegmentsConnectorTest, HorizontalSegmentsTwoSeparable)
   {
      mSegments.push_back(Segment::create(10.f, 10.f, 100.f, 10.f));
      mSegments.push_back(Segment::create(102.f, 10.f, 500.f, 10.f));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(2, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 10.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(100.f, 10.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegments.at(0)->getSurface());
      EXPECT_EQ(math::Vector2<float>(102.f, 10.f), mSegments.at(1)->a);
      EXPECT_EQ(math::Vector2<float>(500.f, 10.f), mSegments.at(1)->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegments.at(1)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, HorizontalSegmentsTwoIntersecting)
   {
      mSegments.push_back(Segment::create(10.f, 10.f, 100.f, 10.f, SegmentSurface::Slippery));
      mSegments.push_back(Segment::create(50.f, 10.f, 1000.f, 10.f, SegmentSurface::Slippery));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(1, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 10.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(1000.f, 10.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Slippery, mSegments.at(0)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, HorizontalSegmentsTwoOnePixel)
   {
      mSegments.push_back(Segment::create(10.f, 10.f, 100.f, 10.f));
      mSegments.push_back(Segment::create(101.f, 10.f, 500.f, 10.f));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(1, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 10.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(500.f, 10.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegments.at(0)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, HorizontalSegmentsTwoDifferentSurfaces)
   {
      mSegments.push_back(Segment::create(10.f, 10.f, 100.f, 10.f, SegmentSurface::Slippery));
      mSegments.push_back(Segment::create(50.f, 10.f, 1000.f, 10.f, SegmentSurface::Sticky));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(2, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 10.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(100.f, 10.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Slippery, mSegments.at(0)->getSurface());
      EXPECT_EQ(math::Vector2<float>(50.f, 10.f), mSegments.at(1)->a);
      EXPECT_EQ(math::Vector2<float>(1000.f, 10.f), mSegments.at(1)->b);
      EXPECT_EQ(SegmentSurface::Sticky, mSegments.at(1)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, HorizontalSegmentsTwoFirstInside)
   {
      mSegments.push_back(Segment::create(50.f, 10.f, 80.f, 10.f));
      mSegments.push_back(Segment::create(10.f, 10.f, 100.f, 10.f));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(1, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 10.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(100.f, 10.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegments.at(0)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, HorizontalSegmentsTwoSecondInside)
   {
      mSegments.push_back(Segment::create(10.f, 10.f, 100.f, 10.f));
      mSegments.push_back(Segment::create(40.f, 10.f, 60.f, 10.f));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(1, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 10.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(100.f, 10.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegments.at(0)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, HorizontalSegmentsThree)
   {
      mSegments.push_back(Segment::create(10.f, 10.f, 100.f, 10.f, SegmentSurface::Slippery));
      mSegments.push_back(Segment::create(101.f, 10.f, 1000.f, 10.f, SegmentSurface::Slippery));
      mSegments.push_back(Segment::create(1001.f, 10.f, 2000.f, 10.f, SegmentSurface::Slippery));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(1, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 10.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(2000.f, 10.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Slippery, mSegments.at(0)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, VerticalSegmentsTwoSeparable)
   {
      mSegments.push_back(Segment::create(20.f, 10.f, 20.f, 200.f));
      mSegments.push_back(Segment::create(20.f, 400.f, 20.f, 215.f));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(2, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(20.f, 10.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(20.f, 200.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegments.at(0)->getSurface());
      EXPECT_EQ(math::Vector2<float>(20.f, 215.f), mSegments.at(1)->a);
      EXPECT_EQ(math::Vector2<float>(20.f, 400.f), mSegments.at(1)->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegments.at(1)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, VerticalSegmentsTwoIntersecting)
   {
      mSegments.push_back(Segment::create(10.f, 20.f, 10.f, 200.f, SegmentSurface::Sticky));
      mSegments.push_back(Segment::create(10.f, 100.f, 10.f, 300.f, SegmentSurface::Sticky));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(1, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 20.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(10.f, 300.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Sticky, mSegments.at(0)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, VerticalSegmentsTwoOnePixel)
   {
      mSegments.push_back(Segment::create(10.f, 20.f, 10.f, 200.f, SegmentSurface::Sticky));
      mSegments.push_back(Segment::create(10.f, 201.f, 10.f, 400.f, SegmentSurface::Sticky));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(1, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 20.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(10.f, 400.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Sticky, mSegments.at(0)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, VerticalSegmentsTwoDifferentSurfaces)
   {
      mSegments.push_back(Segment::create(10.f, 20.f, 10.f, 200.f, SegmentSurface::Sticky));
      mSegments.push_back(Segment::create(10.f, 100.f, 10.f, 300.f, SegmentSurface::Slippery));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(1, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 20.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(10.f, 300.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Sticky, mSegments.at(0)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, VerticalSegmentsThree)
   {
      mSegments.push_back(Segment::create(10.f, 10.f, 10.f, 100.f, SegmentSurface::Sticky));
      mSegments.push_back(Segment::create(10.f, 101.f, 10.f, 1000.f, SegmentSurface::Sticky));
      mSegments.push_back(Segment::create(10.f, 1001.f, 10.f, 2000.f, SegmentSurface::Sticky));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(1, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 10.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(10.f, 2000.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Sticky, mSegments.at(0)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, DiagonalSegmentsTwoSeparable)
   {
      mSegments.push_back(Segment::create(10.f, 10.f, 100.f, 100.f));
      mSegments.push_back(Segment::create(102.f, 102.f, 200.f, 200.f));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(2, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 10.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(100.f, 100.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegments.at(0)->getSurface());
      EXPECT_EQ(math::Vector2<float>(102.f, 102.f), mSegments.at(1)->a);
      EXPECT_EQ(math::Vector2<float>(200.f, 200.f), mSegments.at(1)->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegments.at(1)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, DiagonalSegmentsTwoIntersecting)
   {
      mSegments.push_back(Segment::create(10.f, 10.f, 100.f, 100.f, SegmentSurface::Sticky));
      mSegments.push_back(Segment::create(60.f, 60.f, 200.f, 200.f, SegmentSurface::Sticky));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(1, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 10.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(200.f, 200.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Sticky, mSegments.at(0)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, DiagonalSegmentsTwoOnePixel)
   {
      mSegments.push_back(Segment::create(10.f, 10.f, 100.f, 100.f));
      mSegments.push_back(Segment::create(101.f, 101.f, 200.f, 200.f));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(1, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 10.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(200.f, 200.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Ordinary, mSegments.at(0)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, DiagonalSegmentsTwoDifferentSurfaces)
   {
      mSegments.push_back(Segment::create(10.f, 10.f, 100.f, 100.f, SegmentSurface::Slippery));
      mSegments.push_back(Segment::create(60.f, 60.f, 200.f, 200.f, SegmentSurface::Sticky));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(1, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 10.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(200.f, 200.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Slippery, mSegments.at(0)->getSurface());
   }

   TEST_F(SegmentsConnectorTest, DiagonalSegmentsThree)
   {
      mSegments.push_back(Segment::create(10.f, 10.f, 100.f, 100.f, SegmentSurface::Slippery));
      mSegments.push_back(Segment::create(60.f, 60.f, 200.f, 200.f, SegmentSurface::Sticky));
      mSegments.push_back(Segment::create(201.f, 201.f, 400.f, 400.f, SegmentSurface::Ordinary));

      SegmentsConnector::connect(mSegments);
      ASSERT_EQ(1, mSegments.size());
      EXPECT_EQ(math::Vector2<float>(10.f, 10.f), mSegments.at(0)->a);
      EXPECT_EQ(math::Vector2<float>(400.f, 400.f), mSegments.at(0)->b);
      EXPECT_EQ(SegmentSurface::Slippery, mSegments.at(0)->getSurface());
   }
}