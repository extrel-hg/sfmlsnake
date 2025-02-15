add_library(tinyfiledialogs tinyfiledialogs.c tinyfiledialogs.h)

target_include_directories(tinyfiledialogs
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})