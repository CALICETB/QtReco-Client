###############################################################################
# cmake module for finding ROOT
#
# requires:
#   MacroCheckPackageLibs.cmake for checking package libraries
#
# Following cmake variables are returned by this module:
#
#   ROOT_FOUND              : set to TRUE if ROOT found
#       If FIND_PACKAGE is called with REQUIRED and COMPONENTS arguments
#       ROOT_FOUND is only set to TRUE if ALL components are found.
#       If REQUIRED is NOT set components may or may not be available
#
#   ROOT_LIBRARIES          : list of ROOT libraries (NOT including COMPONENTS)
#   ROOT_INCLUDE_DIRS       : list of paths to be used with INCLUDE_DIRECTORIES
#   ROOT_LIBRARY_DIRS       : list of paths to be used with LINK_DIRECTORIES
#   ROOT_COMPONENT_LIBRARIES    : list of ROOT component libraries
#   ROOT_${COMPONENT}_FOUND     : set to TRUE or FALSE for each library
#   ROOT_${COMPONENT}_LIBRARY   : path to individual libraries
#   
#
#   Please note that by convention components should be entered exactly as
#   the library names, i.e. the component name equivalent to the library
#   $ROOTSYS/lib/libMathMore.so should be called MathMore and NOT:
#       mathmore or Mathmore or MATHMORE
#
#   However to follow the usual cmake convention it is agreed that the
#   ROOT_${COMPONENT}_FOUND and ROOT_${COMPONENT}_LIBRARY variables are ALL
#   uppercase, i.e. the MathMore component returns: ROOT_MATHMORE_FOUND and
#   ROOT_MATHMORE_LIBRARY NOT ROOT_MathMore_FOUND or ROOT_MathMore_LIBRARY
#
#
# The additional ROOT components should be defined as follows:
# FIND_PACKAGE( ROOT COMPONENTS MathMore Gdml Geom ...)
#
# If components are required use:
# FIND_PACKAGE( ROOT REQUIRED COMPONENTS MathMore Gdml Geom ...)
#
# If only root is required and components are NOT required use:
# FIND_PACKAGE( ROOT REQUIRED )
# FIND_PACKAGE( ROOT COMPONENTS MathMore Gdml Geom ... QUIET )
#   then you need to check for ROOT_MATHMORE_FOUND, ROOT_GDML_FOUND, etc.
#
# The variable ROOT_USE_COMPONENTS can also be used before calling
# FIND_PACKAGE, i.e.:
# SET( ROOT_USE_COMPONENTS MathMore Gdml Geom )
# FIND_PACKAGE( ROOT REQUIRED ) # all ROOT_USE_COMPONENTS must also be found
# FIND_PACKAGE( ROOT ) # check for ROOT_FOUND, ROOT_MATHMORE_FOUND, etc.
#
# @author Jan Engels, DESY
###############################################################################



# ==============================================
# ===        ROOT_CONFIG_EXECUTABLE          ===
# ==============================================

SET( ROOT_CONFIG_EXECUTABLE ROOT_CONFIG_EXECUTABLE-NOTFOUND )
MARK_AS_ADVANCED( ROOT_CONFIG_EXECUTABLE )
# FIND_PROGRAM: Once one of the calls succeeds the result variable will be set and stored in the cache so that no call will search again. 
FIND_PROGRAM( ROOT_CONFIG_EXECUTABLE root-config PATHS ${ROOT_DIR}/bin NO_DEFAULT_PATH )
FIND_PROGRAM( ROOT_CONFIG_EXECUTABLE root-config PATHS $ENV{ROOTSYS}/bin NO_DEFAULT_PATH)
FIND_PROGRAM( ROOT_CONFIG_EXECUTABLE root-config PATHS ENV PATH )
FIND_PROGRAM( ROOT_CONFIG_EXECUTABLE root-config )



IF( NOT ROOT_FIND_QUIETLY )
    MESSAGE( STATUS "Check for ROOT_CONFIG_EXECUTABLE: ${ROOT_CONFIG_EXECUTABLE}" )
ENDIF()


