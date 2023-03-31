
########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

list(APPEND gr_phil_sources
    mux_impl.cc
    msg_tagger_impl.cc
    tagger_rx_impl.cc
    shared.cpp
    symbol_bert_impl.cc
)

set(gr_phil_sources "${gr_phil_sources}" PARENT_SCOPE)
if(NOT gr_phil_sources)
    MESSAGE(STATUS "No C++ sources... skipping lib/")
    return()
endif(NOT gr_phil_sources)

add_library(gnuradio-gr_phil SHARED ${gr_phil_sources})
target_link_libraries(gnuradio-gr_phil gnuradio::gnuradio-runtime)
target_include_directories(gnuradio-gr_phil
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    PUBLIC $<INSTALL_INTERFACE:include>
  )
set_target_properties(gnuradio-gr_phil PROPERTIES DEFINE_SYMBOL "gnuradio_gr_phil_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-gr_phil PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-gr_phil)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

# If your unit tests require special include paths, add them here
#include_directories()
# List all files that contain Boost.UTF unit tests here
list(APPEND test_gr_phil_sources
)
# Anything we need to link to for the unit tests go here
list(APPEND GR_TEST_TARGET_DEPS gnuradio-gr_phil)

if(NOT test_gr_phil_sources)
    MESSAGE(STATUS "No C++ unit tests... skipping")
    return()
endif(NOT test_gr_phil_sources)

foreach(qa_file ${test_gr_phil_sources})
    GR_ADD_CPP_TEST("gr_phil_${qa_file}"
        ${CMAKE_CURRENT_SOURCE_DIR}/${qa_file}
    )
endforeach(qa_file)
