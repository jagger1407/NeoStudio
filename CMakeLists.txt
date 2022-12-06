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
  # These are necessary for the program to work with the Qt Framework
  src/external/qt_includes.h
  # src
  # This is where the main logic is
  src/main.cpp
  src/neo_info.h
  # external
  # These are the classes that are general purpose,
  # or classes that write externally (i.e. files)
  src/external/fileparse.cpp
  src/external/debug.cpp
  src/external/bitmanipulation.h
  src/external/optionprocessing.h
  # fs
  # These classes are for all the logic concerning the .pak file specifically
  src/pak_filesystem/parameterfile.h
  src/pak_filesystem/generalparameters.cpp
  src/pak_filesystem/meleeparameters.cpp
  src/pak_filesystem/pakcontrols.cpp
  # ui
  # These classes are all the UI Dialogs/Windows that this program has
  src/ui/neostudio.cpp
  src/ui/menu/aboutwindow.cpp
  src/ui/menu/optiondialog.cpp
  src/ui/paramSections/generalframe.cpp
  src/ui/paramSections/meleeframe.cpp
)

# Tell CMake to create the executable
add_executable(neostudio ${neostudio_SRC})

# Use the Widgets module from Qt 5.
target_link_libraries(neostudio Qt5::Widgets)

# Install the executable
install(TARGETS neostudio DESTINATION bin)
