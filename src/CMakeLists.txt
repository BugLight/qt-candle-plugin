cmake_minimum_required(VERSION 3.5)

add_library(qt-candle-plugin SHARED
  candlecanbusplugin.cpp
  candlecanbusplugin.h
  qt-candle-plugin.json
  candledevice.h
  candledevice.cpp
)

target_include_directories(qt-candle-plugin PRIVATE
  "${PROJECT_SOURCE_DIR}/candle_api/src"
)

target_link_libraries(qt-candle-plugin PRIVATE
  Qt5::Core
  Qt5::SerialBus
  candle_api
)

target_compile_definitions(qt-candle-plugin PRIVATE QTCANDLEPLUGIN_LIBRARY)
