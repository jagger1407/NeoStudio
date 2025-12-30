cmake_minimum_required(VERSION 3.5)
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
  src/options.h
  src/bitmanipulation.h
  src/external/fileparse.h
  src/external/cfgparser.h
  src/external/debug.h

  src/pak_filesystem/pakcontrols.h
  src/pak_filesystem/generalparameters.h
  src/pak_filesystem/meleeparameters.h
  src/pak_filesystem/kiparameters.h
  src/pak_filesystem/movementparameters.h

  src/ui/neostudio.h
  src/ui/editors/charparamframe.h
  src/ui/editors/skilllistframe.h
  src/ui/menu/aboutwindow.h
  src/ui/menu/optiondialog.h
  src/ui/menu/datselectiondialog.h
  src/ui/menu/characterselectiondialog.h
  src/ui/menu/sectionselectiondialog.h

  src/ui/paramSections/generalframe.h
  src/ui/paramSections/meleeframe.h
  src/ui/paramSections/kiframe.h
  src/ui/paramSections/movementframe.h

  # ::source files::
  src/main.cpp
  src/options.cpp
  src/external/fileparse.cpp
  src/external/cfgparser.cpp
  src/external/debug.cpp

  src/pak_filesystem/pakcontrols.cpp
  src/pak_filesystem/generalparameters.cpp
  src/pak_filesystem/meleeparameters.cpp
  src/pak_filesystem/kiparameters.cpp
  src/pak_filesystem/movementparameters.cpp

  src/ui/neostudio.cpp
  src/ui/editors/charparamframe.cpp
  src/ui/editors/skilllistframe.cpp
  src/ui/menu/aboutwindow.cpp
  src/ui/menu/optiondialog.cpp
  src/ui/menu/datselectiondialog.cpp
  src/ui/menu/characterselectiondialog.cpp
  src/ui/menu/sectionselectiondialog.cpp

  src/ui/paramSections/generalframe.cpp
  src/ui/paramSections/meleeframe.cpp
  src/ui/paramSections/kiframe.cpp
  src/ui/paramSections/movementframe.cpp

  # ::designer files::
  src/ui/neostudio.ui
  src/ui/editors/charparamframe.ui
  src/ui/editors/skilllistframe.ui
  src/ui/paramSections/generalframe.ui
  src/ui/paramSections/meleeframe.ui
  src/ui/paramSections/kiframe.ui
  src/ui/paramSections/movementframe.ui
  src/ui/menu/aboutwindow.ui
  src/ui/menu/optiondialog.ui
  src/ui/menu/datselectiondialog.ui
  src/ui/menu/characterselectiondialog.ui
  src/ui/menu/sectionselectiondialog.ui
)

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
endif()

# Tell CMake to create the executable
add_executable(neostudio ${neostudio_SRC})

if(WIN32)
set_target_properties(neostudio PROPERTIES
    WIN32_EXECUTABLE TRUE
)
endif()

# Use the Widgets module from Qt 5.
target_link_libraries(neostudio Qt5::Widgets)

# Install the executable
install(TARGETS neostudio DESTINATION bin)

# Copy the assets folder to the build directory
add_custom_command(TARGET neostudio POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:neostudio>/assets/)
