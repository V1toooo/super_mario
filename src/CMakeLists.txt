cmake_minimum_required(VERSION 3.2...3.27.5)

project(super_mario)

SET(CMAKE_CXX_FLAGS "-finput-charset=utf-8 -fexec-charset=utf-8")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(os_controls)
add_subdirectory(controller)
add_subdirectory(levels)
add_subdirectory(model)
add_subdirectory(objects)
add_subdirectory(ui)
add_subdirectory(util)

if(GAME_TYPE STREQUAL "WindowsConsole")
	target_compile_definitions(${PROJECT_NAME} PRIVATE WINDOWS_CONSOLE)
elseif(GAME_TYPE STREQUAL "LinuxConsole")
	target_link_libraries(${PROJECT_NAME} ncurses pthread)
	target_compile_definitions(${PROJECT_NAME} PRIVATE LINUX_CONSOLE)
elseif(GAME_TYPE STREQUAL "Qt")
	find_package(Qt6 REQUIRED COMPONENTS Widgets)
	target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
	target_compile_definitions(${PROJECT_NAME} PRIVATE QT_GAME)
endif()
