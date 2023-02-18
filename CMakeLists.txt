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

  # src/
  # this is where the main logic is,
  # including main, game-related data and option processing.
  
  # external/
  # All the handling (reading/writing) of external files is put here.
  
  # pak_filesystem/
  # The classes in here all relate to the parsing and
  # modification of data that stems from .pak character files.
  
  # ui/
  # This contains all the logic handling the UI Windows and Dialogs.

  # ::Qt files::
  src/external/qt_includes.h

  # ::header files::
  src/neo_info.h
  src/neo_info.h
  src/options.h
  src/external/fileparse.h
  src/external/debug.h
  src/external/bitmanipulation.h
  src/pak_filesystem/parameterfile.h
  src/pak_filesystem/generalparameters.h
  src/pak_filesystem/meleeparameters.h
  src/pak_filesystem/pakcontrols.h
  src/ui/neostudio.h
  src/ui/menu/aboutwindow.h
  src/ui/menu/optiondialog.h
  src/ui/paramSections/generalframe.h
  src/ui/paramSections/meleeframe.h
  
  # ::source files::
  src/main.cpp
  src/options.cpp
  src/external/fileparse.cpp
  src/external/debug.cpp
  src/pak_filesystem/generalparameters.cpp
  src/pak_filesystem/meleeparameters.cpp
  src/pak_filesystem/pakcontrols.cpp
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
