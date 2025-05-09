if(BUILD_TESTING)
   set(HEADERS)
   set(SOURCES
      src/PropertiesTest.cpp
      )

   find_package(GTest CONFIG REQUIRED)

   add_executable(jp_ut_algorithm ${HEADERS} ${SOURCES})

   target_link_libraries(jp_ut_algorithm PRIVATE GTest::gtest_main jp_algorithm)
   
   include(GoogleTest)
   gtest_discover_tests(jp_ut_algorithm)
endif()