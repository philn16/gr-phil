INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_GR_PHIL gr_phil)

FIND_PATH(
    GR_PHIL_INCLUDE_DIRS
    NAMES gr_phil/api.h
    HINTS $ENV{GR_PHIL_DIR}/include
        ${PC_GR_PHIL_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_PHIL_LIBRARIES
    NAMES gnuradio-gr_phil
    HINTS $ENV{GR_PHIL_DIR}/lib
        ${PC_GR_PHIL_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gr_philTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_PHIL DEFAULT_MSG GR_PHIL_LIBRARIES GR_PHIL_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_PHIL_LIBRARIES GR_PHIL_INCLUDE_DIRS)
