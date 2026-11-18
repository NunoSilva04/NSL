#include "nsl_io.hpp"
#include "nsl_string.hpp"
#include "nsl_types.hpp"
#include <windows.h>

namespace nsl {
    namespace io_detail {
	void print_argument(const io::NSL_CONSOLE_TYPE console_type, const nsl::string &string){
        HANDLE output; 

        switch(console_type){
            default:
            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_OUTPUT:
                output = GetStdHandle(STD_OUTPUT_HANDLE);
                WriteFile(output, string.data(), string.length(), nullptr, nullptr);
                break;

            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_INPUT:

                break;

            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_ERROR:

                break;
        }

	    return;
	}
	
	void print_argument(const io::NSL_CONSOLE_TYPE console_type, const char *string){
        HANDLE output; 
	    nsl::string nsl_string(string);

        switch(console_type){
            default:
            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_OUTPUT:
                output = GetStdHandle(STD_OUTPUT_HANDLE);
                WriteFile(output, nsl_string.data(), nsl_string.length(), nullptr, nullptr);
                break;

            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_INPUT:

                break;

            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_ERROR:

                break;
        }

	    return;
	}

	void print_argument(const io::NSL_CONSOLE_TYPE console_type, const nsl::types::u32 &u32){
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
  
        HANDLE output;
        switch(console_type){
            default:
            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_OUTPUT:
                output = GetStdHandle(STD_OUTPUT_HANDLE);
                WriteFile(output, &buffer[index], buffer_size - index, nullptr, nullptr);
                break;

            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_INPUT:

                break;

            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_ERROR:

                break;
        }

	    return;
	}

	void print_argument(const io::NSL_CONSOLE_TYPE console_type, const nsl::types::s32 &s32){
	    nsl::types::u32 magnitude = static_cast<nsl::types::u32>(s32);

	    if(s32 < 0){
		    magnitude = 0u - magnitude;
	    }

	    print_argument(console_type, magnitude);
	    return;
	}
    }
}
