#include "nsl_io.hpp"
#include <unistd.h>

namespace nsl {
    namespace io_detail {
	void print_argument(const nsl::string &string){
	    write(STDOUT_FILENO, string.data(), string.length());

	    return;
	}
    }
}
