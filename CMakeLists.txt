#cmake version
cmake_minimum_required(VERSION 2.8)
project(MazeSolver)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
		message(STATUS "Setting build type to 'Release as none was specified.")
		set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
		#set possible values of built type for cmake-gui
		set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug"
						"MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(EXECUTABLE_NAME "MazeSovler")
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
configure_file(
				"${PROJECT_SOURCE_DIR}/config.h.in"
				"${PROJECT_BINARY_DIR}/config.h"
				)

set(HEADERS
				src/backend/disjointSets.hpp
				src/backend/mazeGen.hpp
)

set(SOURCES
				src/backend/disjointSets.cpp
				src/backend/mazeGen.cpp
				src/main.cpp
)

set(RUNTIME_DEPENDENCIES
                src/frontend/pySolve.py
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src/backend")
include_directories("${PROJECT_SOURCE_DIR}/src/frontend")

add_executable(${EXECUTABLE_NAME} ${SOURCES} ${HEADERS})

set(Python_ADDITIONAL_VERSIONS 3.4)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(${EXECUTABLE_NAME} ${PYTHON_LIBRARIES})

#copy runtime deps
add_custom_target(copy_runtime_dependencies ALL)
foreach(RUNTIME_DEPENDENCY ${RUNTIME_DEPENDENCIES})
    add_custom_command(TARGET copy_runtime_dependencies POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_SOURCE_DIR}/${RUNTIME_DEPENDENCY}
                       $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/${RUNTIME_DEPENDENCY})
endforeach()
