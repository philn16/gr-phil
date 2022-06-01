#pragma once
#include <gr_phil/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace gr_phil {

class GR_PHIL_API tagger_rx : virtual public gr::sync_block    {
  public:
	typedef boost::shared_ptr<tagger_rx> sptr;

	static sptr make(int dtype=0);
};

} // namespace gr_phil
} // namespace gr
