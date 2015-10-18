ADD_EXECUTABLE(tstRectangle tstRectangle.cpp)
TARGET_LINK_LIBRARIES(tstRectangle gdev ${Boost_TEST_EXEC_MONITOR_LIBRARY})
ADD_TEST(Rectangle_test tstRectangle)

ADD_EXECUTABLE(tstEllipse tstEllipse.cpp)
TARGET_LINK_LIBRARIES(tstEllipse gdev ${Boost_TEST_EXEC_MONITOR_LIBRARY})
ADD_TEST(Ellipse_test tstEllipse)

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

ADD_EXECUTABLE(tstWindowRenderer tstWindowRenderer.cpp)
TARGET_LINK_LIBRARIES(tstWindowRenderer gdev ${Boost_TEST_EXEC_MONITOR_LIBRARY})
ADD_TEST(WindowRenderer_test tstWindowRenderer)

ADD_EXECUTABLE(tstStaticTexture tstStaticTexture.cpp)
TARGET_LINK_LIBRARIES(tstStaticTexture gdev ${Boost_TEST_EXEC_MONITOR_LIBRARY})
ADD_TEST(StaticTexture_test tstStaticTexture ${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_image.png ${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_font.ttf)

ADD_EXECUTABLE(tstTargetTexture tstTargetTexture.cpp)
TARGET_LINK_LIBRARIES(tstTargetTexture gdev ${Boost_TEST_EXEC_MONITOR_LIBRARY})
ADD_TEST(TargetTexture_test tstTargetTexture)

ADD_EXECUTABLE(tstStreamingTexture tstStreamingTexture.cpp)
TARGET_LINK_LIBRARIES(tstStreamingTexture gdev ${Boost_TEST_EXEC_MONITOR_LIBRARY})
ADD_TEST(StreamingTexture_test tstStreamingTexture ${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_image.png ${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_font.ttf)

ADD_EXECUTABLE(tstGeneralButton tstGeneralButton.cpp)
TARGET_LINK_LIBRARIES(tstGeneralButton gdev ${Boost_TEST_EXEC_MONITOR_LIBRARY})
ADD_TEST(GeneralButton_test tstGeneralButton ${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_font.ttf)