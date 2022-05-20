#ifndef INCLUDED_GR_PHIL_MUX_IMPL_H
#define INCLUDED_GR_PHIL_MUX_IMPL_H

#include <gr_phil/mux.h>

namespace gr {
namespace gr_phil {

class mux_impl : public mux {
  private:
	// Nothing to declare in this block.

  public:
	mux_impl(int select);
	~mux_impl();

	// Where all the action really happens
	int work(
	    int noutput_items,
	    gr_vector_const_void_star &input_items,
	    gr_vector_void_star &output_items
	);
};

} // namespace gr_phil
} // namespace gr

#endif /* INCLUDED_GR_PHIL_MUX_IMPL_H */

