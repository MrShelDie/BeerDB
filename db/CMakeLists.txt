cmake_minimum_required(VERSION 3.10)
project(MiniDB)
set(CMAKE_CXX_STANDARD 14)
include_directories(
    ${CMAKE_SOURCE_DIR}/deps/cereal-1.3.2/include
)
aux_source_directory(src source_list)
add_executable(minidb ${source_list})
target_link_libraries(minidb readline stdc++fs pthread)
