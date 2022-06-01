#ifndef INCLUDED_GR_PHIL_MSG_TAGGER_H
#define INCLUDED_GR_PHIL_MSG_TAGGER_H

#include <gr_phil/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace gr_phil {


class GR_PHIL_API msg_tagger : virtual public gr::sync_block {
  public:
	typedef boost::shared_ptr<msg_tagger> sptr;

	static sptr make(int period=100, int dtype=0);
};

} // namespace gr_phil
} // namespace gr

#endif /* INCLUDED_GR_PHIL_MSG_TAGGER_H */

