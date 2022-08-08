set(CMAKE_CXX_COMPILER g++)

project (arrow-report)

## CMake version
cmake_minimum_required(VERSION 3.14)

# Look for installed packages the system
find_package(Arrow REQUIRED)
find_package(Parquet REQUIRED PATHS ${Arrow_DIR} NO_DEFAULT_PATH)

## Use C++17 features
add_definitions(-std=c++17)

## Set dependencies
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fopenmp -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fopenmp -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable -Wno-unused-function -Wno-parentheses")

add_executable(main "src/main.cpp")

## Set include paths
include_directories(src)

set(LINK_LIB ${LINK_LIB} parquet_shared arrow_shared)

target_link_libraries(main PRIVATE ${LINK_LIB})
