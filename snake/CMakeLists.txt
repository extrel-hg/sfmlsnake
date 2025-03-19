cmake_minimum_required(VERSION 3.28)

project(sfmlsnake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SFMLFOLDER "SFML-2.6.2")
set(INCLUDEDLLS)

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

if(INCLUDEDLLS)
    message(STATUS "Including .dlls (we are working on windows)")

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${SFMLFOLDER} buildsfml)

    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include/SFML)

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/buildsfml/lib/sfml-system-2.dll DESTINATION finishedsnake)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/buildsfml/lib/sfml-window-2.dll DESTINATION finishedsnake)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/buildsfml/lib/sfml-graphics-2.dll DESTINATION finishedsnake)

	target_link_options(${PROJECT_NAME} PRIVATE -mwindows)
	target_sources(${PROJECT_NAME} PRIVATE source/icon.rc)
	##Those two lines disable opening of console, and the adding of icon.rc to sources sets the icon
endif(INCLUDEDLLS)

if(NOT INCLUDEDLLS)
    message(STATUS "Including .so (we are working on linux)")
	
    install(FILES ${SFMLFOLDER}/lib/libsfml-system.so.2.6.2 DESTINATION finishedsnake RENAME libsfml-system.so.2.6)
    install(FILES ${SFMLFOLDER}/lib/libsfml-window.so.2.6.2 DESTINATION finishedsnake RENAME libsfml-window.so.2.6)
    install(FILES ${SFMLFOLDER}/lib/libsfml-graphics.so.2.6.2 DESTINATION finishedsnake RENAME libsfml-graphics.so.2.6)
	target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${SFMLFOLDER}/lib)
	target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${SFMLFOLDER}/include)

endif(NOT INCLUDEDLLS)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

add_subdirectory(tinyfiledialogs)
target_link_libraries(${PROJECT_NAME} tinyfiledialogs)

set(CMAKE_INSTALL_PREFIX .)
set_property(TARGET ${PROJECT_NAME} PROPERTY INSTALL_RPATH $ORIGIN)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION finishedsnake)
install(DIRECTORY rsc DESTINATION finishedsnake)
install(FILES ../README.md DESTINATION finishedsnake)
install(FILES ../updatelogs.md DESTINATION finishedsnake)
