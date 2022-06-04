#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "mux_impl.h"
#include <string.h>

namespace gr {
namespace gr_phil {

mux::sptr mux::make(int select, int num_inputs, int dtype) {
	return gnuradio::get_initial_sptr (new mux_impl(select,num_inputs,dtype));
}

mux_impl::mux_impl(int select, int num_inputs, int dtype):
	// we have n inputs and just 1 output
	gr::sync_block("mux", gr::io_signature::make(num_inputs, num_inputs, dtype_size((_Dtype)dtype)), gr::io_signature::make(1, 1, dtype_size((_Dtype)dtype))) {
	this->select = select;
	this->num_inputs = num_inputs;
	this->dtype = (_Dtype)dtype;
}

void mux_impl::set_select(int select) {
	this->select = select;
}

mux_impl::~mux_impl() {}

int mux_impl::work(int noutput_items, gr_vector_const_void_star &input_items, gr_vector_void_star &output_items) {
	const void *in = input_items[this->select];
	void *out = output_items[0];

	memcpy(out,in,dtype_size(dtype)*noutput_items);

	return noutput_items;
}

} /* namespace gr_phil */
} /* namespace gr */

