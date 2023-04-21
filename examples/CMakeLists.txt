cmake_minimum_required (VERSION 3.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(AppName JmTestApp)

set(MY_SOURCES 
	src/jmtestapp.ui
	src/jmtestapp.qrc
	src/jmtestapp.cpp
	src/jmtestapp.h
	src/main.cpp
)

#将各种文件归类到指定变量
FILE(GLOB_RECURSE FORMS "*.ui")
FILE(GLOB_RECURSE RESOURCE_FILES "*.qrc")
FILE(GLOB TS_FILES "*.ts")
FILE(GLOB MOC_FILES "mocs_*.cpp")

list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "ui")

#将ui文件编译成ui_*.h文件
IF(FORMS)
	QT5_WRAP_UI(FORMS_UIC ${FORMS})
ENDIF()

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

add_executable(${AppName} WIN32  ${MY_SOURCES})
add_link_options(${AppName} PRIVATE -mwindows)


target_link_libraries (${AppName} PRIVATE JmUiLite)

target_link_libraries(${AppName}
	PRIVATE
		Qt${QT_VERSION_MAJOR}::Core
		Qt${QT_VERSION_MAJOR}::Gui
		Qt${QT_VERSION_MAJOR}::Widgets
		Qt${QT_VERSION_MAJOR}::Xml
)

