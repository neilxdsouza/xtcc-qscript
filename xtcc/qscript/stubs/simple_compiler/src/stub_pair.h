/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/stub_pair.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#ifndef xtcc_stub_pair_h
#define xtcc_stub_pair_h


#include <sys/types.h>
#include <string>
#include <sstream>
#include "stub_pair_options.h"


using std::string;
struct	stub_pair
{
	string stub_text;
	int32_t code;
	bool mask;
	bool is_mutex;
	stub_pair_options::stub_media stub_media_type;
	string url_image;
	string other_specify_text;
	stub_pair()
		: stub_text(""), code(-1), mask(false), is_mutex(false),
		  url_image(), other_specify_text()
	{ }
	stub_pair(string l_txt, int32_t l_code)
		: stub_text(l_txt), code(l_code), mask(true),
		  is_mutex(false),
		  url_image(), other_specify_text()
	{ }
	stub_pair (const string & l_txt, const int32_t l_code, const stub_pair_options & p_stub_pair_options) 
		: stub_text(l_txt), code(l_code), mask (true), 
		  is_mutex (p_stub_pair_options.is_mutex),
		  stub_media_type(p_stub_pair_options.stub_media_type), url_image (p_stub_pair_options.url),
		  other_specify_text()
	{ }
	/*
	stub_pair(string l_txt, int32_t l_code, bool p_mutex)
		: stub_text(l_txt), code(l_code), mask(true),
		  is_mutex(p_mutex),
		  url_image(), other_specify_text()
	{ }
	stub_pair(string l_txt, int32_t l_code, bool p_mutex, string p_image_url)
		: stub_text(l_txt), code(l_code), mask(true),
		  is_mutex(p_mutex),
		  url_image(), other_specify_text()
	{ }
	*/

	/*

	stub_pair(const stub_pair & p1) 
	{
		stub_text = p1.stub_text;
		code = p1.code;
	}
	stub_pair & operator = (const stub_pair & rhs)
	{
		stub_text = rhs.stub_text;
		code = rhs.code;
		return *this;
	}
	*/

	void toString(std::stringstream & s) const
	{
	using std::endl;
		s 	<< "{"
			<< "\"stub_text\":" << "\"" << stub_text << "\"" << ","
			<< "\"stub_code\":" << code << ","
			<< "\"mask\":" << mask << ","
			<< "\"is_mutex\":" << is_mutex << ","
			<< "\"url_image\":" << "\"" << url_image << "\""
			//<< ","
			<< "}"
			<< endl;
	}

};

struct stub_pair_order_asc
{
public:
	bool operator() (const stub_pair & p, const stub_pair & q)
	{
		return p.code < q.code;
	}

};


struct stub_pair_order_desc
{
public:
	bool operator() (const stub_pair & p, const stub_pair & q)
	{
		return p.code > q.code;
	}
};


#endif /* xtcc_stub_pair_h */
