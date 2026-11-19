#ifndef __NSL_STRING_HPP__
#define __NSL_STRING_HPP__

#include "nsl_types.hpp"

namespace nsl {
    class string{
	public:
	    string(const char *data);
	    string(char *data) : string(static_cast<const char *>(data)) {};
	    string();
	    string(const string &data) : string(data.data()) {};
	    ~string();
	    string &operator=(const string &string_2);
	    string &operator=(const char *string);
	    string &operator=(char *string);

	    nsl::types::u32 length(void) const;
	    nsl::types::u32 capacity(void) const;
	    void resize(void);
	    void resize(nsl::types::u32 specific_capacity);
	    char *data(void);
	    char *data(void) const;
	    void print_info(void);

	private:
	    char *string_data;
	    nsl::types::u32 string_length;
	    nsl::types::u32 string_capacity;
	    static constexpr nsl::types::u32 default_string_capacity = 32;

	    static nsl::types::u32 length_ex(const char *data);
	    static void copy_ex(char *string, const char *data);
    };
}

#endif // __NSL_STRING_HPP__
