#pragma once

#include <gr_phil/msg_tagger.h>
#include <string>

namespace gr {
namespace gr_phil {

enum class _Dtype {FLOAT = 0, COMPLEX = 1};

class msg_tagger_impl : public msg_tagger {
  private:

	struct _Params {
		_Dtype dtype;
		int period;
	} params;

	std::string tag_key = "default";
	long packet_number = 0;
	int samp_num = 0;
	double freq = 0;

	void increment_sampnum(int i);

	void update_tag_key(const pmt::pmt_t& msg);
  public:
	msg_tagger_impl(int period, int dtype);
	~msg_tagger_impl();

	void set_period(int period) override;

	int work( int noutput_items, gr_vector_const_void_star &input_items, gr_vector_void_star &output_items ) override;
};

} // namespace gr_phil
} // namespace gr
