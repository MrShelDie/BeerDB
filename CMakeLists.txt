cmake_minimum_required(VERSION 3.10)

project(BeerDB VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

include_directories(
    ${CMAKE_SOURCE_DIR}/db/deps/cereal-1.3.2/include
    ${CMAKE_SOURCE_DIR}/db/src
)

#Find all files in BeerDB
set(DB_SRC_DIR ${CMAKE_SOURCE_DIR}/db/src)
file (GLOB DB_SRC "${DB_SRC_DIR}/*")

set(GUI_SRC
        ${CMAKE_CURRENT_LIST_DIR}/gui/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/gui/mainwindow.cpp
        ${CMAKE_CURRENT_LIST_DIR}/gui/mainwindow.h
        ${CMAKE_CURRENT_LIST_DIR}/gui/mainwindow.ui
)

add_executable(BeerDB ${GUI_SRC} ${DB_SRC})

target_link_libraries(BeerDB PRIVATE Qt${QT_VERSION_MAJOR}::Widgets stdc++fs pthread)
