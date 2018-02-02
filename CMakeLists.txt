cmake_minimum_required(VERSION 3.5)
project(echo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

find_library(muduo_net_cpp11 muduo_net)
find_library(muduo_base_cpp11 muduo_base_cpp11)

MESSAGE(STATUS ${muduo_base_cpp11})

add_executable(echo echo.cc echo.hpp)
target_link_libraries(${PROJECT_NAME} muduo_net_cpp11 muduo_base_cpp11 boost_system pthread)

add_executable(iopool_echo iopool_echo.cc iopool_echo.hpp)
target_link_libraries(iopool_echo muduo_net_cpp11 muduo_base_cpp11 boost_system pthread)

add_executable(bucket_echo bucket_echo.cc bucket_echo.hpp circuit_buffer.cc)
target_link_libraries(bucket_echo muduo_net_cpp11 muduo_base_cpp11 boost_system pthread)