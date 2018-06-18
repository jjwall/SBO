cmake_minimum_required(VERSION 3.5)
project(SBO)

add_executable(sbo
    src/main.cpp)
target_link_libraries(sbo
    ws2_32
    boost_system-mt
    wsock32)
target_include_directories(sbo PUBLIC
    src/websocketpp
    src/nlohmann)
set_target_properties(sbo
    PROPERTIES CXX_STANDARD 17)