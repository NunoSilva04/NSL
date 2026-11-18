#include "nsl_io.hpp"
#include <unistd.h>

namespace nsl {
    namespace io{
	void print_to_console(const char *string, int size){
	    write(STDOUT_FILENO, string, size);

	    return;
	}
    }
}
