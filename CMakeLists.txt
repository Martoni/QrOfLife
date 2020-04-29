
cmake_minimum_required(VERSION 3.0)

# set the project name
project(QrOfLife VERSION 0.1 LANGUAGES CXX)

option(BUILD_STATIC "Whether or not to build with static libraries" OFF)

## specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

if (BUILD_STATIC)
	 set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static")
	 set(BUILD_SHARED_LIBS OFF)
endif()

include(GNUInstallDirs)
# By default: DATA_DIR="/usr/local/share"
add_definitions(-DDATA_DIR=\"${CMAKE_INSTALL_FULL_DATAROOTDIR}\")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(
    ${GTKMM_LIBRARY_DIRS}  )

include_directories(
    ${GTKMM_INCLUDE_DIRS}  )

set(QROFLIFE_SOURCE
  src/QrOfLife.cpp
  src/QrCode.cpp
  src/MyDrawing.cpp
  src/GameOfLife.cpp
  src/QOLWindow.cpp
)

set(QROFLIFE_HEADERS
  src/QrOfLife.hpp
  src/QrCode.hpp
  src/MyDrawing.hpp
  src/QOLWindow.hpp
  src/GameOfLife.hpp
)

add_executable(QrOfLife
	${QROFLIFE_SOURCE}
	${QROFLIFE_HEADERS}
)

if (BUILD_STATIC)
	set_target_properties(QrOfLife PROPERTIES LINK_SEARCH_END_STATIC 1)
endif()

target_link_libraries(QrOfLife
    ${GTKMM_LIBRARIES}  )

install(TARGETS QrOfLife DESTINATION bin)
