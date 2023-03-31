#pragma once
#include <gr_phil/symbol_bert.h>

namespace gr {
namespace gr_phil {

class symbol_bert_impl : public symbol_bert {
  private:
  public:
	symbol_bert_impl(int nbits_prbs, const std::vector<gr_complex>& constellation);
	~symbol_bert_impl();
	int work( int noutput_items, gr_vector_const_void_star &input_items, gr_vector_void_star &output_items);
};

} // namespace gr_phil
} // namespace gr

