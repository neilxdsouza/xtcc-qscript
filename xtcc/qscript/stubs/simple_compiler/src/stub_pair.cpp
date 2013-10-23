/*
 * =====================================================================================
 *
 *       Filename:  stub_pair.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Tuesday 01 October 2013 10:57:27  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>
#include "stub_pair.h"


stub_pair::stub_pair(string l_txt, int32_t l_code, const stub_pair_options & current_stub_pair_options)
		: stub_text(l_txt), code(l_code), mask(true),
		  is_mutex (current_stub_pair_options.is_mutex),
		  is_other_specify (current_stub_pair_options.is_other_specify),
		  url_image (current_stub_pair_options.url)
{ 
	//using std::cout;
	//using std::endl;
	//cout << "url_image: " << url_image << endl;
}
