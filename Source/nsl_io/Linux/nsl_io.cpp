#include "nsl_io.hpp"
#include "nsl_string.hpp"
#include "nsl_types.hpp"
#include <unistd.h>

namespace nsl {
    namespace io_detail {
	void write_argument(const io::NSL_CONSOLE_TYPE console_type, const nsl::string &string){
	    switch(console_type){
		default:
		case io::NSL_CONSOLE_TYPE::OUTPUT:
		    write(STDOUT_FILENO, string.data(), string.length());
		    break;

		case io::NSL_CONSOLE_TYPE::INPUT:
		    write(STDIN_FILENO, string.data(), string.length());
		    break;

		case io::NSL_CONSOLE_TYPE::ERROR:
		    write(STDERR_FILENO, string.data(), string.length());
		    break;
	    }


	    return;
	}
	
	void write_argument(const io::NSL_CONSOLE_TYPE console_type, const char *string){
	    nsl::string nsl_string(string);
	    write_argument(console_type, nsl_string);

	    return;
	}

	void write_argument(const io::NSL_CONSOLE_TYPE console_type, const nsl::types::u32 &u32){
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
	    switch(console_type){
		default:
		case io::NSL_CONSOLE_TYPE::OUTPUT:
		    write(STDOUT_FILENO, &buffer[index], buffer_size - index);
		    break;

		case io::NSL_CONSOLE_TYPE::INPUT:
		    write(STDIN_FILENO, &buffer[index], buffer_size - index);
		    break;

		case io::NSL_CONSOLE_TYPE::ERROR:
		    write(STDERR_FILENO, &buffer[index], buffer_size - index);
		    break;
	    }

	    return;
	}

	void write_argument(const io::NSL_CONSOLE_TYPE console_type, const nsl::types::s32 &s32){
	    nsl::types::u32 magnitude = static_cast<nsl::types::u32>(s32);

	    if(s32 < 0){
		switch(console_type){
		    default:
		    case io::NSL_CONSOLE_TYPE::OUTPUT:
			write(STDOUT_FILENO, "-", 1);
			break;

		    case io::NSL_CONSOLE_TYPE::INPUT:
			write(STDIN_FILENO, "-", 1);
			break;

		    case io::NSL_CONSOLE_TYPE::ERROR:
			write(STDERR_FILENO, "-", 1);
			break;
		}
		magnitude = 0u - magnitude;
	    }

	    write_argument(console_type, magnitude);
	    return;
	}
    }
}
