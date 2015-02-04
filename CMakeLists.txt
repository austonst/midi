# Copyright (c) 2014 Auston Sterling
# See LICENSE for copying permission.

cmake_minimum_required(VERSION 2.8.8)

project(midi)

# Enable C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#Set files
set(SRCS
  ./note.cpp
  ./varlength.cpp
  ./scales.cpp
  ./chords.cpp
  ./event.cpp
  ./timedivision.cpp
  ./track.cpp
  ./midi.cpp
  )

# Create library and test suite
add_library(midiobj OBJECT ${SRCS})
add_library(midi $<TARGET_OBJECTS:midiobj>)
add_executable(testmidi $<TARGET_OBJECTS:midiobj> ./testmidi.cpp)