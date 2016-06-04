
SET ( SRC_FILES 
	  src/GuiClient.cpp
      src/QCanvasWidget.cpp
      src/Logger.cpp
      src/TCPClient.cpp
      src/QRootCanvas.cpp )

SET ( INC_FILES
      include/GuiClient.h
      include/QCanvasWidget.h
      include/Logger.h
      include/TCPClient.h
      include/QRootCanvas.h )

# require proper c++
ADD_DEFINITIONS( "-pedantic -Wunused-value -O2" )
ADD_DEFINITIONS("-Wno-long-long -Wreturn-type -Werror")

IF ( WITH_QT5 )

SET(CMAKE_AUTOMOC OFF)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

INCLUDE_DIRECTORIES( BEFORE include ${Qt5Widgets_INCLUDE_DIRS})
SET(QT_LIBRARIES ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${ROOT_QTROOT_LIBRARY} ${ROOT_GQT_LIBRARY} ${ROOT_GUI_LIBRARY})
  
QT5_WRAP_CPP(MOC_SRC_FILES ${INC_FILES} )

QT5_WRAP_UI(UI_FILES
			../ui/GuiClient.ui)

ADD_LIBRARY( ${PROJECT_NAME} SHARED ${SRC_FILES} ${MOC_SRC_FILES} ${UI_FILES} )
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${QT_LIBRARIES} )

ADD_EXECUTABLE( QtReco_Client main/QtReco_Client.cpp )
TARGET_LINK_LIBRARIES( QtReco_Client ${PROJECT_NAME} ${PROJECT_NAME} )

QT5_USE_MODULES(QtReco_Client Core Gui Widgets)

ELSE( WITH_QT5 )

INCLUDE_DIRECTORIES( BEFORE include ${QT_INCLUDE_DIRS})

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

QT4_WRAP_CPP( MOC_SRC_FILES ${INC_FILES} )
QT4_WRAP_UI( UI_FILES
			../ui/GuiClient.ui)
			
ADD_LIBRARY( ${PROJECT_NAME} SHARED ${SRC_FILES} ${MOC_SRC_FILES} ${UI_FILES} )
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${QT_LIBRARIES} ${ROOT_QTROOT_LIBRARY} ${ROOT_GQT_LIBRARY} ${ROOT_GUI_LIBRARY} )

ADD_EXECUTABLE( QtReco_Client main/QtReco_Client.cpp )
TARGET_LINK_LIBRARIES( QtReco_Client ${PROJECT_NAME} ${PROJECT_NAME} )

ENDIF ( WITH_QT5 )

# ----- Install headers -----
INSTALL_DIRECTORY( include DESTINATION . FILES_MATCHING PATTERN "*.h" )
