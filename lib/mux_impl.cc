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
	set_tag_propagation_policy(tag_propagation_policy_t::TPP_CUSTOM);
}

void mux_impl::set_select(int select) {
	this->select = select;
}

mux_impl::~mux_impl() {}

int mux_impl::work(int noutput_items, gr_vector_const_void_star &input_items, gr_vector_void_star &output_items) {
	const void *in = input_items[select];
	void *out = output_items[0];

	memcpy(out,in,dtype_size(dtype)*noutput_items);

	if ( handle_tags ) {
		get_tags_in_range(tags, select, nitems_read(select), nitems_read(select) + noutput_items);
		for( tag_t& tag : tags )
			add_item_tag(0,tag);
	}

	return noutput_items;
}

} /* namespace gr_phil */
} /* namespace gr */

