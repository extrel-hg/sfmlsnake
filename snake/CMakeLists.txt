cmake_minimum_required(VERSION 3.28)
## Sets CMake minimum version

project(sfmlsnake)
## Defines project name (it could define stuff like versions, but I dont bother)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
## Sets standards

set(SFMLFOLDER "SFML-2.6.2")
set(INCLUDEDLLS)
## Defines some script variables

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
    source/2playergameloop.cpp
)
## Adds all source files

## This is ran when Windows is selected
if(INCLUDEDLLS)
    message(STATUS "Including .dlls (we are working on windows)")

    set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")
    ## Forces static linking of MinGW libraries, so no weird .dlls are needed

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${SFMLFOLDER} buildsfml)
    ## Adds SFML. Will build it automatically if not built yet.

    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include/SFML)
    ## Adds include directory of SFML

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/buildsfml/lib/sfml-system-2.dll DESTINATION finishedsnake)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/buildsfml/lib/sfml-window-2.dll DESTINATION finishedsnake)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/buildsfml/lib/sfml-graphics-2.dll DESTINATION finishedsnake)
    ## Defines the .dll files to put in finished snake

	target_link_options(${PROJECT_NAME} PRIVATE -mwindows)
	target_sources(${PROJECT_NAME} PRIVATE source/icon.rc)
	##Those two lines disable opening of console, and the adding of icon.rc to sources sets the icon

endif(INCLUDEDLLS)

## Linux build
if(NOT INCLUDEDLLS)
    message(STATUS "Including .so (we are working on linux)")
	
    install(FILES ${SFMLFOLDER}/lib/libsfml-system.so.2.6.2 DESTINATION finishedsnake RENAME libsfml-system.so.2.6)
    install(FILES ${SFMLFOLDER}/lib/libsfml-window.so.2.6.2 DESTINATION finishedsnake RENAME libsfml-window.so.2.6)
    install(FILES ${SFMLFOLDER}/lib/libsfml-graphics.so.2.6.2 DESTINATION finishedsnake RENAME libsfml-graphics.so.2.6)

	target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${SFMLFOLDER}/lib)
	target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${SFMLFOLDER}/include)
    ## Link and include pre-built SFML version

    set_property(TARGET ${PROJECT_NAME} PROPERTY INSTALL_RPATH $ORIGIN)
    ## Forces the finished app to look for .so files in its directory

endif(NOT INCLUDEDLLS)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
## Link sfml

add_subdirectory(tinyfiledialogs)
target_link_libraries(${PROJECT_NAME} tinyfiledialogs)
## Adds tinyfiledialogs

set(CMAKE_INSTALL_PREFIX .)
## Makes the default install location the current directory

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION finishedsnake)
install(DIRECTORY rsc DESTINATION finishedsnake)
install(FILES ../README.md DESTINATION finishedsnake)
install(FILES ../updatelogs.md DESTINATION finishedsnake)
## Adds resources to finishedsnake