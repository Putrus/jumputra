if(BUILD_TESTING)
   set(HEADERS)
   set(SOURCES
      src/MathTest.cpp
      src/RectTest.cpp
      src/SegmentTest.cpp
      src/Vector2Test.cpp
      )

   find_package(GTest CONFIG REQUIRED)

   add_executable(jp_ut_math ${HEADERS} ${SOURCES})

   target_link_libraries(jp_ut_math PRIVATE GTest::gtest_main)
   
   include(GoogleTest)
   gtest_discover_tests(jp_ut_math)
endif()