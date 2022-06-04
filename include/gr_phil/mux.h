#ifndef INCLUDED_GR_PHIL_MUX_H
#define INCLUDED_GR_PHIL_MUX_H

#include <gr_phil/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace gr_phil {

class GR_PHIL_API mux : virtual public gr::sync_block {
  public:
	typedef boost::shared_ptr<mux> sptr;

	static sptr make(int select, int num_inputs, int dtype);

	virtual void set_select(int select) = 0;
};

} // namespace gr_phil
} // namespace gr

#endif /* INCLUDED_GR_PHIL_MUX_H */

