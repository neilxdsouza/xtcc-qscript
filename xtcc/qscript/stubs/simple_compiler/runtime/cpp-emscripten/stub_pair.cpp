/*
 * =====================================================================================
 *
 *       Filename:  stub_pair.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 29 November 2013 03:10:44  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <cstdio>
#include "stub_pair.h"
#include "dom_manip_funcs.h"

string stub_pair::toString() 
{
	//using std::endl;
	//using std::stringstream;
	//stringstream s;
	//s 	<< "{"
	//	<< "\"stub_text\":" << "\"" << stub_text << "\"" << ","
	//	<< "\"stub_code\":" << code << ","
	//	<< "\"mask\":" << mask << ","
	//	<< "\"is_other\":" << is_other << ","
	//	<< "\"is_mutex\":" << is_mutex << ","
	//	<< "\"url_image\":" << "\"" << url_image << "\""
	//	//<< ","
	//	<< "}"
	//	<< endl;
	//return s.str();
	char buffer[4000]; char * ptr = buffer;
	for (int i=0; i < 4000; ++i) {
		buffer[i] = 0;
	}

	int n = sprintf (ptr, "{"); ptr += n;
	//my_log_from_cpp (ptr);
	n = sprintf (ptr, "\"stub_text\":\"%s\",", stub_text.c_str()); ptr+=n;
	n = sprintf (ptr, "\"stub_code\":%d,", code); ptr+=n;
	n = sprintf (ptr, "\"mask\": %d,", mask); ptr+=n;
	n = sprintf (ptr, "\"is_other\": %d,", is_other); ptr+=n;
	n = sprintf (ptr, "\"is_mutex\": %d,", is_mutex); ptr+=n;
	n = sprintf (ptr, "\"url_image\":\"%s\"", url_image.c_str()); ptr+=n;
	//	//<< ","
	n += sprintf (ptr, "}");
	//my_log_from_cpp (buffer);
	string r_val (buffer);
	return r_val;
}
