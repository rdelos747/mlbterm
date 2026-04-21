# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(mlbterm)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set the C++ version
set(CMAKE_CXX_STANDARD 20)

# Set the C++ compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -w")

include(FetchContent)
FetchContent_Declare(
    cpr 
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.12.0
)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(
    json 
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Find all .cpp source files in the src directory
file(GLOB SRCS "${CMAKE_SOURCE_DIR}/src/*.cpp")

message(STATUS "Source files: ${SRCS}")

# Add the executable target
add_executable(mlbterm ${SRCS})

# Link the required libraries
target_link_libraries(mlbterm ncurses panel cpr::cpr nlohmann_json::nlohmann_json) 

target_include_directories(mlbterm PRIVATE)