#pragma once
#include <gr_phil/symbol_bert.h>

#include "pyphil/symbol_sync.hpp"

namespace gr {
namespace gr_phil {

/*
Inputs:
	Takes a sync pattern as a predetermined PRBS sequence of some number of bits.
	Takes timing syncronized constellation points

Outputs:
	Prints bit error rate
	Outputs the symbols after performing phase synchronization based on the PRBS sequence
*/
class symbol_bert_impl : public symbol_bert {
  private:
	Symbol_Sync sync;
	int print_samp_interval = 1e3;
	int print_interval_tracker=0;
	long total_samp_count=0;

	struct Error_Capture_Interval {
		Error_Capture_Interval(int interval) {
			this->interval=interval;
		}
		int interval;
		// state variables
		int current_error_count=0;
		int last_error_count=-1;
		int current_count=0;
	};

	std::vector<Error_Capture_Interval> error_capture_intervals = {Error_Capture_Interval(1e3),Error_Capture_Interval(1e4),Error_Capture_Interval(1e5),Error_Capture_Interval(1e6),Error_Capture_Interval(1e7) };

  public:
	symbol_bert_impl(const std::vector<gr_complex>& constellation, int print_samp_interval, const std::vector<gr_complex>& sequence);
	~symbol_bert_impl();
	int work( int noutput_items, gr_vector_const_void_star &input_items, gr_vector_void_star &output_items);
};

} // namespace gr_phil
} // namespace gr

