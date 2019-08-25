cmake_minimum_required(VERSION 3.5)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY, ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_SKIP_INSTALL_RULES ON)

message("${CMAKE_CXX_COMPILER_ID}")

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set Definetions
if (CMAKE_BUILD_TYPE STREQUAL "Debug") 
    add_definitions(-D__DEBUG__)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")
if (CMAKE_BUILD_TYPE STREQUAL "Release") 
    add_definitions(-D__RELEASE__)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

# isogen
file(GLOB_RECURSE isogen_hdrs "src/*.h")
file(GLOB_RECURSE isogen_srcs "src/*.cpp")

add_executable(
    "isogen"

    ${isogen_hdrs}
    ${isogen_srcs}
)
