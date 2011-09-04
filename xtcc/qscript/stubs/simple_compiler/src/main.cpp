#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include "symtab.h"
#include "stmt.h"
#include "expr.h"
#include "question.h"
#include "named_attributes.h"
#include "named_range.h"
#include "qscript_parser.h"
#include "scope.h"
#include "qscript_debug.h"
#include "LatexDoc.h"

#if _WIN32
#include <windows.h>
#include <tchar.h>
#endif /* _WIN32 */


#include <fstream>
using  std::cerr;
using  std::endl;
using  std::cout;

	//extern Scope* active_scope;
	//extern vector <Scope*> active_scope_list;
	extern void yyrestart(FILE *input_file);
	extern int32_t yyparse();
	extern void GenerateCode();
	//extern vector </*Statement::*/FunctionInformation*> func_info_table;
	using qscript_parser::func_info_table;

	void clean_lex();

	string check_for_registry_key();
#if _WIN32
string QueryKeyData(HKEY hKey);
#endif /* _WIN32 */
	void InitStatement();
	bool do_sanity_checks(string qscript_install_dir);

namespace program_options_ns {
	bool ncurses_flag = false;
	bool static_binary_flag = false;
	bool web_server_flag = false;
	int32_t fname_flag = 0;
	bool  no_question_save_restore_optimization;
	bool flag_nice_map;
	bool compile_to_cpp_only_flag = false;
	bool latex_flag = false;
}

