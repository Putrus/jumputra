# CMakeList.txt : CMake project for Jumputra, include source and define
# project specific logic here.
#


# Libraries
#SFML
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR ../ext/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML 2.5.1 COMPONENTS graphics window audio REQUIRED)

# Add source to this project's executable.
add_executable (Jumputra "Main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Jumputra PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

target_link_libraries(Jumputra PRIVATE sfml-graphics sfml-window sfml-audio)
