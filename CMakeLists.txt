cmake_minimum_required(VERSION 3.5)

project(OSGQT LANGUAGES CXX)

find_package( OpenThreads REQUIRED)
find_package( osg REQUIRED)
find_package( osgDB REQUIRED)
find_package( osgUtil REQUIRED)
find_package( osgViewer REQUIRED)
#set (OpenGL_GL_PREFERENCE LEGACY)
set (OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)



macro( config_project PROJNAME LIBNAME )
    include_directories( ${${LIBNAME}_INCLUDE_DIR} )
    target_link_libraries( ${PROJNAME} PRIVATE ${${LIBNAME}_LIBRARY} )
endmacro()

#message(" here - ${OSGVIEWER_INCLUDE_DIR}")
#message("target link lybraries - ${OSGVIEWER_LIBRARY}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES OSGQT_en_VG.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        sources/osgqthread.cpp
        sources/osgqthread.h
        sources/mygeometryobject.cpp
        sources/mygeometryobject.h
        sources/pointscreator.cpp
        sources/pointscreator.h
        sources/mypointscreator.h
        sources/mypointscreator.cpp
        mainwindow.ui
        ${TS_FILES}
)



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(OSGQT
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(OSGQT SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(OSGQT
            ${PROJECT_SOURCES}
        )
        config_project( OSGQT OPENTHREADS )

        config_project( OSGQT OSG )

        config_project( OSGQT OSGDB )

        config_project( OSGQT OSGUTIL )

        config_project( OSGQT OSGVIEWER )

        #include_directories("${HOME}/OpenSceneGraph/osg/include")
        #target_link_libraries(OSGQT PUBLIC "${HOME}/OpenSceneGraph/osg/build/lib")

        config_project( OSGQT OSGGLUT )
        include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

        target_link_libraries(OSGQT  PUBLIC ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

endif()




target_link_libraries(OSGQT  PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


