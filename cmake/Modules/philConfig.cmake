INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_PHIL phil)

FIND_PATH(
    PHIL_INCLUDE_DIRS
    NAMES phil/api.h
    HINTS $ENV{PHIL_DIR}/include
        ${PC_PHIL_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    PHIL_LIBRARIES
    NAMES gnuradio-phil
    HINTS $ENV{PHIL_DIR}/lib
        ${PC_PHIL_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PHIL DEFAULT_MSG PHIL_LIBRARIES PHIL_INCLUDE_DIRS)
MARK_AS_ADVANCED(PHIL_LIBRARIES PHIL_INCLUDE_DIRS)

