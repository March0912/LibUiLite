cmake_minimum_required (VERSION 3.1.0)

set(JmTestApp_SOURCES 
	src/jmtestapp.ui
	src/jmtestapp.qrc
	src/jmtestapp.cpp
	src/jmtestapp.h
	src/main.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(JmTestApp ${JmTestApp_SOURCES})

set(CMAKE_AUTOMOC TRUE)

target_link_libraries (JmTestApp PRIVATE JmUiLite)

target_link_libraries(JmTestApp
	PRIVATE
		Qt${QT_VERSION_MAJOR}::Core
		Qt${QT_VERSION_MAJOR}::Gui
		Qt${QT_VERSION_MAJOR}::Widgets
		Qt${QT_VERSION_MAJOR}::Xml
)