int32_t main(int32_t argc, char* argv[])
{
	InitStatement();
	using qscript_parser::active_scope_list;
	using qscript_parser::active_scope;
	using qscript_parser::no_errors;
	int32_t opterr = 1, c;
	using qscript_parser::fname;
	bool exit_flag = false;

	while( (c = getopt(argc, argv, "molcsnf:")) != -1 ){
		char ch = optopt;
		switch(c){
		case 'c':
			program_options_ns::compile_to_cpp_only_flag = true;
			break;
		case 'n':
			program_options_ns::ncurses_flag = true;
			break;
		case 's':
			program_options_ns::static_binary_flag = true;
			break;
		case 'f':
			fname = optarg;
			program_options_ns::fname_flag = 1;
			break;
		case 'l':
			program_options_ns::latex_flag = true;
			break;
		case 'o':
			program_options_ns::no_question_save_restore_optimization = true;
			break;
		case 'm':
			program_options_ns::flag_nice_map = true;
			break;
		case '?':
			if (optopt == 'f' )
				cerr << " option -'" << optopt << "' requires an argument" << endl;
			else if (isprint(optopt)){
				cerr << " unknown option : '-" << optopt << "'" << endl;
			} else
				cerr << " unknown character " << optopt << endl;
			exit(1);
			break;
		default:
			cerr << "Usage: "
				<< argv[0] << " -f <input-file>\n" <<   endl;
			exit(0);
		}
		if (program_options_ns::fname_flag == 1){
			break;
		}
	}
	string  qscript_install_dir ;
	// uncomment this and comment the one below to 
	// test the registry key code
	//char * QSCRIPT_HOME = 0;
	char * QSCRIPT_HOME = getenv("QSCRIPT_HOME");

#if 	_WIN32
	if (!QSCRIPT_HOME) {
		qscript_install_dir = check_for_registry_key();
		if (qscript_install_dir != "") {
			cout << "got qscript_install_dir from registry key : SOFTWARE\\QScript" << endl;
			exit_flag = false;
			// this is going to result in a small memory leak
			QSCRIPT_HOME = strdup(qscript_install_dir.c_str());
			cout << "QSCRIPT_HOME is : " << QSCRIPT_HOME << endl;
		} else {
			cout << "For Windows you can also set qscript_install_dir using the registry key : SOFTWARE\\QScript" << endl;
		}
	}
#endif /* _WIN32 */

	if (!QSCRIPT_HOME) {
		cout << "Please set environment variable QSCRIPT_HOME to the top-level directory that qscript is installed in" << endl
			<< "If qscript was installed in /home/unixuser/qscript/, in UNIX - bash " << endl
			<< "you would do this as (assume $ as shell prompt):" << endl
			<< "$export QSCRIPT_HOME=/home/unix_user/qscript" << endl;
		exit_flag = true;
	}

	if (!qscript_parser::ReadQScriptConfig()) {
		exit_flag = true;
	}
	if (exit_flag){
		exit(1);
	}
	do_sanity_checks(QSCRIPT_HOME);
	//cout << "reached here" << endl;

	if (!program_options_ns::fname_flag){
		cout << "Usage: "
			<< argv[0] << " -f <input-file> "  << endl;
		cout << "Options: " << endl;
		cout << " -n            - creates an ncurses executable " << endl;
		cout << " -s            - creates an static executable - for windows only " << endl;
		cout << " -c            - compile to c++ only - dont invoke c++ compiler" << endl;
		cout << " -l            - run latex on generated latex file" << endl;
		cout << " -o            - no question save/restore optimization" << endl;
		cout << " -m            - make a nice map" << endl;
		exit(0);
	}
	active_scope = new Scope();
	active_scope_list.push_back(active_scope);

	string printf_name = "printf";
	/*Statement:: */FunctionParameter* v_list = 0;
	DataType myreturn_type = INT8_TYPE;
	/*Statement::*/FunctionInformation* fi = new /*Statement::*/FunctionInformation(printf_name, v_list, myreturn_type);
	func_info_table.push_back(fi);


	FILE * yyin = fopen(fname.c_str(), "rb");
	if (!yyin){
		cerr << " Unable to open: " << fname << " for read ... exiting" << endl;
		exit(1);
	}
	yyrestart(yyin);
	qscript_parser::lex_location.SetFileName(qscript_parser::fname);
	qscript_parser::lex_location.ResetLine();
	qscript_parser::lex_location.ResetColumn();
	if (!yyparse() && !no_errors) {
		cout << "Input parsed successfully: There could still be errors detected in code generation from if-else statements." << endl;
		//data_entry_loop();
		qscript_parser::GenerateCode(fname, program_options_ns::ncurses_flag);
		if (no_errors) {
			cout << "There were "
				<< no_errors
				<< " errors detected in the code generation phase"
				<< endl;
			goto lab_maintainer_messages;
		}
#ifndef _WIN32
		{
			std::stringstream bcpp_command;
			string output_file_name = qscript_parser::ExtractBaseFileName(qscript_parser::fname);
			bcpp_command << "bcpp " << output_file_name << ".C" << " > " << output_file_name << "_bcpp.C";
			if (int32_t ret_val = system(bcpp_command.str().c_str())) {
				cout << "error running bcpp - maybe its not installed or not present in the PATH variable" << endl;
			} else {
				// cout << "successfully ran bcpp to generate indented source" << endl;
			}

			if (program_options_ns::latex_flag) {
				std::stringstream latex_fname;
				{
					// Generate LatexDoc
					latex_fname << output_file_name << ".latex";
					LatexDocument doc(latex_fname.str());
					doc.visit(qscript_parser::tree_root);
					//doc.latex_file << doc.finish_latex();
					//std::fstream latex_file(latex_fname.str().c_str(), exc_flags);
					//std::ofstream latex_file; latex_file.exceptions(exc_flags); latex_file.open(latex_fname.str().c_str());
					//if (latex_file)
					//	latex_file << doc;
				}
				{
					using std::cout;
					using std::endl;
					using std::stringstream;
					stringstream latex_command;
					latex_command << "latex " << latex_fname.str();
					if (int32_t ret_val = system(latex_command.str().c_str())) {
						cout << "error running latex - maybe its not installed or not present in the PATH variable. " << endl
							<< "You can install the TeX/LaTeX system and have qscript automatically generate " << endl
							<< "beautiful pdf questionnaires. Read more about TeX/LaTeX at http://www.tug.org\n";
					} else {
						stringstream dvipdf_command;
						dvipdf_command << "dvipdf " << output_file_name << ".dvi";
						if (int32_t ret_val = system(dvipdf_command.str().c_str())) {
							cout << "error running dvipdf - maybe it is not installed or present in the PATH variable. " << endl
								<< " please check the latest release of ghostscript " << endl;
						} else {
							// successfully ran dvipdf
						}
					}
				}
			}
		}
#endif /* _WIN32 */

		cout << "code generated " << endl;
		if (program_options_ns::compile_to_cpp_only_flag) {
		} else {
			if (program_options_ns::static_binary_flag)
				qscript_parser::CompileGeneratedCodeStatic(fname);
			else
				qscript_parser::CompileGeneratedCode(fname);
		}
	} else {
		cerr << "There were : " << no_errors << " errors in parse" << endl;
	}
lab_maintainer_messages:
	{
		if (qscript_debug::MAINTAINER_MESSAGES) {
			using qscript_parser::maintainer_messages;
			cout << "maintainer_messages: " << endl;
			for(map<pair<int32_t, int32_t>, string>::iterator it=maintainer_messages.begin();
					it!=maintainer_messages.end(); ++it) {
				cout << it->second << endl;
			}
		}
	}

////////////////////////////////
#if 0
	try
	{
		std::ofstream conf;
		conf.exceptions(std::ios::failbit | std::ios::badbit);
		conf.open("a.cfg");

		std::vector<AbstractQuestion*> &qv = qscript_parser::question_list;
		conf << qv.size() << '\n';
		for(int32_t i = 0; i < qv.size(); ++i)
		{
			conf << qv[i]->questionName_ << ' ';
			switch(qv[i]->dt)
			{
				case INT8_TYPE  : conf << "int8"  ; break;
				case INT16_TYPE : conf << "int16" ; break;
				case INT32_TYPE : conf << "int32" ; break;
				case FLOAT_TYPE : conf << "float" ; break;
				case DOUBLE_TYPE: conf << "double"; break;
				default: conf << "Unrecognised type";
			}
			conf << ' ';
			NamedStubQuestion *nsq = dynamic_cast<NamedStubQuestion*>(qv[i]); if (nsq) conf << nsq->nr_ptr->name;
			conf << '\n';
		}

		std::vector<named_range*> &nsl = qscript_parser::named_stubs_list;
		for(int32_t i = 0; i < nsl.size(); ++i)
		{
			conf << nsl[i]->name;
			std::vector<stub_pair> &sv = nsl[i]->stubs;
			for(int32_t i = 0; i < sv.size(); ++i) conf << ' ' << sv[i].code << " \"" << sv[i].stub_text << '\"';
			conf << '\n';
		}
	}
	catch(...){ std::cout << "error while generating configuration file\n"; }
#endif /* 0 */
////////////////////////////////
	if (qscript_parser::tree_root) {
		//cerr << "deleting qscript_parser::tree_root" << endl;
		delete qscript_parser::tree_root;
		if (active_scope_list[0]) {
			delete active_scope_list[0]; active_scope_list[0] = 0;
		}
		delete fi; fi = 0;
		//yy_delete_buffer(YY_CURRENT_BUFFER);
		clean_lex();
		for(int i=0; i<qscript_parser::
			    delete_manually_in_cleanup.size(); ++i){
			delete qscript_parser::delete_manually_in_cleanup[i];
			qscript_parser::delete_manually_in_cleanup[i]=0;
		}
	}


	return no_errors;
}

