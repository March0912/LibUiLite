cmake_minimum_required (VERSION 3.1.0)
project(JmUiLite VERSION 1.0.0)

set(JmUiLite_STANDALONE_BUILD OFF)
if(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(JmUiLite_STANDALONE_BUILD ON)
endif()

# option(JmUiLite_ENABLE_TESTS "${PROJECT_NAME}: Enable tests" ${JmUiLite_STANDALONE_BUILD})
option(JmUiLite_ENABLE_EXAMPLES "${PROJECT_NAME}: Enable examples" ${JmUiLite_STANDALONE_BUILD})

option(BUILD_SHARED_LIBS "Build a dynamic JmUiLite library (default: on)" ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
set(JmUilite_BUILD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SRC)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(CMAKE_AUTOMOC TRUE)
if(Not(Qt5_FOUND))
	find_package(QT NAMES Qt5 COMPONENTS  core gui widgets xml REQUIRED)
	find_package(Qt${QT_VERSION_MAJOR} COMPONENTS core gui widgets xml REQUIRED)
	if(Qt5_FOUND)
		message("Qt5 found.")
		message(STATUS "Qt version is ${Qt5Core_VERSION}")
		set(QT_MIN_VEERSION 5.15.2)
	else()
		message(FATAL_ERROR "Not found Qt5!")
	endif()
endif()

if(Qt${QT_VERSION_MAJOR}Core_VERSION VERSION_LESS ${QT_MIN_VERSION})
	message(FATAL_ERROR "Minimum support Qt Version is ${QT_MIN_VEERSION}")
endif()

set(CPACK_PACKAGE_NAME ${PROJECT_NAME} )
set(CMAKE_CXX_STANDARD 14)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8.0)
    message(FATAL_ERROR "gcc 4.8 or higher required!")
  endif()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9.99)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override")
  endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.3.0)
    message(FATAL_ERROR "llvm/clang 3.3 or higher required!")
  endif()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  if(MSVC_VERSION LESS 1920)
    message(FATAL_ERROR "msvc 2019 or higher required!")
  endif()
  # disable common warnings in Qt/stdlib
  # disable 4127: conditional expression is constant
  #         4512: assignment operator could not be generated
  #         4267: conversion from 'size_t' to 'type', possible loss of data
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4127 -wd4512 -wd4267 -wd4913 -we4265")

  string(REGEX REPLACE "/W[0-3]" "/W4" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

  add_definitions(-DUNICODE -DNOMINMAX)

  set(CMAKE_DEBUG_POSTFIX _d)
endif()

add_subdirectory(include)
add_subdirectory(src)

if (JmUiLite_ENABLE_EXAMPLES)
	add_subdirectory(examples)
endif()

ADD_LIBRARY(SHARED)

set(UILite_SOURCES
    JmUiLite/jmdrawhelper.cpp
	JmUiLite/jmdrawhelper.h
	JmUiLite/jmmovewidget.cpp
	JmUiLite/jmmovewidget.h
	JmUiLite/jmshadowframebase.cpp
	JmUiLite/jmshadowframebase.h
	JmUiLite/jmskinloader.cpp
	JmUiLite/jmskinloader.h
	JmUiLite/jmuilite.cpp
	JmUiLite/jmuilite.h
	JmUiLite/jmuilite_global.h
	JmUiLite/jmwidgetbase.cpp
	JmUiLite/jmwidgetbase.h
)
