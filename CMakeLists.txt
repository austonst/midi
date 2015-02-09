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
  ./midi.cpp)

set(HDRS
  ./note.hpp
  ./varlength.hpp
  ./scales.hpp
  ./chords.hpp
  ./event.hpp
  ./timedivision.hpp
  ./track.hpp
  ./midi.hpp
  ./instruments.hpp)

# Create library
add_library(midi SHARED ${SRCS})

# Create test suite
add_executable(testmidi ./testmidi.cpp)
target_link_libraries(testmidi midi)

# Install the library to the appropriate places
install(TARGETS midi
  DESTINATION lib)
install(FILES ${HDRS}
  DESTINATION include/midi/)