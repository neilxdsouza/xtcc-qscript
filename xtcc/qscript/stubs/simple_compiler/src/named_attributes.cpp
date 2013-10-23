#include <sys/types.h>
#include <iostream>
#include "named_attributes.h"
using std::cout;
using std::endl;

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

named_attribute_list::named_attribute_list(DataType dt, int32_t lline_no
					   , string l_name
					   , vector<string> l_attr)
	: AbstractStatement(dt, lline_no)
	, name(l_name), attribute(l_attr), symbolTableEntry_(0)
{ }

named_attribute_list::named_attribute_list()
	: AbstractStatement(NAMED_ATTRIBUTE_TYPE, 0)
	, name(), attribute(), symbolTableEntry_(0)
{ }

named_attribute_list::~named_attribute_list()
{ }

void named_attribute_list::GenerateCode(StatementCompiledCode & code)
{
	code.program_code << "/* "
		<< __PRETTY_FUNCTION__ << ", " << __FILE__ << ", " << __LINE__ 
		<< "*/" << endl;
	code.quest_defns << "named_attribute_list " 
		<<  name << ";\n";
	code.quest_defns_init_code
		<< name << ".name = \"" << name << "\";\n";
	for (int i=0; i<attribute.size(); ++i) {
		code.quest_defns_init_code 
			<<  name << ".attribute.push_back (string(\"" << attribute[i]
				<< "\"));\n";
	}

	code.quest_defns_init_code
		<< "named_attribute_list_vec.push_back ( &" << name << ");" << endl;

	if (program_options_ns::emscripten_flag) {
		// empty - do not generate messages code in html
		// file - to reduce the code size generated
	} else {
		code.quest_defns_init_code
			<< "\tif (write_messages_flag) {\n"
			<< "\tfor (int i=0; i<"
			<< name << ".attribute.size(); ++i) {\n"
			<< "\tmessages << \"<message id=\\\"\" << \"" << name  << "\" << \"_\" << i << \"\\\">\""
			<<	" << "
			<< name
			<< ".attribute[i] << \"</message>\\n\" << endl;\n"
			<< "\t}\n"
			<< "}\n";
	}
	if (next_) {
		next_->GenerateCode(code);
	}
}
