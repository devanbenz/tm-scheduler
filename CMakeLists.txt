cmake_minimum_required(VERSION 3.30)
project(tm_scheduler)

set(CMAKE_CXX_STANDARD 23)

find_package(Arrow REQUIRED)

include(FetchContent)
FetchContent_Declare(
        gRPC
        GIT_REPOSITORY https://github.com/grpc/grpc
        GIT_TAG v1.28.0
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(gRPC)

add_executable(tm_scheduler main.cpp
        src/include/models.h)
target_link_libraries(tm_scheduler PRIVATE Arrow::arrow_shared)
target_link_libraries(tm_scheduler grpc++)