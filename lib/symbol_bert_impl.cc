#include <gnuradio/io_signature.h>
#include "symbol_bert_impl.h"
#include <complex>
#include <iostream>
using std::cout;
using std::endl;

namespace gr {
namespace gr_phil {

symbol_bert::sptr symbol_bert::make(int nbits_prbs, const std::vector<gr_complex>& constellation, int print_samp_interval) {
	return gnuradio::get_initial_sptr(new symbol_bert_impl(nbits_prbs,constellation,print_samp_interval));
}

static int log2(int n) {
	int _log2=0;
	while(n > 1 ) {
		n = n / 2;
		_log2++;
	}
	return _log2;
}

symbol_bert_impl::symbol_bert_impl(int nbits_prbs, const std::vector<gr_complex>& constellation, int print_samp_interval)
	: gr::sync_block("symbol_bert", gr::io_signature::make(1,1, sizeof(gr_complex)), gr::io_signature::make(1,1,sizeof(gr_complex))) {

	cout << "nbits_prbs:\n\t" << nbits_prbs << "\n";
	cout << "constellation:\n";
	for( gr_complex v : constellation )
		cout << "\t"<<v<<"\n";

	sync.init(nbits_prbs,log2(constellation.size()),constellation);
	this->print_samp_interval=print_samp_interval;

	// cout << "\33[1m\33[36m" << __FUNCTION__ << "\n" << __DATE__ << " " << __TIME__ << "\33[0m" << "\n\n";
}

symbol_bert_impl::~symbol_bert_impl() {
}

int symbol_bert_impl::work(int noutput_items, gr_vector_const_void_star &input_items, gr_vector_void_star &output_items) {
	const gr_complex *in = (const gr_complex*) input_items[0];
	gr_complex *out = (gr_complex *) output_items[0];

	std::vector<gr_complex> in_v(in,in+noutput_items);

	Symbol_Sync::Work_Return ret = sync.work(in_v);

	for( int i=0; i < ret.decision_actual.size(); i++) {
		// we want the output to be phase corrected but not amplitude corrected so that a combiner algorithm might combine multiple signals intellegently
		out[i] = ret.mult_to_decision[i] / std::abs(ret.mult_to_decision[i]) * in[i];
	}

	for( bool error : ret.error ) {
		total_samp_count++;
		for( Error_Capture_Interval &v : error_capture_intervals) {
			v.current_count++;
			if ( error )
				v.current_error_count++;
			// reset the counter and set the last error count once our count has reached the particular counting interval
			if ( v.current_count == v.interval ) {
				v.last_error_count = v.current_error_count;
				v.current_count=0;
				v.current_error_count=0;
			}
		}
		// TODO: send messge with error counts
		if ( ++print_interval_tracker >= print_samp_interval && print_samp_interval > 0) {
			cout << "\n";
			cout << "["<<total_samp_count<<"]"<<"\n";
			for( Error_Capture_Interval &v : error_capture_intervals) {
				// if ( v.last_error_count > 0 ) {
				cout << v.last_error_count << "/" << v.interval << "\n";
				// }
			}
			cout << "\n";
			print_interval_tracker=0;
		}
	}
	return noutput_items;
}

} /* namespace gr_phil */
} /* namespace gr */

