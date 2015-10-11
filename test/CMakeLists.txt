ADD_EXECUTABLE(tstGlobalSDLSession tstGlobalSDLSession.cpp)
TARGET_LINK_LIBRARIES(tstGlobalSDLSession gdev ${Boost_TEST_EXEC_MONITOR_LIBRARY})
ADD_TEST(GlobalSDLSession_test tstGlobalSDLSession)

ADD_EXECUTABLE(tstFont tstFont.cpp)
TARGET_LINK_LIBRARIES(tstFont gdev ${Boost_TEST_EXEC_MONITOR_LIBRARY})
ADD_TEST(Font_test tstFont ${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_font.ttf)

ADD_EXECUTABLE(tstSurface tstSurface.cpp)
TARGET_LINK_LIBRARIES(tstSurface gdev ${Boost_TEST_EXEC_MONITOR_LIBRARY})
ADD_TEST(Surface_test tstSurface ${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_image.png ${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_font.ttf)

ADD_EXECUTABLE(tstWindow tstWindow.cpp)
TARGET_LINK_LIBRARIES(tstWindow gdev ${Boost_TEST_EXEC_MONITOR_LIBRARY})
ADD_TEST(Window_test tstWindow) 

ADD_EXECUTABLE(tstSurfaceRenderer tstSurfaceRenderer.cpp)
TARGET_LINK_LIBRARIES(tstSurfaceRenderer gdev ${Boost_TEST_EXEC_MONITOR_LIBRARY})
ADD_TEST(SurfaceRenderer_test tstSurfaceRenderer)

ADD_EXECUTABLE(tstStaticTexture tstStaticTexture.cpp)
TARGET_LINK_LIBRARIES(tstStaticTexture gdev ${Boost_TEST_EXEC_MONITOR_LIBRARY})
ADD_TEST(StaticTexture_test tstStaticTexture ${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_image.png ${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_font.ttf)

