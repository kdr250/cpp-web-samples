cmake_minimum_required(VERSION 3.19)

if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    cmake_path(SET VCPKG_PATH NORMALIZE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
    set(CMAKE_TOOLCHAIN_FILE ${VCPKG_PATH} CACHE STRING "")
endif()

project(main VERSION 1.0)

find_package(gRPC CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>")

# just sets a variable containing all of our .proto files
set(PROTO_FILES "${CMAKE_CURRENT_LIST_DIR}/../proto/example.proto")

# myproto is a library we are creating to group our generated files and gRPC+protobuf dependencies
add_library(myproto OBJECT ${PROTO_FILES})
target_link_libraries(
    myproto PUBLIC
    protobuf::libprotobuf
    gRPC::grpc
    gRPC::grpc++
    gRPC::grpc++_reflection
)

set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(PROTO_IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/../proto")

target_include_directories(myproto PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")

protobuf_generate(
    TARGET myproto
    IMPORT_DIRS ${PROTO_IMPORT_DIRS}
    PROTOC_OUT_DIR "${PROTO_BINARY_DIR}"
)
protobuf_generate(
    TARGET myproto 
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
    IMPORT_DIRS ${PROTO_IMPORT_DIRS}
    PROTOC_OUT_DIR "${PROTO_BINARY_DIR}"
)

# Create our executable
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(
    main
    ${SOURCES}
)

# add "myproto" (generated protobuf files and gRPC libs) to the executable.
target_link_libraries(main PRIVATE myproto)

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:main>/resources
)
