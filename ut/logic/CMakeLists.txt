if(BUILD_TESTING)
   set(HEADERS
      inc/SegmentTest.hpp
      )
   set(SOURCES
      src/DiagonalSegmentTest.cpp
      src/EntityTest.cpp
      src/GoalTest.cpp
      src/HorizontalSegmentTest.cpp
      src/PropertiesTest.cpp
      src/RunnableTest.cpp
      src/SegmentTest.cpp
      src/SelectableTest.cpp
      src/VerticalSegmentTest.cpp
      src/WindTest.cpp
      )
   
   add_executable(jp_ut_logic ${HEADERS} ${SOURCES})

   target_link_libraries(jp_ut_logic PRIVATE GTest::gmock_main GTest::gtest_main jp_logic)

   include(GoogleTest)
   gtest_discover_tests(jp_ut_logic)
endif()