#if _WIN32
string check_for_registry_key()
{
	HKEY hTestKey;
	string qscript_install_dir ;


	//
	//HKEY_CURRENT_USER
	//HKEY_LOCAL_MACHINE
	if (RegOpenKeyEx( HKEY_CURRENT_USER,
		TEXT("SOFTWARE\\QScript"),
		0,
		KEY_READ,
		&hTestKey) == ERROR_SUCCESS
		)
	{
		qscript_install_dir = QueryKeyData(hTestKey);
	}

	RegCloseKey(hTestKey);
	return qscript_install_dir;
}


#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 32767

string QueryKeyData(HKEY hKey)
{
	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
	DWORD    cbName;                   // size of name string
	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name
	//DWORD    cchClassName = MAX_PATH;  // size of class string
	DWORD    cchClassName = MAX_PATH;  // size of class string
	DWORD    cSubKeys=0;               // number of subkeys
	DWORD    cbMaxSubKey =0 ;              // longest subkey size
	DWORD    cchMaxClass = 0;              // longest class string
	DWORD    cValues = 0;              // number of values for key
	DWORD    cchMaxValue =0;          // longest value name
	DWORD    cbMaxValueData = 0;       // longest value data
	DWORD    cbSecurityDescriptor = 0; // size of security descriptor
	FILETIME ftLastWriteTime;      // last write time


	TCHAR    achKeyValue[MAX_VALUE_NAME];   // buffer for subkey name
	BYTE    achKeyValueData[MAX_VALUE_NAME];   // buffer for subkey name
	DWORD  pcbData = 0;

	DWORD i, retCode;

	TCHAR  achValue[MAX_VALUE_NAME];
	DWORD cchValue = MAX_VALUE_NAME;

	// Get the class name and the value count.
	retCode = RegQueryInfoKey(
			hKey,                    // key handle
			achClass,                // buffer for class name
			&cchClassName,           // size of class string
			NULL,                    // reserved
			&cSubKeys,               // number of subkeys
			&cbMaxSubKey,            // longest subkey size
			&cchMaxClass,            // longest class string
			&cValues,                // number of values for this key
			&cchMaxValue,            // longest value name
			&cbMaxValueData,         // longest value data
			&cbSecurityDescriptor,   // security descriptor
			&ftLastWriteTime);       // last write time

    // Enumerate the subkeys, until RegEnumKeyEx fails.

	if (cSubKeys) {
		printf( "\nNumber of subkeys: %d\n", cSubKeys);
		for (i=0; i<cSubKeys; i++) {
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, i,
			     achKey,
			     &cbName,
			     NULL,
			     NULL,
			     NULL,
			     &ftLastWriteTime);
			if (retCode == ERROR_SUCCESS)
			{
			_tprintf(TEXT("(%d) %s\n"), i+1, achKey);
			}
		}
	}

	/*
	if (cValues)
	{
	printf( "\nNumber of values: %d\n", cValues);

	for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++)
	{
	    cchValue = MAX_VALUE_NAME;
	    achValue[0] = '\0';
	    retCode = RegEnumValue(hKey, i,
		achValue,
		&cchValue,
		NULL,
		NULL,
		NULL,
		NULL);

	    if (retCode == ERROR_SUCCESS )
	    {
		_tprintf(TEXT("step 1, retCode: %d: (%d) %s\n"), retCode, i+1, achValue);
	    }
	}
	}
	*/

	string return_value;
	if (cSubKeys) {
		i=0;
		//short int my_cchValue=32767;
		int my_cchValue=32767;
		DWORD pcbKeyValueData = MAX_VALUE_NAME;
		cchValue = MAX_VALUE_NAME;
		achValue[0] = '\0';
		retCode = RegEnumValue(hKey, i,
				achValue,
				//&my_cchValue,
				&cchValue,
				NULL /* reserved */,
				NULL /* type: can be null if type not required */,
				achKeyValueData,
				&pcbKeyValueData
				);

		if (retCode == ERROR_SUCCESS ) {
			//_tprintf(TEXT("step 2, retCode: %d: (%d) %s\n"), retCode, i+1, achValue);
			//_tprintf(TEXT("step 2, retCode: %d: achKeyValueData:  %s\n"), retCode,  achKeyValueData);
			//return_value = string(static_cast<const char *>(achKeyValueData));
			char c = -1;
			for (int i=0; i<MAX_VALUE_NAME && c; ++i) {
				char c = achKeyValueData[i];
				return_value.push_back(c);
			}
		} else {
			//_tprintf(TEXT("step 2, !ERROR_SUCCESS retCode: (%d) \n"),  retCode);
		}
	}

	/*

	i = 0;
	retCode = RegEnumValue(hKey, i,
                achValue,
                &my_cchValue,
                NULL,
                NULL,
                NULL,
                NULL);
            if (retCode == ERROR_SUCCESS )
            {
                _tprintf(TEXT("(%d) %s\n"), i+1, achValue);
            } else {
                _tprintf(TEXT("retCode: (%d) \n"),  retCode);
	    }
	for (i=0; i<MAX_VALUE_NAME; ++i) {
		achKeyValue[i] = 0;
	}
	*/
	// retCode = RegGetValueA (hKey, "SOFTWARE\\QScript", "Install_Dir",
	// 			0x00000002  /*RRF_RT_REG_SZ */, NULL, achKeyValue, &pcbData);
        // if (retCode == ERROR_SUCCESS )
        // {
	// 	_tprintf(TEXT("achKeyValue: %s\n"), achKeyValue);
	// } else {
	// 	_tprintf(TEXT("retCode: (%d) \n"),  retCode);
	// }
	return return_value;
}

#endif /* _WIN32 */

bool do_sanity_checks(string qscript_install_dir)
{
	return false;
}
