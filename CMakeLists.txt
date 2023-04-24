cmake_minimum_required (VERSION 3.1.0)
project(JmUiLite VERSION 1.0.0)

set(JmUiLite_STANDALONE_BUILD OFF)
if(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(JmUiLite_STANDALONE_BUILD ON)
endif()

# option(JmUiLite_ENABLE_TESTS "${PROJECT_NAME}: Enable tests" ${JmUiLite_STANDALONE_BUILD})
option(JmUiLite_ENABLE_EXAMPLES "${PROJECT_NAME}: Enable examples" ${JmUiLite_STANDALONE_BUILD})

set(OPENCV_ENABLE OFF)

option(BUILD_SHARED_LIBS "Build a dynamic JmUiLite library (default: on)" ON)


set(CMAKE_INCLUDE_CURRENT_DIR OFF)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT5_DIR D:/Qt/Qt5.15/5.15.2/msvc2019_64/lib/cmake/Qt5)
message(STATUS "qt cmake path: " ${QT5_DIR})

if(NOT "Qt5_FOUND")
	find_package(QT NAMES Qt5 COMPONENTS core gui widgets xml REQUIRED)
	find_package(Qt${QT_VERSION_MAJOR} COMPONENTS core gui widgets xml REQUIRED)
	if(Qt5_FOUND)
		message("Qt5 found.")
		message(STATUS "Qt version is ${Qt5Core_VERSION}")
		set(QT_MIN_VEERSION 5.15.2)
	else()
		message(FATAL_ERROR "Not found Qt5!")
	endif()
endif()

#if(${Qt5_VERSION} VERSION_LESS ${QT_MIN_VERSION})
#	message(FATAL_ERROR "Minimum support Qt Version is ${QT_MIN_VEERSION}")
#endif()

set(CPACK_PACKAGE_NAME ${PROJECT_NAME} )
set(CMAKE_CXX_STANDARD 17)

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

#设置头文件
set(MY_HEADERS
	include/jmdrawhelper.h
	include/jmmovewidget.h
	include/jmshadowframebase.h
	include/jmskinloader.h
	include/jmuilite.h
	include/jmuilite_global.h
	include/jmwidgetbase.h
)

#设置源文件
set(MY_SOURCES
	src/jmdrawhelper.cpp
	src/jmmovewidget.cpp
	src/jmshadowframebase.cpp
	src/jmskinloader.cpp
	src/jmuilite.cpp
	src/jmwidgetbase.cpp
)

FILE(GLOB_RECURSE RESOURCE_FILES "*.qrc")
FILE(GLOB MOC_FILES "mocs_*.cpp")

list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "ui")
FILE(GLOB_RECURSE FORMS "*.ui")
QT5_WRAP_UI(FORMS_UIC ${FORMS})

#将包含Q_OBJECT的头文件编译成moc_*.cpp文件
QT5_WRAP_CPP(MOC_FILES ${MOC_FILES})
 
#启用qrc资源文件
QT5_ADD_RESOURCES(RES_FILES resourse.qrc)

#将ui文件和生成文件整理在一个文件夹中
SOURCE_GROUP("Form Files" FILES ${FORMS})
#将qrc资源文件整理在一个文件夹中
SOURCE_GROUP("Resource Files" FILES ${RESOURCE_FILES})
#翻译文件
SOURCE_GROUP("Translation Files" FILES ${TS_FILES})

#将MOC,UI,QRC的中间生成文件编译进EXE中
SOURCE_GROUP("Generated Files" FILES ${MOC_FILES} ${FORMS_UIC} ${RES_FILES} ${TS_FILES})	

if (JmUiLite_ENABLE_EXAMPLES)
	add_subdirectory(examples)
endif()

#设置输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT BUILD_SHARED_LIBS)
	add_library(${PROJECT_NAME} STATIC ${MY_HEADERS} ${MY_SOURCES})
else()
	add_library(${PROJECT_NAME} SHARED ${MY_HEADERS} ${MY_SOURCES})
endif()

#设置预处理器
target_compile_definitions(${PROJECT_NAME} PRIVATE -DJMUILITE_LIB)

#引入库目录路径
set(THIRD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty")
#link_directories(${THIRD_PATH}/lib ${THIRD_PATH}/opencv/lib)
message(STATUS "set thirdparty path: " ${THIRD_PATH})

if(OPENCV_ENABLE)
	set(OpenCV_Dir ${THIRD_PATH}/opencv)

	#引入库目录头文件
	include_directories(
			 ${OpenCV_Dir}/include/opencv
			 ${OpenCV_Dir}/include/opencv2
	 )

	#链接opencv开发库
	target_link_libraries(${PROJECT_NAME}
		PRIVATE
			debug ${OpenCV_Dir}/lib/Debug/opencv_core2413d.lib			optimized ${OpenCV_Dir}/lib/Release/opencv_core2413.lib
			debug ${OpenCV_Dir}/lib/Debug/opencv_imgproc2413d.lib		optimized ${OpenCV_Dir}/lib/Release/opencv_imgproc2413.lib					
			debug ${OpenCV_Dir}/lib/Debug/opencv_highgui2413d.lib		optimized ${OpenCV_Dir}/lib/Release/opencv_highgui2413.lib
			debug ${OpenCV_Dir}/lib/Debug/opencv_calib3d2413d.lib		optimized ${OpenCV_Dir}/lib/Release/opencv_calib3d2413.lib
	)

endif()


#设置Qt的链接库
target_link_libraries(${PROJECT_NAME}
	PRIVATE
		Qt${QT_VERSION_MAJOR}::Core
		Qt${QT_VERSION_MAJOR}::Gui
		Qt${QT_VERSION_MAJOR}::Widgets
		Qt${QT_VERSION_MAJOR}::Xml
)