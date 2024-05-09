if(BUILD_TESTING)
   set(HEADERS
      inc/CharactersLoaderTest.hpp
      inc/SegmentTest.hpp
      )
   set(SOURCES
      src/CharactersLoaderTest.cpp
      src/DiagonalSegmentTest.cpp
      src/EntityTest.cpp
      src/HorizontalSegmentTest.cpp
      src/VerticalSegmentTest.cpp
      )
   
   add_executable(jp_ut_logic ${HEADERS} ${SOURCES})

   target_link_libraries(jp_ut_logic PRIVATE GTest::gtest_main jp_logic)

   include(GoogleTest)
   gtest_discover_tests(jp_ut_logic)
endif()