# qt-candle-plugin
Candle CAN bus plugin for Qt

# How to build

## Prerequisites

- Qt5 (can be downloaded from [official Qt website](https://www.qt.io/download-qt-installer))
- CMake >= 3.10
- Ninja (optional)

## Build instructions

1. Create the build directory `mkdir -p build && cd build`
2. Generate build files `cmake -G "Ninja" ..`. Or you could just use Unix Makefiles: `cmake ..`
3. Build the plugin `cmake --build .`
