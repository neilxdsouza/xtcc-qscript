/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/named_range.C
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

#include <sys/types.h>
#include <iostream>
#include <sstream>
#include "named_range.h"
#include "qscript_parser.h"
#include "utils.h"

using std::cout;
using std::endl;
using std::stringstream;
using std::string;

namespace program_options_ns {
	extern bool ncurses_flag;
	extern bool static_binary_flag;
	extern bool web_server_flag;
	extern bool microhttpd_flag ;
	extern bool wt_flag ;
	extern bool compile_to_cpp_only_flag;
	extern int32_t fname_flag;
	extern bool flag_nice_map;
	extern bool stdout_flag;
	extern bool wx_flag;
	extern bool gtk_flag;
	extern bool emscripten_flag;
	extern int data_export_flag;
	extern string QSCRIPT_HOME;
};

named_range::~named_range()
{ }

void named_range::GenerateCode(StatementCompiledCode & code)
{
	code.quest_defns << "vector <stub_pair> " 
		<< qscript_parser::temp_name_generator.GetNewName()
		//<< "(" << stubs.size() << ");"
		<< ";" << endl << endl;

	for(int32_t i = 0; i<stubs.size(); ++i){
		code.quest_defns_init_code
			<< qscript_parser::temp_name_generator.GetCurrentName()
			<< ".push_back( stub_pair(\"" << stubs[i].stub_text
			<< "\", " << stubs[i].code
			<< ", false" 
			<< ", \"" << stubs[i].url_image << "\"" 
			<< "));"
			<< endl;
	}

	if (program_options_ns::emscripten_flag) {
		// empty - do not generate messages code in html
		// file - to reduce the code size generated
	} else {
		code.quest_defns_init_code
			<< "\tif (write_messages_flag) {\n"
			<< "\tfor (int i=0; i<"
			<< qscript_parser::temp_name_generator.GetCurrentName()<< ".size(); ++i) {\n"
			<< "\tmessages << \"<message id=\\\"\" << \"" << name  << "\" << \"_\" << i << \"\\\">\""
			<<	" << "
			<< qscript_parser::temp_name_generator.GetCurrentName()
			<< "[i].stub_text << \"</message>\\n\" << endl;\n"
			<< "\t}\n"
			<< "}\n";
	}
	code.quest_defns << "named_range " << name << ";" << endl;
	//code.quest_defns_init_code << "named_range " << name 
	//	<< "(NAMED_RANGE, " << lineNo_
	//	<< ", " << "\"" << name << "\""
	//	<< ", " << qscript_parser::temp_name_generator.GetCurrentName()
	//	<< ");" << endl;
	code.quest_defns_init_code << name << ".set_range_data(\""
		<< name << "\", " << qscript_parser::temp_name_generator.GetCurrentName()
		<< ");" << endl;
	stringstream mesg;
	mesg << "Review source of this file: check we are not allowing duplicate codes in the stubs ";
	LOG_MAINTAINER_MESSAGE(mesg.str());

	if(next_){
		next_->GenerateCode(code);
	}
}

named_range::named_range(named_range & nr)
	: AbstractStatement(nr.type_, nr.lineNo_),
	name (nr.name),  stubs (nr.stubs)
{
}
