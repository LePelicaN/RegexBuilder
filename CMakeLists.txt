
SET( PROJECT_NAME RegexBuilder )

PROJECT( ${PROJECT_NAME} )

CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

INCLUDE( version.cmake )

MESSAGE( STATUS "**** Configuring ${PROJECT_NAME} version ${REGEXBUILDER_VERSION} ****")

# SET warning level
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated -std=c++11" )
SET( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-unused -Wno-uninitialized" )

SET_PROPERTY( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
              "Debug" "Release" "RelWithDebInfo" "Coverage" )

SET( CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage" )
SET( CMAKE_C_FLAGS_COVERAGE "${CMAKE_C_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage" )
SET( CMAKE_EXE_LINKER_FLAGS_COVERAGE "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage" )

set( CMAKE_AUTOMOC ON )

SET( EXECUTABLE_OUTPUT_PATH ${RegexBuilder_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE} )
SET( LIBRARY_OUTPUT_PATH ${RegexBuilder_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE} )

# Set some Win32 Specific Settings
IF ( CMAKE_BUILD_TYPE MATCHES Release )
   IF( WIN32 )
      SET( GUI_TYPE WIN32 )
   ENDIF( WIN32 )
ENDIF ( CMAKE_BUILD_TYPE MATCHES Release )
# Set some Apple MacOS Specific settings
IF ( APPLE )
   SET( GUI_TYPE MACOSX_BUNDLE )
ENDIF ( APPLE )

LINK_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/lib )

CONFIGURE_FILE( config_version.hpp.cmake ${CMAKE_CURRENT_SOURCE_DIR}/config_version.hpp )

add_library( ${PROJECT_NAME} RegexBuilder.cpp )
