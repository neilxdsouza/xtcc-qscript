//import String;

/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/stub_pair.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

package com.qscript.runtime;
public class stub_pair
{
	public String stub_text;
	public int code;
	public boolean mask;
	public boolean is_mutex;
	public boolean is_other_specify;
	public String url_image;

	public stub_pair()
	{
		this.stub_text = "";
		this.code = -1;
		this.mask = false;
		this.is_mutex = false;
		this.is_other_specify = false;
		this.url_image = new String();
	}
	public stub_pair(String l_txt, int l_code)
	{
		this.stub_text = l_txt;
		this.code = l_code;
		this.mask = true;
		this.is_mutex = false;
		this.is_other_specify = false;
		this.url_image = new String();
	}
	/* 
	stub_pair(string l_txt, int32_t l_code, bool p_mutex)
		: stub_text(l_txt), code(l_code), mask(true),
		  is_mutex(p_mutex), url_image()
	{ }
	stub_pair(string l_txt, int32_t l_code, bool p_mutex, string p_image_url)
		: stub_text(l_txt), code(l_code), mask(true),
		  is_mutex(p_mutex), url_image (p_image_url)
	{ }
	*/
	public stub_pair(String l_txt, int l_code, boolean p_mutex, boolean p_other_specify, String p_image_url)
	{
		this.stub_text = l_txt;
		this.code = l_code;
		this.mask = true;
		this.is_mutex = p_mutex;
		this.is_other_specify = p_other_specify;
		this.url_image = p_image_url;
	}

//	stub_pair(String l_txt, int l_code, stub_pair_options current_stub_pair_options);Tangible Method Implementation Not Foundstub_pair-stub_pair


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

//C++ TO JAVA CONVERTER WARNING: 'const' methods are not available in Java:
//ORIGINAL LINE: void toString(std::stringstream & s) const
	//public final void toString(std.stringstream s)
	//{
	//	s << "{" << "\"stub_text\":" << "\"" << stub_text.compareTo() < 0 < < "\"" << "," << "\"stub_code\":" << code << "," << "\"mask\":" << mask << "," << "\"is_mutex\":" << is_mutex << "," << "\"url_image\":" << "\"" << url_image.compareTo() < 0 < < "\"" << "}" << "\n";
	//		//<< ","
	//}

}
