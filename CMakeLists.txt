cmake_minimum_required(VERSION 3.10)
project(pcre2 LANGUAGES C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_LINK_SEARCH_START_STATIC on)

# Configure the search path for extra header files that are not located in the default search path for header files.
include_directories(lib/pcre2/include)

# Configure the search path for extra libraries that are not located in the default search path for libraries.
link_directories(lib/pcre2/lib)

add_library(toolbox STATIC src/toolbox.c src/toolbox.h)
set_target_properties(
        toolbox
        PROPERTIES
        COMPILE_FLAGS  -Wall
        ARCHIVE_OUTPUT_DIRECTORY lib
        EXCLUDE_FROM_ALL off)

add_executable(match1 src/match1.c)
target_link_libraries(match1 pcre2-8)

add_executable(negative_look_ahead src/negative-look-ahead.c)
target_link_libraries(negative_look_ahead toolbox pcre2-8)

add_executable(positive_look_ahead src/positive-look-ahead.c)
target_link_libraries(positive_look_ahead toolbox pcre2-8)

add_executable(negative_look_behind src/negative-look-behind.c)
target_link_libraries(negative_look_behind toolbox pcre2-8)

add_executable(positive_look_behind src/positive-look-behind.c)
target_link_libraries(positive_look_behind toolbox pcre2-8)

add_executable(lazy src/lazy.c)
target_link_libraries(lazy toolbox pcre2-8)

add_executable(possessive src/possessive.c)
target_link_libraries(possessive toolbox pcre2-8)

set_target_properties(
        match1
        negative_look_ahead
        negative_look_behind
        positive_look_ahead
        positive_look_behind
        lazy
        possessive
        PROPERTIES
        COMPILE_FLAGS  -Wall
        RUNTIME_OUTPUT_DIRECTORY bin
        EXCLUDE_FROM_ALL off)
