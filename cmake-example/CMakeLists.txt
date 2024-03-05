cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(rubbler-verilator-example)

find_package(verilator REQUIRED)

include(ExternalProject)
ExternalProject_Add(
	rubbler
	GIT_REPOSITORY https://github.com/fuad1502/rubbler.git
	DOWNLOAD_DIR ${CMAKE_BINARY_DIR}
	SOURCE_DIR ${CMAKE_BINARY_DIR}/rubbler
	BINARY_DIR ${CMAKE_BINARY_DIR}/rubbler
	CONFIGURE_COMMAND ""
	INSTALL_COMMAND ""
	BUILD_COMMAND cargo build --release
)
set(RUBBLER_LIB ${CMAKE_BINARY_DIR}/rubbler/target/release/librubbler.a)

add_executable(main main.cpp)
target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR}/rubbler)
target_link_libraries(main PRIVATE ${RUBBLER_LIB})
verilate(main SOURCES top.sv)
