#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "tagger_rx_impl.h"

namespace gr {
namespace gr_phil {

tagger_rx::sptr tagger_rx::make(int dtype)    {
	return gnuradio::get_initial_sptr(new tagger_rx_impl(dtype));
}

tagger_rx_impl::tagger_rx_impl(int dtype):
	gr::sync_block("tagger_rx", gr::io_signature::make(1, 1, dtype_size((_Dtype)dtype)), gr::io_signature::make(1, 1, dtype_size((_Dtype)dtype))) {
	params.dtype = (_Dtype)dtype;
	PRINT_VAR(dtype);
}

tagger_rx_impl::~tagger_rx_impl() {
}

float tagger_rx_impl::get_freq(int i) {
	while ( i >= tags.offsets[tags.curindex] ) {
		if ( tags.curindex + 1 == tags.offsets.size() )
			break;
		tags.curindex += 1;
	}
	return tags.freqs[tags.curindex];
}

void tagger_rx_impl::update_tags() {

	tags.curindex = 0;
	tags.offsets.clear();
	tags.freqs.clear();

	long start_offset = tags.tags[0].offset;

	for( auto& tag : tags.tags) {
		tags.offsets.push_back(tag.offset - start_offset);
		if ( ! pmt::is_number(tag.value) ) {
			std::cout << tag.value << " not a number \n";
			this->d_logger->warn("expecting value to be a number");
			tags.freqs.push_back(pmt::to_double(0));
			continue;
		} else {
			tags.freqs.push_back(pmt::to_double(tag.value));
		}
	}
	if ( params.print_tag_offset ) {
		std::cout << "offsets: " << start_offset << "+" << tags.offsets << "\n";
		std::cout << "freqs:   " << tags.freqs << "\n";
	}
}

int tagger_rx_impl::work(int noutput_items, gr_vector_const_void_star &input_items, gr_vector_void_star &output_items) {
	get_tags_in_range(tags.tags, 0, nitems_read(0), nitems_read(0) + noutput_items);
	update_tags();



	for( int i=0; i < noutput_items; i++) {
		curfreq = get_freq(i);
		switch ( params.dtype ) {
			case _Dtype::FLOAT: {
				const float *in = (const float *) input_items[0];
				float *out = (float *) output_items[0];
				out[i] = in[i] * ( alpha_m1() + params.alpha * std::cos(this->angle));
				break;
			}
			case _Dtype::COMPLEX: {
				const gr_complex *in = (const gr_complex *) input_items[0];
				gr_complex *out = (gr_complex *) output_items[0];
				out[i] = in[i] * ( alpha_m1() + params.alpha * std::complex<float>(0,this->angle));
				break;
			}
		}
		// increment the angle by the current frequency
		this->angle += this->curfreq * M_PI*2;
	}

	// handle long term float rounding error by finding 2*pi modulo
	this->angle -= M_PI * int(this->angle / (2 * M_PI));

	return noutput_items;
}

} /* namespace gr_phil */
} /* namespace gr */

