
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

INCLUDE_DIRECTORIES( BEFORE include ${QT_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS})

SET(CMAKE_AUTOMOC OFF)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

QT4_WRAP_CPP( MOC_SRC_FILES ${INC_FILES} )
QT4_WRAP_UI( UI_FILES
			../ui/GuiClient.ui)
		
ADD_SHARED_LIBRARY( ${PROJECT_NAME} ${SRC_FILES} ${MOC_SRC_FILES} ${UI_FILES} )
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${QT_LIBRARIES} ${ROOT_QTROOT_LIBRARY} ${ROOT_LIBRARIES} )

INSTALL(
        TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
)

ADD_EXECUTABLE( QtReco_Client_interface main/QtReco_Client.cpp )
TARGET_LINK_LIBRARIES( QtReco_Client_interface ${PROJECT_NAME} ${PROJECT_NAME} )

INSTALL(
    TARGETS QtReco_Client_interface
    RUNTIME DESTINATION bin
)

# ----- Install headers -----
INSTALL_DIRECTORY( include DESTINATION . FILES_MATCHING PATTERN "*.h" )
