cmake_minimum_required(VERSION 3.30)
include(FetchContent)
project(TmScheduler)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
FetchContent_Declare(
        Crow
        GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
        GIT_TAG 94a011b9f7c0a991e5382927a2dbe5a7d9a056b8
)

FetchContent_MakeAvailable(Crow)

add_library(protolib protos/api/v1/master.proto
        src/include/master.h)

target_link_libraries(protolib gRPC::grpc++)
target_include_directories(protolib PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)

protobuf_generate(TARGET protolib LANGUAGE CPP)
protobuf_generate(TARGET protolib LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")

add_library(tm_scheduler
        src/control_plane/api_server.cpp
        src/include/api_server.h
)
target_link_libraries(tm_scheduler protolib spdlog::spdlog Crow::Crow)
target_include_directories(tm_scheduler PUBLIC ${asio_DIR})

add_executable(control_plane src/control_plane/main.cpp)
target_link_libraries(control_plane tm_scheduler)

add_executable(master_node src/master/main.cpp)
target_link_libraries(master_node tm_scheduler)

add_executable(worker_node src/worker/main.cpp
        src/include/worker.h)
target_link_libraries(master_node tm_scheduler)

add_executable(task_manager src/task_manager/main.cpp
        src/include/task_manager.h
        src/include/scheduler.h
        src/task_manager/fifo_scheduler.cpp
        src/include/fifo_scheduler.h)
target_link_libraries(task_manager tm_scheduler)
