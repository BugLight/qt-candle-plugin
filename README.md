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

## Usage 

 - Copy your qt-candle-plugin.dll to the Qt installation/plugins/canbus folder.
 - Make sure you are copying the plugin built in the same mode as your application uses (Debug mode built plugin will not be loaded in Relase built applications)
 - Copy the candle_api.dll from the build folder to a path which is in your application's library load path (next to the executable for e.g.)
