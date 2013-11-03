cmake_minimum_required(VERSION 2.6)
 
project(arkanoid)

SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -std=c++11")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

if(UNIX)
	if(EXISTS "/usr/local/lib/OGRE/cmake")

	  set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local

	elseif(EXISTS "/usr/lib/OGRE/cmake")

	  set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") # Otherwise, this one

	else ()
	  message(SEND_ERROR "Failed to find module path.")
	endif(EXISTS "/usr/local/lib/OGRE/cmake")
endif(UNIX)
 
if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()
 
set(CMAKE_DEBUG_POSTFIX "_d")
 
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}")
 
find_package(OGRE REQUIRED)
 
find_package(SDL2 REQUIRED)
 
if(NOT SDL2_FOUND)
    message(SEND_ERROR "Failed to find SDL2.")
endif()
 
# Find Boost
if (NOT OGRE_BUILD_PLATFORM_IPHONE)
	if (WIN32 OR APPLE)
		set(Boost_USE_STATIC_LIBS TRUE)
	else ()
		# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
		set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
	endif ()
	if (MINGW)
		# this is probably a bug in CMake: the boost find module tries to look for
		# boost libraries with name libboost_*, but CMake already prefixes library
		# search names with "lib". This is the workaround.
		set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
	endif ()
	set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
	# Components that need linking (NB does not include header-only components like bind)
	set(OGRE_BOOST_COMPONENTS thread date_time)
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	if (NOT Boost_FOUND)
		# Try again with the other type of libs
		set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
		find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	endif()
	find_package(Boost QUIET)
 
	# Set up referencing of Boost
	include_directories(${Boost_INCLUDE_DIR})
	add_definitions(-DBOOST_ALL_NO_LIB)
	set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
endif()

set(BOX2D_VERSION 2.1.0)
add_subdirectory(libs/box2d-2.2.1/Box2D)
 
set(HEADERS
    src/Application.h
    src/BillboardAtlas.h
    src/Game.h
    src/GameObj.h
    src/GameObjBall.h
    src/GameObjBrick.h
    src/GameObjWall.h
    src/NLTmxMap.h
)
 
set(SOURCES
	src/main.cpp
    src/Application.cpp
    src/BillboardAtlas.cpp
    src/Game.cpp
    src/GameObj.cpp
    src/GameObjBall.cpp
    src/GameObjBrick.cpp
    src/GameObjWall.cpp
    src/NLTmxMap.cpp
)
 
include_directories( ${SDL2_INCLUDE_DIR}
	${OGRE_INCLUDE_DIRS}
    ${Box2D_SOURCE_DIR}
)
 
add_executable(arkanoid ${HEADERS} ${SOURCES})
 
set_target_properties(arkanoid PROPERTIES DEBUG_POSTFIX _d)
 
target_link_libraries(arkanoid ${OGRE_LIBRARIES} ${SDL2_LIBRARY} Box2D)
 
if(MINGW OR UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
endif(MINGW OR UNIX)
 
if(UNIX)
 
	install(TARGETS arkanoid
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
endif(UNIX)
