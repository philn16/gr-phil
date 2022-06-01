#pragma once
#include <sstream>
#include <vector>

#define PRINT_VAR(x) std::cout << #x << ": " << x << "\n"

namespace gr {
namespace gr_phil {
enum class _Dtype {COMPLEX = 0, FLOAT = 1};

//! returns the sizeof() for a given dtype
int dtype_size(_Dtype dtype);

template<class T>
std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, std::vector<T>& vec) {
	os << "[";
	for( auto& v : vec )
		os << v << ",";
	os << "]";
	return os;
}

}
}
