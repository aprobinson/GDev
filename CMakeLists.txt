# Define the minimum required version of CMake
CMAKE_MINIMUM_REQUIRED(VERSION 3.0.1 FATAL_ERROR)

# Add the custom modules to the module path
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
  "${CMAKE_DIR}/share/cmake-3.0/Modules"
  ${PROJECT_SOURCE_DIR}/cmake)

# Define the project name
INCLUDE(ProjectName)

# Define the project version
INCLUDE(Version)

# Include the macros that have been defined for this project
INCLUDE(Macros)

# Enforce an out-of-source build
ENFORCE_OUT_OF_SOURCE_BUILD()

# Load the patch files
FIND_FILE(SDL_RENDER_SW_C_PATCH
  NAMES "SDL_render_sw.c.patch"
  PATHS ${CMAKE_SOURCE_DIR}/patches/
  CACHE STRING "The SDL software renderer patch file" FORCE)

# Find the patch exec
FIND_PROGRAM(PATCH_EXEC NAMES patch)
IF(${PATCH_EXEC} MATCHES NOTFOUND)
  MESSAGE(FATAL_ERROR "The patch program could not be found!")
ENDIF()

# Enable the make test target
ENABLE_TESTING()

IF(SDL_PREFIX)
  # Find the SDL package
  SET(SDL_INCLUDE_DIRS ${SDL_PREFIX}/include ${SDL_PREFIX}/include/SDL2)
  SET(SDL_LIBRARY_DIRS ${SDL_PREFIX}/lib)

  # Set the include paths for SDL
  INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIRS})

  # Set the link paths for SDL
  LINK_DIRECTORIES(${SDL_LIBRARY_DIRS})
  
  # Find the SDL library
  FIND_LIBRARY(SDL libSDL2.so ${SDL_LIBRARY_DIRS} NO_CMAKE_SYSTEM_PATH NO_DEFAULT_PATH)
  
  IF(${SDL} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The SDL2 library could not be found!")
  ENDIF()

  IF((NOT DEFINED SDL_SW_RENDERER_PATCHED) OR (NOT ${SDL_SW_RENDERER_PATCHED}))
    FIND_FILE(SDL_RENDER_SW_C
      NAMES "SDL_render_sw.c"
      PATHS ${SDL_PREFIX}/src/src/render/software ${SDL_PREFIX}/SDL2-2.0.3/src/render/software)
    IF(SDL_RENDER_SW_C MATCHES NOTFOUND)
      MESSAGE(FATAL_ERROR "The SDL_render_sw.c file could not be found!")
    ENDIF()

    IF(NOT DEFINED SDL_RENDER_SW_C_PATCH)
      MESSAGE(FATAL_ERROR "The SDL_render_sw.c patch file needs to be defined!")
    ENDIF()

    IF(NOT DEFINED PATCH_EXEC)
      MESSAGE(FATAL_ERROR "The patch executable needs to be defined!")
    ENDIF()
    
    EXECUTE_PROCESS(COMMAND ${PATCH_EXEC} -s -N -r ${CMAKE_BINARY_DIR}/SDL_render_sw.c.rej ${SDL_RENDER_SW_C} ${SDL_RENDER_SW_C_PATCH}
      OUTPUT_VARIABLE SDL_RENDER_SW_C_PATCH_OUTPUT
      ERROR_VARIABLE SDL_RENDER_SW_C_PATCH_ERROR
      RESULT_VARIABLE SDL_RENDER_SW_C_PATCH_RESULT)
    
    IF(${SDL_RENDER_SW_C_PATCH_OUTPUT} MATCHES "FAILED")
      MESSAGE(FATAL_ERROR "The SDL_render_sw.c file could not be patched: ${SDL_RENDER_SW_C_PATCH_OUTPUT}")
    ELSEIF(${SDL_RENDER_SW_C_PATCH_OUTPUT} MATCHES "refusing")
      MESSAGE(FATAL_ERROR "The SDL_render_sw.c file could not be patched: ${SDL_RENDER_SW_C_PATCH_OUTPUT}")
    ELSEIF(SDL_RENDER_SW_C_PATCH_RESULT EQUAL "0")
      MESSAGE(FATAL_ERROR "SDL_render_sw.c was successfully patched for the first time. SDL needs to be rebuilt before proceeding.")
    ELSE()
      SET(SDL_SW_RENDERER_PATCHED "ON"
	CACHE BOOL "Flag that indicates if the patch was successful." FORCE)
      MESSAGE("-- SDL_render_sw.c has been patched!")
    ENDIF()
  ENDIF()
  
  # Echo the SDL details if a verbose configure was requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("Found SDL! Here are the details: ")
    MESSAGE(" SDL_PREFIX = ${SDL_PREFIX}")
    MESSAGE(" SDL_INCLUDE_DIRS = ${SDL_INCLUDE_DIRS}")
    MESSAGE(" SDL_LIBRARY_DIRS = ${SDL_LIBRARY_DIRS}")
    MESSAGE(" SDL_LIBRARY = ${SDL}")
    MESSAGE("End of SDL details\n")
  ENDIF()
ELSE()
  MESSAGE(ERROR "The SDL_PREFIX must me set.")
ENDIF()

# Enable SDL_IMG
IF(SDL_IMG_PREFIX)
  # Find the SDL-IMAGE package
  SET(SDL_IMG_INCLUDE_DIRS ${SDL_IMG_PREFIX}/include)
  SET(SDL_IMG_LIBRARY_DIRS ${SDL_IMG_PREFIX}/lib)

  # Set the include paths for SDL_IMG
  INCLUDE_DIRECTORIES(${SDL_IMG_INCLUDE_DIRS})

  # Set the link paths for SDL_IMG
  LINK_DIRECTORIES(${SDL_IMG_LIBRARY_DIRS})
  
  # Find the SDL_IMG library
  FIND_LIBRARY(SDL_IMG libSDL2_image.so ${SDL_IMG_LIBRARY_DIRS} NO_CMAKE_SYSTEM_PATH NO_DEFAULT_PATH)
  
  IF(${SDL_IMG} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The SDL_IMG library could not be found!")
  ENDIF()

  # Echo the SDL details if a verbose configure was requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("Found SDL_IMG! Here are the details: ")
    MESSAGE(" SDL_IMG_PREFIX = ${SDL_IMG_PREFIX}")
    MESSAGE(" SDL_IMG_INCLUDE_DIRS = ${SDL_IMG_INCLUDE_DIRS}")
    MESSAGE(" SDL_IMG_LIBRARY_DIRS = ${SDL_IMG_LIBRARY_DIRS}")
    MESSAGE(" SDL_IMG_LIBRARY = ${SDL_IMG}")
    MESSAGE("End of SDL details\n")
  ENDIF()
ELSE()
  MESSAGE(ERROR "The SDL_IMG_PREFIX must me set.")
ENDIF()

# Enable SDL_FONT
IF(SDL_FONT_PREFIX)
  # Find the SDL-FONT package
  SET(SDL_FONT_INCLUDE_DIRS ${SDL_FONT_PREFIX}/include)
  SET(SDL_FONT_LIBRARY_DIRS ${SDL_FONT_PREFIX}/lib)

  # Set the include paths for SDL_FONT
  INCLUDE_DIRECTORIES(${SDL_FONT_INCLUDE_DIRS})

  # Set the link paths for SDL_FONT
  LINK_DIRECTORIES(${SDL_FONT_LIBRARY_DIRS})
  
  # Find the SDL_FONT library
  FIND_LIBRARY(SDL_FONT libSDL2_ttf.so ${SDL_FONT_LIBRARY_DIRS} NO_CMAKE_SYSTEM_PATH NO_DEFAULT_PATH)
  
  IF(${SDL_FONT} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The SDL_FONT library could not be found!")
  ENDIF()

  # Echo the SDL details if a verbose configure was requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("Found SDL_FONT! Here are the details: ")
    MESSAGE(" SDL_FONT_PREFIX = ${SDL_FONT_PREFIX}")
    MESSAGE(" SDL_FONT_INCLUDE_DIRS = ${SDL_FONT_INCLUDE_DIRS}")
    MESSAGE(" SDL_FONT_LIBRARY_DIRS = ${SDL_FONT_LIBRARY_DIRS}")
    MESSAGE(" SDL_FONT_LIBRARY = ${SDL_FONT}")
    MESSAGE("End of SDL details\n")
  ENDIF()
ELSE()
  MESSAGE(ERROR "The SDL_FONT_PREFIX must me set.")
ENDIF()

# Enable BOOST Support
IF(BOOST_PREFIX)
  ENABLE_BOOST_SUPPORT(program_options serialization thread timer chrono test_exec_monitor)
ELSE()
  MESSAGE(STATUS "The BOOST_PREFIX has not been set. The system default will be used.")
ENDIF()

# Add Design-by-Contract support if requested
IF(${PROJECT_NAME}_ENABLE_DBC)
  IF(${${PROJECT_NAME}_ENABLE_DBC})
    SET(HAVE_${PROJECT_NAME}_DBC "1")
  ELSE()
    SET(HAVE_${PROJECT_NAME}_DBC "0")
  ENDIF()
ELSE()
  SET(HAVE_${PROJECT_NAME}_DBC "0")
ENDIF()

# Parse the DBC configure file so it can be used in source files
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/dbc_config.hpp.in ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_dbc_config.hpp)

# Add the CMAKE_BINARY_DIR to the include path to access config files
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

# Allow CXX11 support
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fext-numeric-literals")

# Set up the project directory hierarchy
ADD_SUBDIRECTORY(src)
INCLUDE_DIRECTORIES(src)

ADD_SUBDIRECTORY(test)

ADD_SUBDIRECTORY(cli)
