#pragma once
#include <gr_phil/mux.h>
#include "shared.hpp"

namespace gr {
namespace gr_phil {

class mux_impl : public mux {
  private:

	int select;
	_Dtype dtype;
	int num_inputs;
	std::vector<tag_t> tags;
	bool handle_tags = true;

  public:
	mux_impl(int select, int num_inputs, int dtype);
	~mux_impl();

	void set_select(int select);

	// Where all the action really happens
	int work(
	    int noutput_items,
	    gr_vector_const_void_star &input_items,
	    gr_vector_void_star &output_items
	);
};

} // namespace gr_phil
} // namespace gr
