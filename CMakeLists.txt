cmake_minimum_required(VERSION 3.5)
project(SBO)

add_executable(sbo
    src/main.cpp
    src/game_server.cpp
    src/game_client.cpp)
target_link_libraries(sbo
    ws2_32
    boost_system-mt
    wsock32)
target_include_directories(sbo PUBLIC
    ext/websocketpp
    ext/nlohmann/single_include)
set_target_properties(sbo
    PROPERTIES CXX_STANDARD 17)
target_compile_options(sbo PRIVATE
    "$<$<CONFIG:DEBUG>:-Wa,-mbig-obj>")