cmake_minimum_required(VERSION 3.30)
include(FetchContent)
project(TmScheduler)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Python 3.13 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)
find_package(RocksDB CONFIG REQUIRED)
FetchContent_Declare(
        Crow
        GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
        GIT_TAG 94a011b9f7c0a991e5382927a2dbe5a7d9a056b8
)
FetchContent_MakeAvailable(Crow)
include(FetchContent)
FetchContent_Declare(cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG bb01c8db702fb41e5497aee9c0559ddf4bf13749
)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

add_library(protolib protos/api/v1/node.proto protos/api/v1/task_manager.proto protos/api/v1/common.proto)

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
target_link_libraries(tm_scheduler
        protolib
        spdlog::spdlog
        Crow::Crow
        RocksDB::rocksdb
)

add_library(metadata_store
        src/include/metadata.h
)
target_link_libraries(metadata_store RocksDB::rocksdb)

target_include_directories(tm_scheduler PUBLIC ${asio_DIR})

pybind11_add_module(PyTmSched
        src/control_plane/py_bindings.cpp
)

add_library(grpc_client
        src/utils/grpc_client.cpp
        src/include/grpc_client.h
)
target_link_libraries(grpc_client protolib)
target_include_directories(grpc_client PUBLIC ${Python_INCLUDE_DIRS})

target_link_libraries(PyTmSched PRIVATE grpc_client cpr::cpr nlohmann_json::nlohmann_json)

add_executable(control_plane
        src/control_plane/main.cpp
)
target_link_libraries(control_plane PUBLIC tm_scheduler grpc_client metadata_store)

add_executable(worker_node src/worker/main.cpp
        src/include/worker.h)
target_link_libraries(worker_node tm_scheduler)

add_executable(task_manager src/task_manager/main.cpp
        src/include/task_manager.h
        src/include/scheduler.h
        src/task_manager/rr_scheduler.cpp
        src/include/rr_scheduler.h
        src/task_manager/task_manager.cpp)
target_link_libraries(task_manager tm_scheduler metadata_store)
