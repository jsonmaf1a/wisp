cmake_minimum_required(VERSION 3.28)
project(Wisp LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE WISP_SOURCES src/*.cpp)

add_library(Wisp STATIC ${WISP_SOURCES})
target_compile_features(Wisp PRIVATE cxx_std_23)
target_include_directories(Wisp PUBLIC include/)
target_link_libraries(Wisp PUBLIC SFML::Window SFML::Graphics SFML::System)

add_executable(wisp_dev src/main.cpp)
target_link_libraries(wisp_dev PRIVATE Wisp)
target_include_directories(wisp_dev PRIVATE include/)
