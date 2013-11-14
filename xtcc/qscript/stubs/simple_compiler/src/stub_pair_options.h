/*
 * =====================================================================================
 *
 *       Filename:  stub_pair_options.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 19 September 2013 07:15:45  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef stub_pair_options_h
#define stub_pair_options_h

#include <string>

struct stub_pair_options {
	bool is_mutex;
	bool is_other_specify;
	std::string url;
	enum stub_media { none, image, video, audio };
	stub_media stub_media_type;
	stub_pair_options():
		is_mutex (false), is_other_specify (false), url(), stub_media_type (none)
	{ }
	void reset () {
		is_mutex=false; is_other_specify =false; url=""; stub_media_type = none;
	}
};

#endif /*  stub_pair_options_h */
