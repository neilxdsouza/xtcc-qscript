/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/stmt_common.C
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */
#include "stmt.h"
#include "expr.h"
#include "debug_mem.h"
#include "stmt.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include "named_range.h"
#include "qscript_parser.h"



extern vector<mem_addr_tab> mem_addr;
extern int if_line_no;

//extern ofstream debug_log_file;
using std::cout;
using std::endl;
void read_data(const char * prompt);
AbstractStatement::~AbstractStatement()
{
	using qscript_parser::debug_log_file;
	std::cerr << "AbstractStatement::~AbstractStatement()\n" << std::endl;
	if (next_  ) {
		delete next_; next_=0;
	} 
	debug_log_file << "AbstractStatement::~AbstractStatement() base destructor" << endl;
}
