/* -*- c++ -*- */

#define GR_PHIL_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "gr_phil_swig_doc.i"

%{
#include "gr_phil/mux.h"
#include "gr_phil/msg_tagger.h"
#include "gr_phil/tagger_rx.h"
#include "gr_phil/symbol_bert.h"
%}

%include "gr_phil/mux.h"
GR_SWIG_BLOCK_MAGIC2(gr_phil, mux);
%include "gr_phil/msg_tagger.h"
GR_SWIG_BLOCK_MAGIC2(gr_phil, msg_tagger);
%include "gr_phil/tagger_rx.h"
GR_SWIG_BLOCK_MAGIC2(gr_phil, tagger_rx);
%include "gr_phil/symbol_bert.h"
GR_SWIG_BLOCK_MAGIC2(gr_phil, symbol_bert);
