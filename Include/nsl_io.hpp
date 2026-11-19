#ifndef __NSL_IO_HPP__
#define __NSL_IO_HPP__

#include "nsl_string.hpp"
#include "nsl_types.hpp"

namespace nsl {
    namespace io {
	enum class NSL_CONSOLE_TYPE{
	    NSL_CONSOLE_TYPE_OUTPUT,
	    NSL_CONSOLE_TYPE_INPUT,
	    NSL_CONSOLE_TYPE_ERROR,
	};
    }	
	
    namespace io_detail {
	void write_argument(const io::NSL_CONSOLE_TYPE console_type, const nsl::string &string);
	void write_argument(const io::NSL_CONSOLE_TYPE console_type, const char *string);
	void write_argument(const io::NSL_CONSOLE_TYPE console_type, const nsl::types::u32 &u32);
	void write_argument(const io::NSL_CONSOLE_TYPE console_type, const nsl::types::s32 &s32);

	template<typename Last_Argument>
	void write_all_arguments(const io::NSL_CONSOLE_TYPE console_type, const Last_Argument &last){
	    write_argument(console_type, last);

	    return;
	}

	template<typename First_Argument, typename... Last_Argument>
	void write_all_arguments(const io::NSL_CONSOLE_TYPE console_type, const First_Argument &first, const Last_Argument&... last){
	    write_argument(console_type, first);
	    write_all_arguments(console_type, last...);

	    return;
	}
    }

    namespace io {
	template<typename First_Argument, typename... Last_Argument>
	void write_to_console(const NSL_CONSOLE_TYPE console_type, First_Argument &first, const Last_Argument&... rest){
	    io_detail::write_all_arguments(console_type, first, rest...);

	    return;
	}
    }
}

#endif // __NSL_IO_HPP__
