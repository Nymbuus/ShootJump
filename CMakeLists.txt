cmake_minimum_required(VERSION 3.20)

project(ShootJump LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------------------------------
# Raylib
# --------------------------------------------------

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW TRUE
)

# Don't build Raylib's example programs
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)

# --------------------------------------------------
# Our executable
# --------------------------------------------------

add_executable(ShootJump
    src/main.cpp "src/Game.cpp" "src/Game.h" "src/Player.cpp" "src/Player.h" "src/Platform.cpp" "src/Platform.h" "src/Circle.h" "src/Gun.cpp" "src/Gun.h" "src/Bullet.cpp" "src/Bullet.h")

# Link Raylib to our program
target_link_libraries(ShootJump PRIVATE raylib)