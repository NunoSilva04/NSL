#ifndef __NSL_IO_HPP__
#define __NSL_IO_HPP__

#include "nsl_string.hpp"
#include "nsl_types.hpp"

namespace nsl {
	namespace io {
		enum NSL_CONSOLE_TYPE{
			NSL_CONSOLE_TYPE_OUTPUT,
			NSL_CONSOLE_TYPE_INPUT,
			NSL_CONSOLE_TYPE_ERROR,
		};
	}	
	
    namespace io_detail {
	void print_argument(const io::NSL_CONSOLE_TYPE console_type, const nsl::string &string);
	void print_argument(const io::NSL_CONSOLE_TYPE console_type, const char *string);
	void print_argument(const io::NSL_CONSOLE_TYPE console_type, const nsl::types::u32 &u32);
	void print_argument(const io::NSL_CONSOLE_TYPE console_type, const nsl::types::s32 &s32);

	template<typename Last_Argument>
	void print_all_arguments(const io::NSL_CONSOLE_TYPE console_type, const Last_Argument &last){
	    print_argument(console_type, last);

	    return;
	}

	template<typename First_Argument, typename... Last_Argument>
	void print_all_arguments(const io::NSL_CONSOLE_TYPE console_type, const First_Argument &first, const Last_Argument&... last){
	    print_argument(console_type, first);
	    print_all_arguments(console_type, last...);

	    return;
	}
    }

    namespace io {
	template<typename First_Argument, typename... Last_Argument>
	void print_to_console(const NSL_CONSOLE_TYPE console_type, First_Argument &first, const Last_Argument&... rest){
	    io_detail::print_all_arguments(console_type, first, rest...);

	    return;
	}
    }
}

#endif // __NSL_IO_HPP__
