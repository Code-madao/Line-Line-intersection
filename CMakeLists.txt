cmake_minimum_required(VERSION 3.16)

project(INTLINELINE CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# cmake default build type is RelWithDebInfo
# set(CMAKE_BUILD_TYPE "RelWithDebInfo")

# aux_source_directory(src SRCS) #automatically recognize source files in directory "src" and set the variable "SRCS"
# aux_source_directory(. SRC_CURRENT) 

file(GLOB_RECURSE SRCS "./src/*.c" "./src/*.cpp")
# file(GLOB_RECURSE SRCS "./src/*.c" "./src/*.cpp" "./include/glm/detail/*.cpp")

add_executable(intLineLine ${SRCS})


# add_executable(intEE)
# target_sources(intEE PRIVATE ${SRCS})

target_include_directories(intLineLine PRIVATE "./include")