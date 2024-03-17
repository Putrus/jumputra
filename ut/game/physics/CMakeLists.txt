if(BUILD_TESTING)
   set(HEADERS)
   set(SOURCES
      src/EntityTest.cpp
      )
   
   add_executable(jp_ut_game_physics ${HEADERS} ${SOURCES})

   target_link_libraries(jp_ut_game_physics PRIVATE GTest::gtest_main jp_game_physics)

   include(GoogleTest)
   gtest_discover_tests(jp_ut_game_physics)
endif()