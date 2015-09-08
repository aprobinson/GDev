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

# Enable BOOST Support
IF(BOOST_PREFIX)
  ENABLE_BOOST_SUPPORT(program_options serialization thread timer chrono)
ELSE()
  MESSAGE(STATUS "The BOOST_PREFIX has not been set. The system default will be used.")
ENDIF()

# Set up the project directory hierarchy
ADD_SUBDIRECTORY(src)

ADD_SUBDIRECTORY(test)

ADD_SUBDIRECTORY(cli)
