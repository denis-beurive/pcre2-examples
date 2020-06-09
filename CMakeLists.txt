cmake_minimum_required(VERSION 3.10)
project(pcre2 C)

# Configure the search path for extra header files that are not located in the default search path for header files.
include_directories(lib/pcre2/include)

# Configure the search path for extra libraries that are not located in the default search path for libraries.
link_directories(lib/pcre2/lib)

set(CMAKE_C_STANDARD 99)

add_executable(match1 src/match1.c)
target_link_libraries(match1 pcre2-8)
set_target_properties(
        match1
        PROPERTIES
        COMPILE_FLAGS  -Wall
        RUNTIME_OUTPUT_DIRECTORY bin
        EXCLUDE_FROM_ALL off)
