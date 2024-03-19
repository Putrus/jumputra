if(BUILD_TESTING)
   set(HEADERS
      inc/SegmentTest.hpp
      )
   set(SOURCES
      src/DiagonalSegmentTest.cpp
      src/EntityTest.cpp
      src/HorizontalSegmentTest.cpp
      src/VerticalSegmentTest.cpp
      )
   
   add_executable(jp_ut_game_physics ${HEADERS} ${SOURCES})

   target_link_libraries(jp_ut_game_physics PRIVATE GTest::gtest_main jp_game_physics jp_math)

   include(GoogleTest)
   gtest_discover_tests(jp_ut_game_physics)
endif()