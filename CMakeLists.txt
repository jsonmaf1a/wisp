cmake_minimum_required(VERSION 3.28)
project(Wisp LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
target_compile_definitions(Wisp PRIVATE $<$<CONFIG:Debug>:DEBUG>)
target_compile_features(Wisp PRIVATE cxx_std_26)
target_include_directories(Wisp PUBLIC include/)
target_link_libraries(Wisp PUBLIC SFML::Window SFML::Graphics SFML::System)

add_executable(wisp_dev src/main.cpp)
target_link_libraries(wisp_dev PRIVATE Wisp)
target_include_directories(wisp_dev PRIVATE include/)
