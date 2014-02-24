//import String;

/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/named_range.C
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/named_range.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

///#include <fstream>

// rapidjson didnt work in emscripten for me
///#include "../rapidjson/prettywriter.h"	// for stringify JSON
///#include "../rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output

///#include "stmt.h"
///#include "AbstractStatement.h"

package com.qscript.runtime;

public class named_range
{
	//: public AbstractStatement
	public String name;
	public java.util.ArrayList<stub_pair> stubs = new java.util.ArrayList<stub_pair>();
	//named_range(): name(""), stubs(){}
	//void GenerateCode(StatementCompiledCode & code);
	public named_range() //AbstractStatement(NAMED_RANGE, 0),
	{
		this.name = new String();
		this.stubs = new java.util.ArrayList<stub_pair>();
	}
	public named_range(DataType l_type, int l_line_number, String l_name, java.util.ArrayList<stub_pair> l_stubs) //AbstractStatement(l_type, l_line_number),
	{
		this.name = l_name;
		this.stubs = new java.util.ArrayList<stub_pair>(l_stubs);
		//cout << "named_range: constructor" << endl;
	}
	public final void set_range_data(String l_name, java.util.ArrayList<stub_pair> l_stubs)
	{
		stubs = new java.util.ArrayList<stub_pair>(l_stubs);
		name = l_name;
	}
	public void dispose()
	{
	}
	public named_range(named_range nr)
	{
		this.name = nr.name;
		this.stubs = new java.util.ArrayList<stub_pair>(nr.stubs);
	}
	//template <typename Writer>
	//void Serialize(Writer& writer) const ;
//C++ TO JAVA CONVERTER WARNING: 'const' methods are not available in Java:
//ORIGINAL LINE: void toString(stringstream & s) const
	//public final void toString(stringstream s)
	//{
	//	s << "{" << "\n";
	//	s << "\"name\"" << ":" << "\"" << name.compareTo() < 0 < < "\"" << ",";
	//	s << "\"stubs\" : ";
	//	//s << "\""<< name << "\"" << ":" << endl;
	//	s << "[" << "\n";
	//	int i = 0;
	//	for (java.util.Iterator<stub_pair> stub_pair_itr = stubs.iterator(); stub_pair_itr.hasNext(); ++stub_pair_itr, ++i)
	//	{
	//		if (i == 0)
	//		{
	//		}
	//		else
	//		{
	//			s << ",";
	//		}
	//		stub_pair_itr.toString(s);
	//	}
	//	s << "]" << "\n";
	//	s << "}" << "\n";
	//}

}
//C++ TO JAVA CONVERTER NOTE: The following #define macro was replaced in-line:
//ORIGINAL LINE: #define LOG_MAINTAINER_MESSAGE(mesg) log_maintainer_message(__LINE__, __FILE__, __PRETTY_FUNCTION__, mesg)
///#include "TempNameGenerator.h"

//namespace qscript_parser {
//	extern TempNameGenerator temp_name_generator;
//}

//C++ TO JAVA CONVERTER TODO TASK: There is no preprocessor in Java:
///#if false
//void named_range::GenerateCode(StatementCompiledCode & code)
//{
//	code.quest_defns << "vector <stub_pair> "
//		<< qscript_parser::temp_name_generator.GetNewName()
//		//<< "(" << stubs.size() << ");"
//		<< ";" << endl << endl;
//
//	for(int32_t i = 0; i<stubs.size(); ++i){
//		code.quest_defns_init_code
//			<< qscript_parser::temp_name_generator.GetCurrentName()
//			<< ".push_back( stub_pair(\"" << stubs[i].stub_text
//			<< "\", " << stubs[i].code << "));"
//			<< endl;
//	}
//
//	code.quest_defns_init_code
//		<< "\tif (write_messages_flag) {\n"
//		<< "\tfor (int i=0; i<"
//		<< qscript_parser::temp_name_generator.GetCurrentName()<< ".size(); ++i) {\n"
//		<< "\tmessages << \"<message id=\\\"\" << \"" << name  << "\" << \"_\" << i << \"\\\">\""
//		<<	" << "
//		<< qscript_parser::temp_name_generator.GetCurrentName()
//		<< "[i].stub_text << \"</message>\\n\" << endl;\n"
//		<< "\t}\n"
//		<< "}\n";
//	code.quest_defns << "named_range " << name << ";" << endl;
//	//code.quest_defns_init_code << "named_range " << name
//	//	<< "(NAMED_RANGE, " << lineNo_
//	//	<< ", " << "\"" << name << "\""
//	//	<< ", " << qscript_parser::temp_name_generator.GetCurrentName()
//	//	<< ");" << endl;
//	code.quest_defns_init_code << name << ".set_range_data(\""
//		<< name << "\", " << qscript_parser::temp_name_generator.GetCurrentName()
//		<< ");" << endl;
//	stringstream mesg;
//	mesg << "Review source of this file: check we are not allowing duplicate codes in the stubs ";
//	LOG_MAINTAINER_MESSAGE(mesg.str());
//
//	if(next_){
//		next_->GenerateCode(code);
//	}
//}
///#endif

//C++ TO JAVA CONVERTER TODO TASK: There is no preprocessor in Java:
///#if false
//// this code works in normal c++ , doesnt in emscripten
//template <typename Writer>
//void named_range::Serialize(Writer& writer) const
//{
//	using namespace rapidjson;
//	writer.String("name");
//	writer.String(name.c_str(), (SizeType) name.length());
//	writer.StartArray();
//	for (std::vector<stub_pair>::const_iterator stub_pair_itr = stubs.begin();
//			stub_pair_itr != stubs.end(); ++ stub_pair_itr
//		) {
//		stub_pair_itr->Serialize(writer);
//	}
//	writer.EndArray();
//}
///#endif
