#include <gnuradio/io_signature.h>
#include "symbol_bert_impl.h"
#include <iostream>
using std::cout;
using std::endl;

namespace gr {
namespace gr_phil {

symbol_bert::sptr symbol_bert::make(int nbits_prbs, const std::vector<gr_complex>& constellation) {
	return gnuradio::get_initial_sptr(new symbol_bert_impl(nbits_prbs,constellation));
}

static int log2(int n) {
	int _log2=0;
	while(n > 1 ) {
		n = n / 2;
		_log2++;
	}
	return _log2;
}

symbol_bert_impl::symbol_bert_impl(int nbits_prbs, const std::vector<gr_complex>& constellation)
	: gr::sync_block("symbol_bert", gr::io_signature::make(1,1, sizeof(gr_complex)), gr::io_signature::make(0,0,sizeof(gr_complex))) {

	cout << "nbits_prbs:\n\t" << nbits_prbs << "\n";
	cout << "constellation:\n";
	for( gr_complex v : constellation )
		cout << "\t"<<v<<"\n";

	sync.init(nbits_prbs,log2(constellation.size()),constellation);

}

symbol_bert_impl::~symbol_bert_impl() {
}

int symbol_bert_impl::work(int noutput_items, gr_vector_const_void_star &input_items, gr_vector_void_star &output_items) {
	const gr_complex *in = (const gr_complex*) input_items[0];
	gr_complex *out = (gr_complex *) output_items[0];


	return noutput_items;
}

} /* namespace gr_phil */
} /* namespace gr */

