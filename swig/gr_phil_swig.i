/* -*- c++ -*- */

#define GR_PHIL_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "gr_phil_swig_doc.i"

%{
#include "gr_phil/mux.h"
%}

%include "gr_phil/mux.h"
GR_SWIG_BLOCK_MAGIC2(gr_phil, mux);
