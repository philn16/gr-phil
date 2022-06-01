#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "mux_impl.h"

namespace gr {
namespace gr_phil {

mux::sptr mux::make(int select, int num_inputs) {
	return gnuradio::get_initial_sptr
	       (new mux_impl(select,num_inputs));
}

mux_impl::mux_impl(int select, int num_inputs):
	gr::sync_block("mux", gr::io_signature::make(num_inputs, num_inputs, sizeof(float)), gr::io_signature::make(1, 1, sizeof(float))) {
	this->select = select;
	this->num_inputs = num_inputs;
}

void mux_impl::set_select(int select) {
	this->select = select;
}

mux_impl::~mux_impl() {}

int mux_impl::work(int noutput_items, gr_vector_const_void_star &input_items, gr_vector_void_star &output_items) {
	const float *in = (const float *) input_items[this->select];
	float *out = (float *) output_items[0];

	for( int i=0; i < noutput_items; i++)
		out[i] = in[i];
	return noutput_items;
}

} /* namespace gr_phil */
} /* namespace gr */

