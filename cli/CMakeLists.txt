# Create the sdl_test_1 exec
ADD_EXECUTABLE(sdl_test_1 sdl_test_1.cpp)
TARGET_LINK_LIBRARIES(sdl_test_1 ${SDL})

# Add exec to install target
INSTALL(TARGETS sdl_test_1
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)