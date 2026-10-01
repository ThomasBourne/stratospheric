cmake_minimum_required(VERSION 3.28)
project(STRATOSPHERIC LANGUAGES CXX)

set(CMAKE_EXPORcmaT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)
add_definitions(-DSFML_STATIC)

add_executable(
    stratospheric
    src/main.cpp
    src/utility/utility.cpp

    src/game/contexts/splashscreen.cpp
    src/game/contexts/game.cpp
    
    src/engine/context/context.cpp
)
target_compile_features(stratospheric PRIVATE cxx_std_17)
target_link_libraries(stratospheric PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT stratospheric)
