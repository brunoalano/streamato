# Streamato Movie Streaming
# Copyright (C) 2015  Bruno Alano Medina
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
cmake_minimum_required( VERSION 2.8 FATAL_ERROR )

# Setup the project
project( streamato C )

# Where are the additional libraries installed? Note: provide includes
# path here, subsequent checks will resolve everything else
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/modules/" )

# Setup the include path of headers
include_directories( ${STREAMATO_SOURCE_DIR}/include )

# Setup versioning
set( STREAMATO_VERSION_PATCH 0 )
set( STREAMATO_VERSION_MINOR 0 )
set( STREAMATO_VERSION_MAJOR 1 )

# GCC Flags (also works for Clang)
if ( "${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" MATCHES "Clang" )
  message( STATUS "Setting the flags for ${CMAKE_C_COMPILER_ID} compiler" )
  add_definitions( -Wall -Wextra --std=c99 -pedantic )
endif()

# Find GNU LibMicroHTTPD
find_package( LibMicroHTTPD REQUIRED )
include_directories( ${MHD_INCLUDE_DIRS} )
add_definitions( ${MHD_DEFINITIONS} )
set( LIBS ${LIBS} ${MHD_LIBRARIES} )

# Setup the list of source files
set( STREAMATO_SOURCES 
  src/streamato.c
)

# Output the sources that we will compile
message( STATUS "Will compile: ${STREAMATO_SOURCES}" )

# Create the executable
add_executable( ${PROJECT_NAME} ${STREAMATO_SOURCES} )

# Link the libraries
target_link_libraries( ${PROJECT_NAME} ${LIBS} )