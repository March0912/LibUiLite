cmake_minimum_required (VERSION 3.8)

set(JmTestApp_SOURCES 
	src/jmtestapp.ui
	src/jmtestapp.qrc
	src/jmtestapp.cpp
	src/jmtestapp.h
	src/main.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(JmTestApp ${JmTestApp_SOURCES})
target_link_libraries (JmTestApp JmUiLite)

