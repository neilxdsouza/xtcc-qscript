/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/stub_pair.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#ifndef xtcc_stub_pair_h

#define xtcc_stub_pair_h

#include <string>
using std::string;
struct	stub_pair{
	string stub_text;
	int code;
	bool mask;
	stub_pair():stub_text(""), code(-1){}
	stub_pair(string l_txt, int l_code)
		: stub_text(l_txt), code(l_code), mask(true) 
	{}
};

#endif /* xtcc_stub_pair_h */
