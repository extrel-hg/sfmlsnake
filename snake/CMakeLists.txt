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
    source/mainmenuheader.h
)

#set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH $ORIGIN)
#set(_rpath_portable_origin $ORIGIN)

set_property(TARGET ${PROJECT_NAME} PROPERTY INSTALL_RPATH $ORIGIN)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SFML/include)

add_subdirectory(tinyfiledialogs)
target_link_libraries(${PROJECT_NAME} tinyfiledialogs)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
include(CPack)