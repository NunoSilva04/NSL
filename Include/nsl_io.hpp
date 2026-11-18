#ifndef __NSL_IO_HPP__
#define __NSL_IO_HPP__

#include "nsl_string.hpp"
#include "nsl_types.hpp"

namespace nsl {
    namespace io_detail {
	void print_argument(const nsl::string &string);
	void print_argument(const char *string);
	void print_argument(const nsl::types::u32 &u32);

	template<typename Last_Argument>
	void print_all_arguments(const Last_Argument &last){
	    print_argument(last);

	    return;
	}

	template<typename First_Argument, typename... Last_Argument>
	void print_all_arguments(const First_Argument &first, const Last_Argument&... last){
	    print_argument(first);
	    print_all_arguments(last...);

	    return;
	}
    }

    namespace io {
	template<typename First_Argument, typename... Last_Argument>
	void print_to_console(const First_Argument &first, const Last_Argument&... rest){
	    io_detail::print_all_arguments(first, rest...);

	    return;
	}
    }
}

#endif // __NSL_IO_HPP__
