#include "nsl_io.hpp"
#include "nsl_string.hpp"
#include "nsl_types.hpp"
#include <unistd.h>

namespace nsl {
    namespace io_detail {
	void print_argument(const nsl::string &string){
	    write(STDOUT_FILENO, string.data(), string.length());

	    return;
	}
	
	void print_argument(const char *string){
	    nsl::string nsl_string(string);
	    write(STDOUT_FILENO, nsl_string.data(), nsl_string.length());

	    return;
	}

	void print_argument(const nsl::types::u32 &u32){
	    constexpr nsl::types::u32 buffer_size = 10;
	    char buffer[buffer_size] = {};
	    nsl::types::u32 index = buffer_size - 1, number = u32;

	    while(number != 0){
		char curr_digit = '0' + static_cast<char>(number % 10);
		buffer[index] = curr_digit;

		number /= 10;
		index--;
	    }

	    index += 1;	// Because the index always ends up one digit before the actual string
	    write(STDOUT_FILENO, &buffer[index], buffer_size - index);

	    return;
	}

	void print_argument(const nsl::types::s32 &s32){
	    nsl::types::u32 magnitude = static_cast<nsl::types::u32>(s32);

	    if(s32 < 0){
		write(STDOUT_FILENO, "-", 1);
		magnitude = 0u - magnitude;
	    }

	    print_argument(magnitude);
	    return;
	}
    }
}
