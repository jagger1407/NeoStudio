cmake_minimum_required(VERSION 3.0)
project(NeoStudio)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to create code from Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

set(neostudio_SRC
  # qt libraries
  src/qt_includes.h
  # src
  src/main.cpp
  src/fileparse.cpp
  src/debug.cpp
  src/flagbyte.h
  src/pakcontrols.cpp
  # ui
  src/ui/neostudio.cpp
  src/ui/generalframe.cpp
  src/ui/aboutwindow.cpp
  # game logic
  src/neo_info.h
)

# Tell CMake to create the executable
add_executable(neostudio ${neostudio_SRC})

# Use the Widgets module from Qt 5.
target_link_libraries(neostudio Qt5::Widgets)

# Install the executable
install(TARGETS neostudio DESTINATION bin)
