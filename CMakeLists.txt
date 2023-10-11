cmake_minimum_required(VERSION 3.8)
project(TextureGeneration)

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -march=native -pthread -O3")

set(PLATFORM_SPECIFIC_LIBS "-lpthread")

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(inc)

set(SRCSEfrosLeung
    mainEfrosLeung.cpp
    EfrosLeung.cpp
)

set(SRCSKMeans
    mainKMean.cpp
)


find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package(OpenMP REQUIRED)


add_executable(run ${SRCSEfrosLeung})

add_executable(runKMean ${SRCSKMeans})

target_link_libraries(run ${OpenCV_LIBS} )
target_link_libraries(runKMean ${OpenCV_LIBS} )
target_link_libraries(run OpenMP::OpenMP_CXX)
target_link_libraries(runKMean OpenMP::OpenMP_CXX)