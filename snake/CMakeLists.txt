cmake_minimum_required(VERSION 3.28)

project(sfmlsnake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(windows false)
set(sfmlversion "SFML-2.6.2")

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
    source/mainmenuheader.h
)

set_property(TARGET ${PROJECT_NAME} PROPERTY INSTALL_RPATH $ORIGIN)

target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${sfmlversion}/lib)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${sfmlversion}/include)

set(DCMAKE_INSTALL_PREFIX:PATH=.)

add_subdirectory(tinyfiledialogs)
target_link_libraries(${PROJECT_NAME} tinyfiledialogs)

set(CMAKE_INSTALL_PREFIX .)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION snake)
install(DIRECTORY rsc DESTINATION snake)
install(FILES ../README.md DESTINATION snake)
install(FILES ../updatelogs.md DESTINATION snake)

# Automatically put proper .so or .dll files in the install directory. This is not automated, and requires the dev to name the SFML folder "SFML".
# However, as this is a small project, and I am not planning to add more libraries (apart from  sfml-audio), or update to SFML 3.0.0, I reckon this is fine.
# This could be automated by checking what libraries my exe needs, and pulling that list, and putting it here, but this is easier.
# I am doing this since this only concerns the installation process, not any build processes.
if(windows)
    message(STATUS "Set to Windows")
    install(FILES ${sfmlversion}/bin/sfml-system-2.dll DESTINATION snake)
    install(FILES ${sfmlversion}/bin/sfml-window-2.dll DESTINATION snake)
    install(FILES ${sfmlversion}/bin/sfml-graphics-2.dll DESTINATION snake)
endif(windows)
if(NOT windows)
    message(STATUS "Set to Linux")
    install(FILES ${sfmlversion}/lib/libsfml-system.so.2.6.2 DESTINATION snake RENAME libsfml-system.so.2.6)
    install(FILES ${sfmlversion}/lib/libsfml-window.so.2.6.2 DESTINATION snake RENAME libsfml-window.so.2.6)
    install(FILES ${sfmlversion}/lib/libsfml-graphics.so.2.6.2 DESTINATION snake RENAME libsfml-graphics.so.2.6)
endif(NOT windows)

###TO DO:
# make a cmake configure variable for the current date and version number, and use it everywhere from here instead of using it manually everywhere