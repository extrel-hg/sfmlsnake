cmake_minimum_required(VERSION 3.28)

project(sfmlsnake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(INCLUDEDLLS)
set(SFMLVERSION "SFML-2.6.2")

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

target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${SFMLVERSION}/lib)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${SFMLVERSION}/include)

add_subdirectory(tinyfiledialogs)
target_link_libraries(${PROJECT_NAME} tinyfiledialogs)

set(CMAKE_INSTALL_PREFIX .)
set_property(TARGET ${PROJECT_NAME} PROPERTY INSTALL_RPATH $ORIGIN)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION finishedsnake)
install(DIRECTORY rsc DESTINATION finishedsnake)
install(FILES ../README.md DESTINATION finishedsnake)
install(FILES ../updatelogs.md DESTINATION finishedsnake)

if(INCLUDEDLLS)
    message(STATUS "Including .dlls")
    install(FILES ${SFMLVERSION}/bin/sfml-system-2.dll DESTINATION finishedsnake)
    install(FILES ${SFMLVERSION}/bin/sfml-window-2.dll DESTINATION finishedsnake)
    install(FILES ${SFMLVERSION}/bin/sfml-graphics-2.dll DESTINATION finishedsnake)
endif(INCLUDEDLLS)

if(NOT INCLUDEDLLS)
    message(STATUS "Including .so")
    install(FILES ${SFMLVERSION}/lib/libsfml-system.so.2.6.2 DESTINATION finishedsnake RENAME libsfml-system.so.2.6)
    install(FILES ${SFMLVERSION}/lib/libsfml-window.so.2.6.2 DESTINATION finishedsnake RENAME libsfml-window.so.2.6)
    install(FILES ${SFMLVERSION}/lib/libsfml-graphics.so.2.6.2 DESTINATION finishedsnake RENAME libsfml-graphics.so.2.6)
endif(NOT INCLUDEDLLS)