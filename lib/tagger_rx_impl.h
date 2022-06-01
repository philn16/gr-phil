#pragma once
#include <gr_phil/tagger_rx.h>
#include <cmath>
#include "shared.hpp"

namespace gr {
namespace gr_phil {

class tagger_rx_impl : public tagger_rx {
  private:

	struct _Params {
		_Dtype dtype;
		bool print_tag_offset = false;
		float alpha = 1;
	} params;

	inline float alpha_m1() {
		return 1-params.alpha;
	}

	float angle = 0;
	float curfreq=0;

	struct _Tags {
		std::vector<tag_t> tags;
		std::vector<long> offsets;
		std::vector<float> freqs;
		int curindex;
	} tags;

	float get_freq(int i);

	void update_tags();

  public:
	tagger_rx_impl(int dtype);
	~tagger_rx_impl();

	int work( int noutput_items, gr_vector_const_void_star &input_items, gr_vector_void_star &output_items ) override;
};

} // namespace gr_phil
} // namespace gr
