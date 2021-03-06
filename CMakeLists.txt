################################################################################
## -------------------------------------------------------------------------- ##
##                                                                            ##
##                       (C) 2010-2016 Robot Developers                       ##
##                       See LICENSE for licensing info                       ##
##                                                                            ##
## -------------------------------------------------------------------------- ##
################################################################################

################################################################################
# Project Setup

cmake_minimum_required(VERSION 3.2)
project(Robot)

################################################################################
# Tools

# A tool for troubleshooting, to make sure we got all the files
# can be removed without affecting built binaries
function(DisplayList Header ListToShow)
    message(STATUS "\t${Header}")
    foreach(ListItem ${ListToShow})
        message(STATUS "\t\t${ListItem}")
    endforeach(ListItem ${ListToShow})
endfunction(DisplayList)

# Variables to allow us to change these things in the future
set(ProjectRootDir ${${PROJECT_NAME}_SOURCE_DIR}/)
set(ProjectBinaryDir ${${PROJECT_NAME}_BINARY_DIR}/)

set(SourceDir "${ProjectRootDir}Source/")
set(HeaderDir "${ProjectRootDir}Source/")
set(TestSourceDir "${ProjectRootDir}Test/")
set(TestHeaderDir "${ProjectRootDir}Test/")

################################################################################
# Define Source Files

# We could use a globbing expression, but is generally poor form, because
# eventually someone accidentally adds an incorrect file to their build and
# something hard to fix breaks. When there is only one place to update file list
# it is not that painful.
#
# Here are four globbing expressions that appear to work.

#file(GLOB SourceFileList ${SourceDir}*.cc)
#DisplayList("Source Files" "${SourceFileList}")

#file(GLOB HeaderFileList ${HeaderDir}*.h)
#DisplayList("Header Files" "${HeaderFileList}")

#file(GLOB TestSourceFileList ${TestSourceDir}*.cc)
#DisplayList("Test Source Files" "${TestSourceFileList}")

#file(GLOB TestHeaderFileList ${TestHeaderDir}*.h)
#DisplayList("Test Header Files" "${TestHeaderFileList}")

set(SourceFileList
	"${SourceDir}Bounds.cc"
	"${SourceDir}Clipboard.cc"
	"${SourceDir}Color.cc"
	"${SourceDir}Hash.cc"
	"${SourceDir}Image.cc"
	"${SourceDir}Keyboard.cc"
	"${SourceDir}Memory.cc"
	"${SourceDir}Module.cc"
	"${SourceDir}Mouse.cc"
	"${SourceDir}Point.cc"
	"${SourceDir}Process.cc"
	"${SourceDir}Range.cc"
	"${SourceDir}Screen.cc"
	"${SourceDir}Size.cc"
	"${SourceDir}Timer.cc"
	"${SourceDir}Window.cc"
)
DisplayList("Source Files" "${SourceFileList}")

set(HeaderFileList
	"${HeaderDir}Bounds.h"
	"${HeaderDir}Bounds.h"
	"${HeaderDir}Clipboard.h"
	"${HeaderDir}Color.h"
	"${HeaderDir}Enum.h"
	"${HeaderDir}Global.h"
	"${HeaderDir}Hash.h"
	"${HeaderDir}Image.h"
	"${HeaderDir}Keyboard.h"
	"${HeaderDir}Memory.h"
	"${HeaderDir}Module.h"
	"${HeaderDir}Mouse.h"
	"${HeaderDir}Point.h"
	"${HeaderDir}Process.h"
	"${HeaderDir}Range.h"
	"${HeaderDir}Robot.h"
	"${HeaderDir}Screen.h"
	"${HeaderDir}Size.h"
	"${HeaderDir}Timer.h"
	"${HeaderDir}Types.h"
	"${HeaderDir}Window.h"

)
DisplayList("Header Files" "${HeaderFileList}")

set(TestSourceFileList
	"${TestSourceDir}Clipboard.cc"
	"${TestSourceDir}Keyboard.cc"
	"${TestSourceDir}Main.cc"
	"${TestSourceDir}Memory.cc"
	"${TestSourceDir}Mouse.cc"
	"${TestSourceDir}Process.cc"
	"${TestSourceDir}Screen.cc"
	"${TestSourceDir}Targa.cc"
	"${TestSourceDir}Timer.cc"
	"${TestSourceDir}Types.cc"
	"${TestSourceDir}Window.cc"
)
DisplayList("Test Source Files" "${TestSourceFileList}")

set(TestHeaderFileList
	"${TestHeaderDir}Targa.h"
	"${TestHeaderDir}Test.h"
)
DisplayList("Test Header Files" "${TestHeaderFileList}")

#set(PeonSourceFileList
#	"${TestSourceDir}Peon.cc"
#)
#DisplayList("Peon Source Files" "${PeonSourceFileList}")

################################################################################
# Detect Platform

set(SystemIsLinux OFF)
set(SystemIsWindows OFF)
set(SystemIsMacOSX OFF)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    message(STATUS "\tDetected OS as 'Linux'.")
    set(SystemIsLinux ON)
