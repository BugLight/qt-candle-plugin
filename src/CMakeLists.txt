cmake_minimum_required(VERSION 3.5)

add_library(qt-candle-plugin SHARED
  candlecanbusplugin.cpp
  candlecanbusplugin.h
  qt-candle-plugin.json
)

target_link_libraries(qt-candle-plugin PRIVATE Qt5::Core Qt5::SerialBus)

target_compile_definitions(qt-candle-plugin PRIVATE QTCANDLEPLUGIN_LIBRARY)
