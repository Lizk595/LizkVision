cmake_minimum_required(VERSION 3.5)

project(LizkVision VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

)

# 构建
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LizkVision
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        imagemanager.h imagemanager.cpp
        operatorwidget.h operatorwidget.cpp operatorwidget.ui
        m_diagram.h m_diagram.cpp
        arrow.cpp arrow.h
        diagramitem.cpp diagramitem.h
        diagramscene.cpp diagramscene.h
        images.qrc
        m_itemmanager.h m_itemmanager.cpp
        m_process.h m_process.cpp
        m_algroithmfun.h m_algroithmfun.cpp
        m_graphicsview.cpp m_graphicsview.h













    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET LizkVision APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(LizkVision SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(LizkVision
            ${PROJECT_SOURCES}
        )
    endif()
endif()

##############################################################################################################################
# 链接第三方库
set(3RDPARTY_DIR ${CMAKE_SOURCE_DIR}/3rdparty)
# 链接第三方库        --opencv4.6
include_directories(${3RDPARTY_DIR}/opencv4.6/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${3RDPARTY_DIR}/opencv4.6/lib/v15/opencv_world460d.lib)
##############################################################################################################################




# 链接QT库
target_link_libraries(LizkVision PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.LizkVision)
endif()


# 配置构建属性
set_target_properties(LizkVision PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)




include(GNUInstallDirs)
install(TARGETS LizkVision
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(LizkVision)
endif()
