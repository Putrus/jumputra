# CMakeList.txt : CMake project for Jumputra, include source and define
# project specific logic here.
#

# Add source to this project's executable.
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows2")
   add_executable (Jumputra WIN32 ${SOURCES} ${HEADERS})
else()
   add_executable (Jumputra ${SOURCES} ${HEADERS})
endif()

# CMake version
if (CMAKE_VERSION VERSION_GREATER 3.12)
   set_property(TARGET Jumputra PROPERTY CXX_STANDARD 20)
endif()

# Configuration
set(CONFIGURATION x86)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
   set(CONFIGURATION x64)
endif()

if (MSVC)
  #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
endif()

# Libraries
#SFML
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR ../ext/${CMAKE_SYSTEM_NAME}/${CONFIGURATION}/SFML-2.6.0/lib/cmake/SFML)
find_package(SFML 2.6.0 COMPONENTS graphics window audio REQUIRED)

target_link_libraries(Jumputra PRIVATE sfml-graphics sfml-window sfml-audio)
