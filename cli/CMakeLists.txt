# Create the sdl_test_1 exec
ADD_EXECUTABLE(sdl_test_1 sdl_test_1.cpp)
TARGET_LINK_LIBRARIES(sdl_test_1 ${SDL})
INSTALL(TARGETS sdl_test_1
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_2 exec
ADD_EXECUTABLE(sdl_test_2 sdl_test_2.cpp)
TARGET_LINK_LIBRARIES(sdl_test_2 ${SDL})
INSTALL(TARGETS sdl_test_2
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
  

##---------------------------------------------------------------------------##
## Sean's tutorial execs
##---------------------------------------------------------------------------##
# Create the sdl_test_6_sean exec
ADD_EXECUTABLE(sdl_test_6_sean sdl_test_6_sean.cpp)
TARGET_LINK_LIBRARIES(sdl_test_6_sean ${SDL_IMG} ${SDL} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_6_sean
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_7_sean exec
ADD_EXECUTABLE(sdl_test_7_sean sdl_test_7_sean.cpp)
TARGET_LINK_LIBRARIES(sdl_test_7_sean ${SDL_IMG} ${SDL} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_7_sean
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_8_sean exec
ADD_EXECUTABLE(sdl_test_8_sean sdl_test_8_sean.cpp)
TARGET_LINK_LIBRARIES(sdl_test_8_sean ${SDL_IMG} ${SDL} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_8_sean
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_9_sean exec
ADD_EXECUTABLE(sdl_test_9_sean sdl_test_9_sean.cpp)
TARGET_LINK_LIBRARIES(sdl_test_9_sean ${SDL_IMG} ${SDL} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_9_sean
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_10_sean exec
ADD_EXECUTABLE(sdl_test_10_sean sdl_test_10_sean.cpp)
TARGET_LINK_LIBRARIES(sdl_test_10_sean ${SDL_IMG} ${SDL} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_10_sean
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_11_sean exec
ADD_EXECUTABLE(sdl_test_11_sean sdl_test_11_sean.cpp)
TARGET_LINK_LIBRARIES(sdl_test_11_sean ${SDL_IMG} ${SDL} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_11_sean
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_12_sean exec
ADD_EXECUTABLE(sdl_test_12_sean sdl_test_12_sean.cpp)
TARGET_LINK_LIBRARIES(sdl_test_12_sean ${SDL_IMG} ${SDL} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_12_sean
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_13_sean exec
ADD_EXECUTABLE(sdl_test_13_sean sdl_test_13_sean.cpp)
TARGET_LINK_LIBRARIES(sdl_test_13_sean ${SDL_IMG} ${SDL} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_13_sean
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_14_sean exec
ADD_EXECUTABLE(sdl_test_14_sean sdl_test_14_sean.cpp)
TARGET_LINK_LIBRARIES(sdl_test_14_sean ${SDL_IMG} ${SDL} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_14_sean
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_15_sean exec
ADD_EXECUTABLE(sdl_test_15_sean sdl_test_15_sean.cpp)
TARGET_LINK_LIBRARIES(sdl_test_15_sean ${SDL_IMG} ${SDL} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_15_sean
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)


  
##---------------------------------------------------------------------------##
## Alex's tutorial execs
##---------------------------------------------------------------------------##
# Create the sdl_test_4_alex exec
ADD_EXECUTABLE(sdl_test_3_alex sdl_test_3_alex.cpp)
TARGET_LINK_LIBRARIES(sdl_test_3_alex ${SDL})
INSTALL(TARGETS sdl_test_3_alex
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_4_alex exec
ADD_EXECUTABLE(sdl_test_4_alex sdl_test_4_alex.cpp)
TARGET_LINK_LIBRARIES(sdl_test_4_alex ${SDL} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_4_alex
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_5_alex exec
ADD_EXECUTABLE(sdl_test_5_alex sdl_test_5_alex.cpp)
TARGET_LINK_LIBRARIES(sdl_test_5_alex ${SDL} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_5_alex
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_7_alex exec
ADD_EXECUTABLE(sdl_test_7_alex sdl_test_7_alex.cpp)
TARGET_LINK_LIBRARIES(sdl_test_7_alex ${SDL} ${SDL_IMG} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_7_alex
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_8_alex exec
ADD_EXECUTABLE(sdl_test_8_alex sdl_test_8_alex.cpp)
TARGET_LINK_LIBRARIES(sdl_test_8_alex ${SDL} ${SDL_IMG} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_8_alex
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_9_alex exec
ADD_EXECUTABLE(sdl_test_9_alex sdl_test_9_alex.cpp)
TARGET_LINK_LIBRARIES(sdl_test_9_alex ${SDL} ${SDL_IMG} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_9_alex
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_10_alex exec
ADD_EXECUTABLE(sdl_test_10_alex sdl_test_10_alex.cpp)
TARGET_LINK_LIBRARIES(sdl_test_10_alex ${SDL} ${SDL_IMG} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_10_alex
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_11_alex exec 
ADD_EXECUTABLE(sdl_test_11_alex sdl_test_11_alex.cpp)
TARGET_LINK_LIBRARIES(sdl_test_11_alex ${SDL} ${SDL_IMG} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_11_alex
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_12_alex exec 
ADD_EXECUTABLE(sdl_test_12_alex sdl_test_12_alex.cpp)
TARGET_LINK_LIBRARIES(sdl_test_12_alex ${SDL} ${SDL_IMG} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_12_alex
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_13_alex exec 
ADD_EXECUTABLE(sdl_test_13_alex sdl_test_13_alex.cpp)
TARGET_LINK_LIBRARIES(sdl_test_13_alex ${SDL} ${SDL_IMG} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_13_alex
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_14_alex exec 
ADD_EXECUTABLE(sdl_test_14_alex sdl_test_14_alex.cpp)
TARGET_LINK_LIBRARIES(sdl_test_14_alex ${SDL} ${SDL_IMG} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_14_alex
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_15_alex exec 
ADD_EXECUTABLE(sdl_test_15_alex sdl_test_15_alex.cpp)
TARGET_LINK_LIBRARIES(sdl_test_15_alex ${SDL} ${SDL_IMG} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_15_alex
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_16_alex exec 
ADD_EXECUTABLE(sdl_test_16_alex sdl_test_16_alex.cpp)
TARGET_LINK_LIBRARIES(sdl_test_16_alex ${SDL} ${SDL_IMG} ${SDL_FONT} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_16_alex
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Create the sdl_test_17_alex exec 
ADD_EXECUTABLE(sdl_test_17_alex sdl_test_17_alex.cpp)
TARGET_LINK_LIBRARIES(sdl_test_17_alex ${SDL} ${SDL_IMG} ${SDL_FONT} ${Boost_PROGRAM_OPTIONS_LIBRARY})
INSTALL(TARGETS sdl_test_17_alex
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
