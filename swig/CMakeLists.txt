########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT gr_phil_sources)
    MESSAGE(STATUS "No C++ sources... skipping swig/")
    return()
endif(NOT gr_phil_sources)

########################################################################
# Include swig generation macros
########################################################################
find_package(SWIG)
find_package(PythonLibs)
if(NOT SWIG_FOUND OR NOT PYTHONLIBS_FOUND)
    return()
endif()
include(GrSwig)
include(GrPython)

########################################################################
# Setup swig generation
########################################################################
set(GR_SWIG_INCLUDE_DIRS $<TARGET_PROPERTY:gnuradio::runtime_swig,INTERFACE_INCLUDE_DIRECTORIES>)
set(GR_SWIG_TARGET_DEPS gnuradio::runtime_swig)

set(GR_SWIG_LIBRARIES gnuradio-gr_phil)

set(GR_SWIG_DOC_FILE ${CMAKE_CURRENT_BINARY_DIR}/gr_phil_swig_doc.i)
set(GR_SWIG_DOC_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include)

GR_SWIG_MAKE(gr_phil_swig gr_phil_swig.i)

########################################################################
# Install the build swig module
########################################################################
GR_SWIG_INSTALL(TARGETS gr_phil_swig DESTINATION ${GR_PYTHON_DIR}/gr_phil)

########################################################################
# Install swig .i files for development
########################################################################
install(
    FILES
    gr_phil_swig.i
    ${CMAKE_CURRENT_BINARY_DIR}/gr_phil_swig_doc.i
    DESTINATION ${GR_INCLUDE_DIR}/gr_phil/swig
)
