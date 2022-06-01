#include "shared.hpp"
#include <gnuradio/io_signature.h>
#include <iostream>

namespace gr {
namespace gr_phil {

int dtype_size(_Dtype dtype) {
	switch ( dtype ) {
		case _Dtype::FLOAT:
			return sizeof(float);
		case _Dtype::COMPLEX:
			return sizeof(gr_complex);
		default:
			std::cout << "unrecognized dtype " << (int)dtype << "\n";
			return 0;
	}
}



}
}

