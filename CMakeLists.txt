cmake_minimum_required(VERSION 3.28)
project(Wisp LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE WISP_SOURCES src/*.cpp)
add_executable(wisp ${WISP_SOURCES})

target_compile_features(wisp PRIVATE cxx_std_23)
target_include_directories(wisp PRIVATE include/)
target_link_libraries(wisp PRIVATE SFML::Window SFML::Graphics SFML::System)
