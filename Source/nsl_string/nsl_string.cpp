#include "nsl_string.hpp"
#include "nsl_types.hpp"
#include "nsl_io.hpp"

namespace nsl {
    string::string(const char *data){
	this->string_length = length_ex(data);	
	if(this->string_length <= 1)
	    this->string_capacity = this->default_string_capacity;
	else
	    this->string_capacity = this->string_length * 4;
	this->string_data = new char[this->string_capacity]();
	copy_ex(this->string_data, data);
    }

    string::string(){
	this->string_length = 0;
	this->string_capacity = this->default_string_capacity;
	this->string_data = new char[this->string_capacity]();
    }

    string::~string(){
	delete[] this->string_data;
    }

    string &string::operator=(const string &string_2){
	if(this->capacity() < string_2.length()){
	    this->resize(string_2.length() * 2);
	}

	copy_ex(this->string_data, string_2.string_data);
	this->string_length = string_2.string_length;

	return *this;
    }

    string &string::operator=(const char *string){
	nsl::types::u32 str_len = length_ex(string);
	if(this->capacity() < str_len){
	    this->resize(str_len * 2);
	}

	copy_ex(this->string_data, string);
	this->string_length = str_len;

	return *this;
    }

    string &string::operator=(char *string){
	return *this = static_cast<const char *>(string);
    }

    nsl::types::u32 string::length(void) const{
	return this->string_length;
    }

    nsl::types::u32 string::capacity(void) const {
	return this->string_capacity;
    }

    void string::resize(void){
	this->string_capacity *= 2;	
	char *temp_string = new char[this->string_capacity]();

	copy_ex(temp_string, this->string_data);
	delete[] this->string_data;
	this->string_data = temp_string;
    }

    void string::resize(nsl::types::u32 specific_capacity){
	if(specific_capacity <= this->string_capacity)
	    this->string_capacity *=2;
	else
	    this->string_capacity = specific_capacity;	
	char *temp_string = new char[this->string_capacity]();

	copy_ex(temp_string, this->string_data);
	delete[] this->string_data;
	this->string_data = temp_string;
    }

    char *string::data(void){
	return this->string_data;
    }

    char *string::data(void) const{
	return this->string_data;
    }

    void string::print_info(void){
	nsl::io::write_to_console(nsl::io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_OUTPUT, "String Capacity: ", this->string_capacity, "\n");
	nsl::io::write_to_console(nsl::io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_OUTPUT, "String Length: ", this->string_length, "\n");
	nsl::io::write_to_console(nsl::io::NSL_CONSOLE_TYPE::NSL_CONSOLE_TYPE_OUTPUT, "String Data: ", this->string_data, "\n");
	
	return;
    }

    nsl::types::u32 string::length_ex(const char *data){
	nsl::types::u32 count = 0;
	while(data[count] != '\0')
	    count++;

	return count;
    }

    void string::copy_ex(char *string, const char *data){
	nsl::types::u32 i = 0;
	while(data[i] != '\0'){
	    string[i] = data[i];
	    i++;
	}
	string[i] = '\0';

	return;
    }
}
