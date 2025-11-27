cmake_minimum_required(VERSION 3.10)
project(ProfilerUtility VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Create a library for the profiler
add_library(profiler STATIC
    profiler.cpp
    profiler.h
)

target_include_directories(profiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Create the example executable
add_executable(profiler_example
    example.cpp
)

target_link_libraries(profiler_example PRIVATE profiler)

# Optional: Install targets
install(TARGETS profiler profiler_example
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES profiler.h DESTINATION include)
