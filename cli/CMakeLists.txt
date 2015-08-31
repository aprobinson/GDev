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
