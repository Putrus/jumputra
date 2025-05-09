if(BUILD_TESTING)
   set(HEADERS
      inc/CharacterTest.hpp
      inc/EntityTest.hpp
      inc/SegmentsConnectorTest.hpp
      inc/SegmentTest.hpp
      inc/SelectionManagerTest.hpp
      )
   set(SOURCES
      src/CharacterTest.cpp
      src/DiagonalSegmentTest.cpp
      src/EntityTest.cpp
      src/GoalTest.cpp
      src/HorizontalSegmentTest.cpp
      src/PropertiesTest.cpp
      src/RunnableTest.cpp
      src/SegmentsConnectorTest.cpp
      src/SegmentTest.cpp
      src/SelectableTest.cpp
      src/SelectionManagerTest.cpp
      src/StatisticsTest.cpp
      src/VerticalSegmentTest.cpp
      src/WindTest.cpp
      )

   find_package(GTest CONFIG REQUIRED)

   add_executable(jp_ut_logic ${HEADERS} ${SOURCES})

   target_link_libraries(jp_ut_logic PRIVATE GTest::gmock_main GTest::gtest_main jp_logic)

   include(GoogleTest)
   gtest_discover_tests(jp_ut_logic)
endif()