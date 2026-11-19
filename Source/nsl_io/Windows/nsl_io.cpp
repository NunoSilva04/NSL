#include "nsl_io.hpp"
#include "nsl_string.hpp"
#include "nsl_types.hpp"
#include <windows.h>

namespace nsl {
    namespace io_detail {
	void write_argument(const io::NSL_CONSOLE_TYPE console_type, const nsl::string &string){
        HANDLE output; 

        switch(console_type){
            default:
            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_OUTPUT:
                output = GetStdHandle(STD_OUTPUT_HANDLE);
                WriteFile(output, string.data(), string.length(), nullptr, nullptr);
                break;

            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_INPUT:
                output = GetStdHandle(STD_INPUT_HANDLE);
                WriteFile(output, string.data(), string.length(), nullptr, nullptr);
                break;

            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_ERROR:
                output = GetStdHandle(STD_ERROR_HANDLE);
                WriteFile(output, string.data(), string.length(), nullptr, nullptr);
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
	    nsl::types::u32 index = buffer_size, number = u32;

        do{
            --index;
            buffer[index] = static_cast<char>('0' + number % 10);
            number /= 10;
        }while (number != 0);
  
        HANDLE output;
        switch(console_type){
            default:
            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_OUTPUT:
                output = GetStdHandle(STD_OUTPUT_HANDLE);
                WriteFile(output, &buffer[index], buffer_size - index, nullptr, nullptr);
                break;

            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_INPUT:
                output = GetStdHandle(STD_INPUT_HANDLE);
                WriteFile(output, &buffer[index], buffer_size - index, nullptr, nullptr);
                break;

            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_ERROR:
                output = GetStdHandle(STD_ERROR_HANDLE);
                WriteFile(output, &buffer[index], buffer_size - index, nullptr, nullptr);
                break;
        }

	    return;
	}

	void write_argument(const io::NSL_CONSOLE_TYPE console_type, const nsl::types::s32 &s32){
	    nsl::types::u32 magnitude = static_cast<nsl::types::u32>(s32);

        HANDLE output;
	    if(s32 < 0){
		switch(console_type){
		    default:
		    case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_OUTPUT:
                output = GetStdHandle(STD_OUTPUT_HANDLE);
                WriteFile(output, "-", 1, nullptr, nullptr);
                break;

            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_INPUT:
                output = GetStdHandle(STD_INPUT_HANDLE);
                WriteFile(output, "-", 1, nullptr, nullptr);
                break;

            case io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_ERROR:
                output = GetStdHandle(STD_ERROR_HANDLE);
                WriteFile(output, "-", 1, nullptr, nullptr);
                break;
            }
            magnitude = 0u - magnitude;
	    }

	    write_argument(console_type, magnitude);
	    return;
	}
    }
}
