cmake_minimum_required(VERSION 3.10)

project(qt-candle-plugin LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core SerialBus)
if (NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Core SerialBus REQUIRED)
    set(QT_VERSION_MAJOR 5)
else()
    set(QT_VERSION_MAJOR 6)
endif()

add_subdirectory(candle_api/src)

add_subdirectory(src)
