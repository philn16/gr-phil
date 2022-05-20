#ifndef INCLUDED_GR_PHIL_MUX_H
#define INCLUDED_GR_PHIL_MUX_H

#include <gr_phil/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace gr_phil {

/*!
 * \brief <+description of block+>
 * \ingroup gr_phil
 *
 */
class GR_PHIL_API mux : virtual public gr::sync_block {
  public:
	typedef boost::shared_ptr<mux> sptr;

	/*!
	 * \brief Return a shared_ptr to a new instance of gr_phil::mux.
	 *
	 * To avoid accidental use of raw pointers, gr_phil::mux's
	 * constructor is in a private implementation
	 * class. gr_phil::mux::make is the public interface for
	 * creating new instances.
	 */
	static sptr make(int select);
};

} // namespace gr_phil
} // namespace gr

#endif /* INCLUDED_GR_PHIL_MUX_H */

