#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "msg_tagger_impl.h"

#define PRINT_VAR(x) std::cout << #x << ": " << x << "\n"

namespace gr {
namespace gr_phil {

int dtpe_size(_Dtype dtype) {
	switch ( dtype ) {
		case _Dtype::COMPLEX:
			return sizeof(float);
		case _Dtype::FLOAT:
			return sizeof(gr_complex);
		default:
			std::cout << "unrecognized dtype " << (int)dtype << "\n";
			return 0;
	}
}

msg_tagger::sptr msg_tagger::make(int period, int dtype) {
	return gnuradio::get_initial_sptr(new msg_tagger_impl(period, dtype));
}

msg_tagger_impl::msg_tagger_impl(int period, int dtype) :
	gr::sync_block("msg_tagger", gr::io_signature::make(1, 1, dtpe_size((_Dtype)dtype)), gr::io_signature::make(1, 1, dtpe_size((_Dtype)dtype))) {
	PRINT_VAR(period);
	PRINT_VAR(dtype);

	params.period = period;
	params.dtype = (_Dtype)dtype;

	message_port_register_in(pmt::mp("tag_key"));
	set_msg_handler(pmt::mp("tag_key"),[this](const pmt::pmt_t& msg) { this->update_tag_key(msg); });
}

msg_tagger_impl::~msg_tagger_impl() {
}

void msg_tagger_impl::set_period(int period) {
	params.period = period;
}

void msg_tagger_impl::update_tag_key(const pmt::pmt_t& msg) {
	static auto freq_key = pmt::intern("freq");
	static auto ampl_key = pmt::intern("ampl");
	static auto phase_key = pmt::intern("phase");
	static auto offset_key = pmt::intern("offset");

	std::cout << __FUNCTION__ << ": " << msg << "\n";

	// a msg can be both a pair and a dict for some reason
	if (pmt::is_dict(msg))
		std::cout << "is_dict()==true\n";
	if (pmt::is_pair(msg))
		std::cout << "is_pair()==true\n";
	if (pmt::is_number(msg))
		std::cout << "is_number()==true\n";

	// either a key:value pair or a dict
	// create a dict if we get a list of pairs if we get a list of paris, pair, or just a number
	pmt::pmt_t list_of_items;
	if (pmt::is_dict(msg)) {
		// list_of_items = pmt::dict_items(msg);
		list_of_items = pmt::list1(msg);
	} else if (pmt::is_pair(msg)) {
		list_of_items = pmt::list1(msg);
	} else if (pmt::is_number(msg)) {
		this->d_logger->warn("expecting a dict or pair");
		return;
	} else {
		this->d_logger->warn("expecting a dict or pair");
		return;
	}

	std::cout << "list_of_items: " << list_of_items << "\n";

	// iterate through list_of_items. Unfortunately iterators are not supported :(
	do {
		auto item = pmt::car(list_of_items);
		std::cout << "item: " << item << "\n";

		auto key = pmt::car(item);
		std::cout << "key: " << key << "\n";

		auto val = pmt::cdr(item);
		if (! pmt::is_number(val)) {
			std::cout << "val: " << val << "\n";
			this->d_logger->warn("expecting value to be a number");
			continue;
		}
		if (key == freq_key)
			this->freq = pmt::to_double(val);
		else {
			std::string keystr = pmt::symbol_to_string(key);
			this->d_logger->warn(("unknown key \""+keystr+"\"").c_str());
		}

		// advance to next item
		list_of_items = pmt::cdr(list_of_items);
	} while (list_of_items != pmt::PMT_NIL);
	std::cout << "\n";
}

void msg_tagger_impl::increment_sampnum(int i) {
	samp_num++;
	if ( samp_num < params.period )
		return;
	samp_num = 0;
	char buff[20];
	sprintf(buff,"%g",freq);
	auto key = pmt::string_to_symbol("freq");
	auto val = pmt::string_to_symbol(buff);
	int output=0;
	this->add_item_tag(0,this->nitems_written(0)+i,key,val);
}

int msg_tagger_impl::work(int noutput_items, gr_vector_const_void_star &input_items, gr_vector_void_star &output_items) {

	switch ( params.dtype ) {
		case _Dtype::FLOAT: {
			const float *in = (const float *) input_items[0];
			float *out = (float *) output_items[0];
			for( int i=0; i < noutput_items; i++) {
				out[i] = in[i];
				increment_sampnum(i);
			}
			break;
		}
		case _Dtype::COMPLEX: {
			const gr_complex *in = (const gr_complex *) input_items[0];
			gr_complex *out = (gr_complex *) output_items[0];
			for( int i=0; i < noutput_items; i++) {
				out[i] = in[i];
				increment_sampnum(i);
			}
			break;
		}
	}

	return noutput_items;
}

} /* namespace gr_phil */
} /* namespace gr */