IF( ROOT_CONFIG_EXECUTABLE )


    # ==============================================
    # ===          ROOT_VERSION                  ===
    # ==============================================

    INCLUDE( MacroCheckPackageVersion )
    
    EXECUTE_PROCESS( COMMAND "${ROOT_CONFIG_EXECUTABLE}" --version
        OUTPUT_VARIABLE _version
        RESULT_VARIABLE _exit_code
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    IF( _exit_code EQUAL 0 )

        # set required variables for MacroCheckPackageVersion
        STRING(REGEX REPLACE "^([0-9]+).*" "\\1" ROOT_VERSION_MAJOR "${_version}")
        STRING(REGEX REPLACE "^[0-9]+.([0-9]+).*" "\\1" ROOT_VERSION_MINOR "${_version}")
        STRING(REGEX REPLACE "^[0-9]+.[0-9]+.([0-9]+).*" "\\1" ROOT_VERSION_PATCH "${_version}")

        SET( ROOT_VERSION "${ROOT_VERSION_MAJOR}.${ROOT_VERSION_MINOR}.${ROOT_VERSION_PATCH}" )
    ENDIF()

    CHECK_PACKAGE_VERSION( ROOT ${ROOT_VERSION} )



    # ==============================================
    # ===          ROOT_PREFIX                   ===
    # ==============================================

    # get root prefix from root-config output
    EXECUTE_PROCESS( COMMAND "${ROOT_CONFIG_EXECUTABLE}" --prefix
        OUTPUT_VARIABLE ROOT_PREFIX
        RESULT_VARIABLE _exit_code
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    IF( NOT _exit_code EQUAL 0 )
        # clear variable if root-config exits with error
        # it might contain garbage
        SET( ROOT_PREFIX )
    ENDIF()

    # PKG_ROOT variables are a cmake standard
    # since this package is also called ROOT the variable name
    # becomes ROOT_ROOT ...
    SET( ROOT_ROOT ${ROOT_PREFIX} )



    # ==============================================
    # ===          ROOT_BIN_DIR                  ===
    # ==============================================

    # get bindir from root-config output
    EXECUTE_PROCESS( COMMAND "${ROOT_CONFIG_EXECUTABLE}" --bindir
        OUTPUT_VARIABLE ROOT_BIN_DIR
        RESULT_VARIABLE _exit_code
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    IF( NOT _exit_code EQUAL 0 )
        # clear variable if root-config exits with error
        # it might contain garbage
        SET( ROOT_BIN_DIR )
    ENDIF()



    # ==============================================
    # ===          ROOT_EXECUTABLE               ===
    # ==============================================


    SET( ROOT_EXECUTABLE ROOT_EXECUTABLE-NOTFOUND )
    MARK_AS_ADVANCED( ROOT_EXECUTABLE )
    FIND_PROGRAM( ROOT_EXECUTABLE root PATHS ${ROOT_BIN_DIR} NO_DEFAULT_PATH )

    IF( NOT ROOT_FIND_QUIETLY )
        MESSAGE( STATUS "Check for ROOT_EXECUTABLE: ${ROOT_EXECUTABLE}" )
    ENDIF()




    # ==============================================
    # ===          ROOT_CINT_EXECUTABLE          ===
    # ==============================================


    # find rootcint
    SET( ROOT_CINT_EXECUTABLE ROOT_CINT_EXECUTABLE-NOTFOUND )
    MARK_AS_ADVANCED( ROOT_CINT_EXECUTABLE )
    FIND_PROGRAM( ROOT_CINT_EXECUTABLE rootcint PATHS ${ROOT_BIN_DIR} NO_DEFAULT_PATH )

    IF( NOT ROOT_FIND_QUIETLY )
        MESSAGE( STATUS "Check for ROOT_CINT_EXECUTABLE: ${ROOT_CINT_EXECUTABLE}" )
    ENDIF()



    # ==============================================
    # ===          ROOT_INCLUDE_DIR              ===
    # ==============================================

    # get include dir from root-config output
    EXECUTE_PROCESS( COMMAND "${ROOT_CONFIG_EXECUTABLE}" --incdir
        OUTPUT_VARIABLE _inc_dir
        RESULT_VARIABLE _exit_code
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    IF( NOT _exit_code EQUAL 0 )
        # clear variable if root-config exits with error
        # it might contain garbage
        SET( _inc_dir )
    ENDIF()


    SET( ROOT_INCLUDE_DIRS ROOT_INCLUDE_DIRS-NOTFOUND )
    MARK_AS_ADVANCED( ROOT_INCLUDE_DIRS )

    FIND_PATH( ROOT_INCLUDE_DIRS
        NAMES TH1.h
        PATHS ${ROOT_DIR}/include ${_inc_dir}
        NO_DEFAULT_PATH
    )



    # ==============================================
    # ===            ROOT_LIBRARIES              ===
    # ==============================================

    # get library dir from root-config output
    EXECUTE_PROCESS( COMMAND "${ROOT_CONFIG_EXECUTABLE}" --libdir
        OUTPUT_VARIABLE ROOT_LIBRARY_DIR
        RESULT_VARIABLE _exit_code
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    IF( NOT _exit_code EQUAL 0 )
        # clear variable if root-config exits with error
        # it might contain garbage
        SET( ROOT_LIBRARY_DIR )
    ENDIF()



    # ========== standard root libraries =================

    # standard root libraries (without components)
    SET( _root_libnames )

    # get standard root libraries from 'root-config --libs' output
    EXECUTE_PROCESS( COMMAND "${ROOT_CONFIG_EXECUTABLE}" --noauxlibs --libs
        OUTPUT_VARIABLE _aux
        RESULT_VARIABLE _exit_code
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    IF( _exit_code EQUAL 0 )
        
        # create a list out of the output
        SEPARATE_ARGUMENTS( _aux )

        # remove first item -L compiler flag
        LIST( REMOVE_AT _aux 0 )

        FOREACH( _lib ${_aux} )

            # extract libnames from -l compiler flags
            STRING( REGEX REPLACE "^-.(.*)$" "\\1" _libname "${_lib}")

            # fix for some root-config versions which export -lz even if using --noauxlibs
            IF( NOT _libname STREQUAL "z" )

                # append all library names into a list
                LIST( APPEND _root_libnames ${_libname} )

            ENDIF()

        ENDFOREACH()

    ENDIF()



    # ========== additional root components =================

    #LIST( APPEND ROOT_FIND_COMPONENTS Minuit2 ) # DEPRECATED !!!


    # ---------- libraries --------------------------------------------------------
    INCLUDE( MacroCheckPackageLibs )

    SET( ROOT_LIB_SEARCH_PATH ${ROOT_LIBRARY_DIR} )

    # only standard libraries should be passed as arguments to CHECK_PACKAGE_LIBS
    # additional components are set by cmake in variable PKG_FIND_COMPONENTS
    # first argument should be the package name
    CHECK_PACKAGE_LIBS( ROOT ${_root_libnames} )




    # ====== DL LIBRARY ==================================================
    # workaround for cmake bug in 64 bit:
    # see: http://public.kitware.com/mantis/view.php?id=10813
    IF( CMAKE_SIZEOF_VOID_P EQUAL 8 )
        FIND_LIBRARY( DL_LIB NAMES ${CMAKE_DL_LIBS} dl PATHS /usr/lib64 /lib64 NO_DEFAULT_PATH )
    ENDIF( CMAKE_SIZEOF_VOID_P EQUAL 8 )

    FIND_LIBRARY( DL_LIB NAMES ${CMAKE_DL_LIBS} dl )
    MARK_AS_ADVANCED( DL_LIB )

    IF( NOT ROOT_FIND_QUIETLY )
        MESSAGE( STATUS "Check for libdl.so: ${DL_LIB}" )
    ENDIF()

ENDIF( ROOT_CONFIG_EXECUTABLE )

# Threads library
#FIND_PACKAGE( Threads REQUIRED)


# ---------- final checking ---------------------------------------------------
INCLUDE( FindPackageHandleStandardArgs )
# set ROOT_FOUND to TRUE if all listed variables are TRUE and not empty
# ROOT_COMPONENT_VARIABLES will be set if FIND_PACKAGE is called with REQUIRED argument
FIND_PACKAGE_HANDLE_STANDARD_ARGS( ROOT DEFAULT_MSG ROOT_INCLUDE_DIRS ROOT_LIBRARIES ${ROOT_COMPONENT_VARIABLES} PACKAGE_VERSION_COMPATIBLE DL_LIB )

IF( ROOT_FOUND )
    LIST( APPEND ROOT_LIBRARIES ${DL_LIB} )
    # FIXME DEPRECATED
    SET( ROOT_DEFINITIONS "-DUSEROOT -DUSE_ROOT -DMARLIN_USE_ROOT" )
    MARK_AS_ADVANCED( ROOT_DEFINITIONS )

    # file including MACROS for generating root dictionary sources
    GET_FILENAME_COMPONENT( _aux ${CMAKE_CURRENT_LIST_FILE} PATH )
    SET( ROOT_DICT_MACROS_FILE ${_aux}/MacroRootDict.cmake )

ENDIF( ROOT_FOUND )

# ---------- cmake bug --------------------------------------------------------
# ROOT_FIND_REQUIRED is not reset between FIND_PACKAGE calls, i.e. the following
# code fails when geartgeo component not available: (fixed in cmake 2.8)
# FIND_PACKAGE( ROOT REQUIRED )
# FIND_PACKAGE( ROOT COMPONENTS geartgeo QUIET )
SET( ROOT_FIND_REQUIRED )