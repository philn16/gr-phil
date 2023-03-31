#pragma once
#include <gr_phil/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace gr_phil {

class GR_PHIL_API symbol_bert : virtual public gr::sync_block {
  public:
	typedef boost::shared_ptr<symbol_bert> sptr;
	static sptr make(int nbits_prbs, const std::vector<gr_complex>& constellation);
};

} // namespace gr_phil
} // namespace gr