endif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    message(STATUS "\tDetected OS as 'Windows'.")
    set(SystemIsWindows ON)
endif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    message(STATUS "\tDetected OS as 'Mac OS X'.")
    set(SystemIsMacOSX ON)
endif("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")

################################################################################
# Detect Compiler

set(CompilerIsGCC OFF)
set(CompilerIsClang OFF)
set(CompilerIsIntel OFF)
set(CompilerIsMsvc OFF)

set(CompilerDesignNix OFF)
set(CompilerDesignMS OFF)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message(STATUS "\tDetected compiler as 'GCC'.")
    set(CompilerIsGCC ON)
    set(CompilerDesignNix ON)
endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message(STATUS "\tDetected compiler as 'Clang'.")
    set(CompilerIsClang ON)
    set(CompilerDesignNix ON)
endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    message(STATUS "\tDetected compiler as 'Intel'.")
    set(CompilerIsIntel ON)
    set(CompilerDesignNix ON)
endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message(STATUS "\tDetected compiler as 'MSVC'.")
    set(CompilerIsMsvc ON)
    set(CompilerDesignMS ON)
endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

################################################################################
# Set up build 

# When using the CMake-gui this creates a checkbox
option(BuildStatic "Set for Static library, unset for Dynamic library." ON)
if(BuildStatic)
    set(BuildType "STATIC")
else(BuildStatic)
    set(BuildType "SHARED")
endif(BuildStatic)
message(STATUS "\tLibrary Build type '${BuildType}'.")

if(CompilerIsGCC)
    add_definitions("-iquote${HeaderDir}" "-iquote${TestHeaderDir}")
else(CompilerIsGCC)
    include_directories("${HeaderDir}" "${TestHeaderDir}")
endif(CompilerIsGCC)

################################################################################
# System Specific Settings

if(CompilerDesignNix)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
        
    # Extra flags for warnings.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -pedantic -Wall -Wextra -Wcast-align -Wcast-qual\ -Wctor-dtor-privacy\
        -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op\
        -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept\
        -Wold-style-cast -Wredundant-decls -Wshadow -Wsign-conversion\
        -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wundef\
        -Wno-unused -Wparentheses")
endif(CompilerDesignNix)

if(CompilerIsMsvc)
    # Put msvc compiler flags here.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3") 
endif(CompilerIsMsvc)

################################################################################
# Make build targets

# For those unfamiliar with CMake. When it spits out build files, like make
# files, ninja scripts or vs solutions, these are the top level objects 
# presented to the developer.
#
# So a dev can type "make Robot" to build the library or can type "ninja Test"
# to build Test and everything it requires.
#
# If used to create files for IDEs like Code::Blocks, visual studio, or
# QtCreator these will show up appropriately as different projects or build
# targets.

add_library(Robot "${BuildType}" "${HeaderFileList}" "${SourceFileList}")
add_executable(TestRobot "${TestHeaderFileList}" "${TestSourceFileList}")
    set_target_properties(TestRobot PROPERTIES SUFFIX ".BIN")
    set_target_properties(TestRobot PROPERTIES OUTPUT_NAME "Test")
#add_executable(TestPeon "${PeonSourceFileList}")
#    set_target_properties(TestPeon PROPERTIES SUFFIX ".BIN")
#    set_target_properties(TestPeon PROPERTIES OUTPUT_NAME "Peon")

################################################################################
# Link Build Targets

set(LinkLibraries "")

if(SystemIsLinux)
    # rt & X11 - Seem unneeded build succeeded without it
    # These lines search the path and common include directories for the
    # platform this allows for more platforms to be supported as long as they
    # expose some way that the cmake knows how to look for them
    find_library(Xtst_lib Xtst)
    find_library(Xinerama_lib Xinerama)
    find_package ( X11 REQUIRED )
    if(X11_FOUND)
          include_directories(${X11_INCLUDE_DIR})
          link_libraries(${X11_LIBRARIES})
          #message(STATUS " X11_INCLUDE_DIR: ${X11_INCLUDE_DIR}")
          #message(STATUS " X11_LIBRARIES: ${X11_LIBRARIES}")
    endif(X11_FOUND)

    set(LinkLibraries ${LinkLibraries} ${Xtst_lib} ${Xinerama_lib} ${X11_LIBRARIES})
endif(SystemIsLinux)

if(SystemIsWindows AND CompilerIsGCC)
    set(LinkLibraries ${LinkLibraries} Shlwapi psapi)
endif(SystemIsWindows AND CompilerIsGCC)

target_link_libraries(Robot "${LinkLibraries}")
target_link_libraries(TestRobot Robot)
#target_link_libraries(TestPeon Robot)

if(NOT BuildStatic)
    # Adds the definition when building robot
    target_compile_definitions(Robot PRIVATE -DBUILDING_ROBOT_SHARED)
    # Adds the definition when something else links against Robot
    target_compile_definitions(Robot INTERFACE -DUSING_ROBOT_SHARED)
endif(NOT BuildStatic)

# TODO
# install process
# d in debug build
# objective C++ and other mac stuff
# Peon Offset details
# Figure out any special VS specific logic. I don't think is any beyound /W3


