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

# Enable the make test target
ENABLE_TESTING()

# Find the SDL package
SET(SDL_INCLUDE_DIRS ${SDL_PREFIX}/include)
SET(SDL_LIBRARY_DIRS ${SDL_PREFIX}/lib)

# Set the include paths for SDL
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIRS})

# Set the link paths for SDL
LINK_DIRECTORIES(${SDL_LIBRARY_DIRS})

# Find the SDL library
FIND_LIBRARY(SDL libSDL2.so ${SDL_LIBRARY_DIRS} NO_CMAKE_SYSTEM_PATH)

IF(${SDL} MATCHES NOTFOUND)
  MESSAGE(FATAL_ERROR "The SDL2 library could not be found!")
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

# Set up the project directory hierarchy
ADD_SUBDIRECTORY(src)

ADD_SUBDIRECTORY(test)

ADD_SUBDIRECTORY(cli)