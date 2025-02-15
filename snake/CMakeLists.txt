cmake_minimum_required(VERSION 3.28)

project(sfmlsnake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_executable(${PROJECT_NAME}
    source/gameloop.cpp
    source/gameloopgetplayername.cpp
    source/leaderboardmenu.cpp
    source/mainmenu.cpp
    source/mainmenufunctions.cpp
    source/settingsmenu.cpp
    source/snake.cpp
    source/txtfiles.cpp 
    source/mainheader.h
    source/mainmenuheader.h)

add_subdirectory(tinyfiledialogs)