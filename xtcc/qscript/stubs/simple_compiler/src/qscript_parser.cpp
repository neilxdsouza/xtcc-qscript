#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>
#include <utility>
#include "compiled_code.h"
#include "qscript_parser.h"
#include "config_parser.h"
#include "qscript_debug.h"
#include "TempNameGenerator.h"
#include "utils.h"


namespace program_options_ns {
	extern bool ncurses_flag;
	extern bool static_binary_flag;
	extern bool web_server_flag;
	extern bool microhttpd_flag ;
	extern bool wt_flag ;
	extern bool compile_to_cpp_only_flag;
	extern bool latex_flag ;
	extern int32_t fname_flag;
	extern bool flag_nice_map;
	extern int stdout_flag;
	extern int wx_flag;
	extern int gtk_flag;
	extern int emscripten_flag;
	extern int browser_only_flag ;
	extern int data_export_flag;
	extern string QSCRIPT_HOME;
}

extern int32_t qscript_confparse();
extern void qscript_confrestart(FILE *input_file);
namespace qscript_parser
{
	using std::cerr;
	using std::cout;
	using std::endl;
	using std::stringstream;
	vector<AbstractExpression*> for_loop_max_counter_stack;
	vector<CompoundStatement*> compound_body_stack;
	Scope* active_scope;
	vector <Scope*> active_scope_list;
	int32_t nest_lev = 0;
	int32_t flagIsAFunctionBody_ = -1;
	int32_t flagIsAForBody_ = 0;
	int32_t page_nest_lev  = 0;
	bool flag_next_stmt_start_of_block = false;

	std::string globalActivePageName_;
	int32_t globalActivePageSize_;
	bool flag_first_question_in_page = false;

	bool flag_dynamic_base_text = false;
	AbstractQuestion * dynamic_base_text_question = 0;
	bool flag_next_question_start_of_block = false;

	vector<bool> blk_start_flag;
	vector<bool> blk_question_start_flag;
	vector <AbstractStatement*> blk_heads;
	//const int32_t DEFAULT_STACK_SIZE=20;
	vector<CompoundStatement*> stack_cmpd_stmt;
	vector<string> stack_of_active_push_vars;
	map<string, vector<string> > map_of_active_vars_for_questions;
	// map<std::pair<int, int>, string > maintainer_messages;

	AbstractExpression * recurse_for_index(int32_t stack_index);
	vector<AbstractStatement*> delete_manually_in_cleanup;


	ofstream debug_log_file("qscript_debug.log", std::ios_base::out|std::ios_base::trunc);
	using std::string;
	//void print_err(compiler_err_category cmp_err,
	//	string err_msg, int32_t line_no,
	//	int32_t compiler_line_no, string compiler_file_name);
	// int32_t line_no;
	extern noun_list_type noun_list[];

	QuestionType q_type;
#include "const_defs.h"
#include "xtcc_set.h"
	int32_t no_mpn = 0;
	XtccSet xs;
	XtccSet mutex_range_set;
	bool has_mutex_range = false;
	int32_t yylex();
	void yyerror(const char * s);
	//int32_t no_errors;

	struct AbstractStatement* tree_root = 0;
	vector <AbstractQuestion*> question_list;
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);
	const bool XTCC_DEBUG_MEM_USAGE = true;
	bool skip_func_type_check(const char * fname);
	vector<mem_addr_tab>  mem_addr;
	vector <FunctionInformation*> func_info_table;
	int32_t check_parameters(struct AbstractExpression* e, struct VariableList* v);

        vector <string> attribute_list;
	vector <named_range*> named_stubs_list;
	vector <named_attribute_list> named_attributes_list;
        vector <stub_pair> stub_list;
	int32_t if_line_no = -1;

	int32_t yywrap();

	string project_name;
	bool show_lex_error_context = true;
	string fname;
	struct LexLocation lex_location;
	//TempNameGenerator temp_set_name_generator("qscript_temp_xtcc_set_");
	//TempNameGenerator temp_name_generator("qscript_temp_");

}

namespace qscript_parser{

using std::string;

#include <sstream>

void print_header(FILE* script, bool ncurses_flag);
void print_array_question_class(FILE* script);
//void print_flat_ascii_data_class(FILE *script);
//void print_qtm_data_class(FILE *script);
void print_close(FILE* script, ostringstream & program_code, bool  ncurses_flag);
void print_navigation_support_functions(FILE * script);
void print_reset_questionnaire(FILE * script);
void print_read_a_serial_no (FILE * script);
void PrintDisplayActiveQuestions(FILE *script);
void PrintGetUserResponse(FILE *script);
void PrintSetupNCurses(FILE * script);
void PrintSignalHandler(FILE * script, bool ncurses_flag);
void PrintSetupSignalHandler(FILE * script);

void PrintPrintMapHeader(FILE * script);
void PrintDefineSomePDCursesKeys(FILE * script);
void PrintPDCursesKeysHeader(FILE * script);
void PrintProcessOptions(FILE * script);
void PrintNCursesMain(FILE * script, bool ncurses_flag);
void PrintStdoutMain (FILE * script);
void PrintWxSupport_1 (FILE * script);

void PrintMicrohttpdMain (FILE * script, bool ncurses_flag);
void PrintComputeFlatFileMap(StatementCompiledCode & compute_flat_map_code);
void print_eval_questionnaire (FILE* script, ostringstream & program_code, bool ncurses_flag);
void print_write_qtm_data_to_disk(FILE *script);
void print_write_ascii_data_to_disk(FILE *script);
void print_write_spss_file_for_ascii_data_to_disk(/*FILE *script*/StatementCompiledCode & compute_flat_map_code);
void print_do_freq_counts(FILE *script);
void print_write_xtcc_data_to_disk(FILE *script);
const char * file_exists_check_code();
const char * write_data_to_disk_code();
void print_summary_axis(FILE * script);
void print_prompt_user_for_serial_no(FILE * script);
void print_ncurses_include_files (FILE * script);
void print_ncurses_func_prototypes (FILE * script);
void print_microhttpd_web_support (FILE * script);
void print_web_func_prototypes (FILE * script);
void print_Wt_support_code(FILE * script);
void print_microhttpd_include_files (FILE * script);
void print_web_support_structs (FILE * script);
void print_microhttpd_web_support_structs (FILE * script);

void print_new_logic_support_functions(FILE * script);
void print_new_logic_support_functions_2(FILE * script);
void print_emscripten_support_functions(FILE * script);

void print_question_messages(FILE * script);

string ExtractBaseFileName(const string & fname)
{
	string output_file_name = fname;
	int32_t dot_pos = fname.find_last_of('.');
	if(!(dot_pos == string::npos)){
		output_file_name = fname.substr(0, dot_pos);
	}
	return output_file_name;
}

void GenerateCode(const string & src_file_name, bool ncurses_flag)
{
	if(qscript_debug::DEBUG_qscript_parser)
		cerr << "ENTER qscript_parser::GenerateCode" << endl;
	string output_file_name = ExtractBaseFileName(src_file_name);
	output_file_name += ".C";
	//string script_name("test_script.C");
	FILE * script = fopen(output_file_name.c_str(), "w");
	if(!script){
		cerr << "unable to open output file : " << output_file_name << endl;
		exit(1);
	}
	//ostringstream quest_defns, program_code;

	print_header(script, ncurses_flag);
	tree_root->GenerateConsolidatedForLoopIndexes();
	StatementCompiledCode compute_flat_map_code;
	if (!program_options_ns::data_export_flag) {
		compute_flat_map_code.program_code << "\n#if 0" << endl;
	}
	PrintComputeFlatFileMap(compute_flat_map_code);
	if (!program_options_ns::data_export_flag) {
		compute_flat_map_code.program_code << "#endif /* 0 */" << endl;
	}
	StatementCompiledCode code;
	tree_root->GenerateCode(code);

	fprintf(script, "struct TheQuestionnaire: public AbstractQuestionnaire\n{\n");
#if 0
	fprintf(script, "AbstractQuestion * last_question_answered;\n");
	fprintf(script, "AbstractQuestion * last_question_visited;\n");
	fprintf(script, "vector <AbstractQuestion*> question_list;\n");
	fprintf(script, "fstream messages;\n");
	fprintf(script, "bool back_jump;\n");
	fprintf(script, "string jno;\n" );
	fprintf(script, "int ser_no;\n");
	fprintf(script, "bool stopAtNextQuestion;\n");
	fprintf(script, "int32_t questions_start_from_here_index;\n" );
	fprintf(script, "int ser_no_pos;\n");
	fprintf (script, " 	string jumpToQuestion;\n");
	fprintf (script, " 	int32_t jumpToIndex;\n");
	fprintf(script, "vector <BaseText> base_text_vec;\n");
#endif /*  0 */
	fprintf(script, "%s\n", code.quest_defns.str().c_str());
	//fprintf(script, "TheQuestionnaire() \n");

	fprintf (script, "TheQuestionnaire (string p_jno): AbstractQuestionnaire(p_jno)\n");
	// nxd 10-may-2013
#if 1
	fprintf(script, " /* length(): %ld */", code.quest_defns_constructor.str().length() );
	if (code.quest_defns_constructor.str().length() == 0) {
		//fprintf(script, ":");
	} else {
		fprintf(script, "%s\n", code.quest_defns_constructor.str().c_str());
		//fprintf(script, ",");
	}
	//fprintf(script, " last_question_answered(0), last_question_visited(0), back_jump(false), stopAtNextQuestion(false)\n");
	//fprintf(script, ", jno (\"%s\"), ser_no(0)\n", project_name.c_str());
#endif /*  0 */

	fprintf(script, "{\n");
	//fprintf(script, "last_question_answered = 0;\n");
	if (program_options_ns::emscripten_flag) {
		// empty - do not generate messages code in html
		// file - to reduce the code size generated
	} else {
		fprintf(script, "if (write_messages_flag) {\n");
		fprintf(script, "\tmessages.open (\"%s.xml\", ios_base::out|ios_base::trunc);\n", project_name.c_str());
		fprintf(script, "\tif(!messages) { cerr << \"unable to open file for output of messages... exiting\\n\"; exit(1); }\n");
		fprintf(script, "\tmessages << \"<?xml version=\\\"1.0\\\" encoding=\\\"UTF8\\\"?>\\n\";\n");
		fprintf(script, "\tmessages << \"<messages>\\n\";");
		fprintf(script, "\tmessages << \"  <message id=\\\"thank_you\\\">The Survey is now complete. Thank You for your time.</message>\\n\";");
		fprintf(script, "}\n");
	}
	fprintf(script, "%s\n", code.quest_defns_init_code.str().c_str());
	fprintf(script, "\tquestions_start_from_here_index = question_list.size();\n\tint our_question_index_no = 100000;\n");

	fprintf(script, "%s\n", code.array_quest_init_area.str().c_str());
	if (program_options_ns::data_export_flag) {
		fprintf(script, "\tcompute_flat_file_map_and_init();\n");
	} else {
		fprintf(script, "\t//compute_flat_file_map_and_init();\n");
	}
	if (program_options_ns::emscripten_flag) {
		// empty - do not generate messages code in html
		// file - to reduce the code size generated
	} else {
		fprintf(script, "\tif (write_messages_flag) {\n");
		fprintf(script, "\tmessages << \"</messages>\\n\";\n");
		fprintf(script, "\tmessages.flush() ;\n");
		fprintf(script, "\t}\n");
	}
	fprintf(script, "}\n");
#if 0
	print_question_messages(script);
	print_summary_axis(script);
	// 5-apr-2011 , 0:12 (am)
	// continue from here - put the compute_flat_map_code into
	// a write data function - commiting this
	// - generated code wont compile
#endif /* 0 */
	fprintf(script, "%s\n", compute_flat_map_code.program_code.str().c_str());
	print_eval_questionnaire(script, code.program_code, ncurses_flag);
#if 0
	fprintf(script, "%s\n", write_data_to_disk_code());
	print_navigation_support_functions(script);
	print_reset_questionnaire(script);
	print_read_a_serial_no (script);
	PrintDisplayActiveQuestions(script);
	PrintGetUserResponse(script);
	print_write_qtm_data_to_disk(script);
	print_write_ascii_data_to_disk(script);
	//print_prompt_user_for_serial_no(script);
	print_write_xtcc_data_to_disk(script);
	print_do_freq_counts(script);
	//print_close(script, code.program_code, ncurses_flag);
	//fflush(script);
#endif /*  0 */
	fprintf(script, "};\n");

	if (program_options_ns::ncurses_flag)
		PrintNCursesMain(script, ncurses_flag);
	if (program_options_ns::microhttpd_flag) {
		print_microhttpd_web_support_structs (script);
		print_web_support_structs (script);
		print_web_func_prototypes (script);
		PrintMicrohttpdMain(script, ncurses_flag);
		print_microhttpd_web_support(script);
	}
	if (program_options_ns::wt_flag) {
		//print_web_support_structs (script);
		print_Wt_support_code(script);
	}
	if (program_options_ns::stdout_flag) {
		//PrintStdoutMain(script);
		PrintWxSupport_1(script);
	}
	if (program_options_ns::wx_flag || program_options_ns::wt_flag) {
		PrintWxSupport_1(script);
	}
	print_close(script, code.program_code, ncurses_flag);
	fflush(script);
	if(qscript_debug::DEBUG_qscript_parser)
		cerr << "EXIT qscript_parser::GenerateCode" << endl;
}

void print_header(FILE* script, bool ncurses_flag)
{
#if 0
	if (program_options_ns::wt_flag) {
		fprintf (script, "#include <Wt/WApplication>\n");
		fprintf (script, "#include <Wt/WServer>\n");
		fprintf (script, "#include <Wt/WBreak>\n");
		fprintf (script, "#include <Wt/WContainerWidget>\n");
		fprintf (script, "#include <Wt/WLineEdit>\n");
		fprintf (script, "#include <Wt/WPushButton>\n");
		fprintf (script, "#include <Wt/WText>\n");
		fprintf (script, "#include <Wt/WRadioButton>\n");
		fprintf (script, "#include <Wt/WCheckBox>\n");
		fprintf (script, "#include <Wt/WBreak>\n");
		fprintf (script, "#include <Wt/WButtonGroup>\n");
		fprintf (script, "#include <Wt/WGroupBox>\n");
		fprintf (script, "#include <Wt/WString>\n");
		fprintf (script, "#include <Wt/WStringUtil>\n");
	}
#endif /* 0 */
	fprintf(script, "#include <iostream>\n");
	fprintf(script, "#include <vector>\n");
	fprintf(script, "#include <string>\n");
	fprintf(script, "#include <sstream>\n");
	fprintf(script, "#include <fstream>\n");
	fprintf(script, "#include <map>\n");
	fprintf(script, "#include <cstdlib>\n");
	fprintf(script, "#include <cstring>\n");
	fprintf(script, "#include <errno.h>\n");
	fprintf(script, "#include <unistd.h>\n");
	if (program_options_ns::ncurses_flag) {
		print_ncurses_include_files(script);
	}

	if (program_options_ns::microhttpd_flag) {
		print_microhttpd_include_files(script);
	}
	fprintf(script, "#include <signal.h>\n");
	fprintf(script, "#include <dirent.h>\n");
	fprintf(script, "#include <cctype>\n");
	fprintf(script, "#include <unistd.h>\n");
	//fprintf(script, "#include \"stmt.h\"\n");
	fprintf(script, "#include \"AbstractQuestionnaire.h\"\n");
	if (program_options_ns::ncurses_flag) {
		fprintf(script, "#include \"question_ncurses_runtime.h\"\n");
	}
	if (program_options_ns::stdout_flag) {
		fprintf (script, "#include \"question_stdout_runtime.h\"\n");
	}
	if (program_options_ns::gtk_flag||program_options_ns::wx_flag || program_options_ns::wt_flag) {
		fprintf (script, "#include \"question_gtk2_runtime.h\"\n");
	}
	if (program_options_ns::emscripten_flag) {
		fprintf (script, "#include \"question_stdout_runtime.h\"\n");
	}
	fprintf(script, "#include \"stub_pair.h\"\n");
	fprintf(script, "//#include \"AbstractStatement.h\"\n");
	fprintf(script, "#include \"named_range.h\"\n");
	fprintf(script, "#include \"xtcc_set.h\"\n");
	fprintf(script, "#include \"datatype.h\"\n");
	fprintf(script, "#include \"qscript_lib.h\"\n");
	fprintf(script, "#include \"question_disk_data.h\"\n");
	fprintf(script, "#include \"question.h\"\n");
	fprintf(script, "#include \"user_navigation.h\"\n");
	if (program_options_ns::data_export_flag) {
		fprintf(script, "#include \"qtm_data_file.h\"\n");
		fprintf(script, "#include \"qtm_datafile_conf_parser.h\"\n");
	} else {
		fprintf(script, "//#include \"qtm_data_file.h\"\n");
		fprintf(script, "//#include \"qtm_datafile_conf_parser.h\"\n");
	}
	fprintf(script, "#include \"ArrayQuestion.h\"\n");
	if (program_options_ns::data_export_flag) {
		fprintf(script, "#include \"AsciiFlatFileQuestionDiskMap.h\"\n");
		fprintf(script, "#include \"XtccDataFile.h\"\n");
	} else {
		fprintf(script, "//#include \"AsciiFlatFileQuestionDiskMap.h\"\n");
		fprintf(script, "//#include \"XtccDataFile.h\"\n");
	}
	fprintf(script, "#include \"base_text.h\"\n");
	fprintf(script, "#include \"named_attributes.h\"\n");

	{
		//stringstream mesg;
		//mesg << "do we need to #include \"TempNameGenerator.h\" in generated code? I have commented it out";
		// LOG_MAINTAINER_MESSAGE(mesg.str());
		// no we dont
		//fprintf(script, "#include \"TempNameGenerator.h\"\n");
	}
	fprintf(script, "#include \"QuestionAttributes.h\"\n");
	fprintf(script, "#include \"UserResponse.h\"\n");
	cerr << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
		<< ", ensure we re-create this functionality in the runtime file"
		<< ", which has been commented out below"
		<< endl;
	if (program_options_ns::wt_flag) {
		fprintf(script, "#include \"question_wt_runtime.h\"\n");
	}
	if (program_options_ns::emscripten_flag) {
		fprintf(script, "#include \"dom_manip_funcs.h\"\n");
	}
	fprintf (script, "#include \"EvalReturnValue.h\"\n");

	// Thanks to the new runtime, this is no longer necessary
	//if(config_file_parser::PLATFORM == "LINUX"){
	//	FILE * simple_pd_curses_keys_h = fopen("a_few_pd_curses_keys.h", "wb");
	//	if(!simple_pd_curses_keys_h){
	//		fprintf(stderr, "unable to open file a_few_pd_curses_keys.h for writing ...\
	//				exiting \n");
	//		exit(1);
	//	}
	//	PrintPDCursesKeysHeader(simple_pd_curses_keys_h);
	//	fclose(simple_pd_curses_keys_h);
	//	fprintf(script, "#include \"a_few_pd_curses_keys.h\"\n");
	//}


	fprintf(script, "using namespace std;\n");
	if (program_options_ns::emscripten_flag) {
		fprintf(script, "//string qscript_stdout_fname(\"qscript_stdout.log\");\n");
		fprintf(script, "//FILE * qscript_stdout = 0;\n");
	} else {
		fprintf(script, "string qscript_stdout_fname(\"qscript_stdout.log\");\n");
		fprintf(script, "FILE * qscript_stdout = 0;\n");
	}
	fprintf(script, "#include \"debug_mem.h\"\n\n\n");

	if (program_options_ns::emscripten_flag) {
		fprintf(script, "//fstream debug_log_file(\"qscript_debug.log\", ios_base::out|ios_base::trunc);\n");
	} else {
		fprintf(script, "fstream debug_log_file(\"qscript_debug.log\", ios_base::out|ios_base::trunc);\n");
	}
	fprintf(script, "extern fstream flat_file;\n");
	fprintf(script, "extern fstream xtcc_datafile;\n");
	fprintf(script, "extern fstream qtm_disk_file;\n");
	fprintf(script, "extern set<string> qtm_include_files;\n");

	fprintf(script, "using namespace std;\n");
	fprintf(script, "//extern vector<int32_t> data;\n");
	if ( program_options_ns::flag_nice_map ) {
		fprintf(script, "namespace program_options_ns { bool flag_nice_map = true; }\n");
	} else {
		fprintf(script, "namespace program_options_ns { bool flag_nice_map = false; }\n");
	}

	fprintf(script, "extern UserNavigation user_navigation;\n");
	//fprintf(script, "//vector <AbstractQuestion*> question_list;\n");
	fprintf(script, "vector<mem_addr_tab>  mem_addr;\n");
	fprintf(script, "//extern vector<question_disk_data*>  qdd_list;\n");
	// fprintf(script, "void merge_disk_data_into_questions(FILE * qscript_stdout,\n"
	// 		"\t\tAbstractQuestion * & p_last_question_answered,\n"
	// 		"\t\tAbstractQuestion * & p_last_question_visited);\n");
	//fprintf(script, "void merge_disk_data_into_questions2(FILE * qscript_stdout, AbstractQuestion * & p_last_question_answered, AbstractQuestion * & p_last_question_visited);\n");
	//fprintf(script, "bool stopAtNextQuestion;\n");
	//fprintf(script, "string jumpToQuestion;\n");
	//fprintf(script, "int32_t jumpToIndex;\n");
	fprintf(script, "bool write_messages_flag;\n\n");
	fprintf(script, "bool write_data_file_flag;\n");
	fprintf(script, "bool write_qtm_data_file_flag;\n");
	fprintf(script, "bool write_xtcc_data_file_flag;\n");
	fprintf(script, "bool card_start_flag;\n");
	fprintf(script, "bool card_end_flag;\n");
	fprintf(script, "int card_start;\n");
	fprintf(script, "int card_end;\n");

	fprintf(script, "int32_t check_if_reg_file_exists(string jno, int32_t ser_no);\n");
	fprintf(script, "void print_map_header(fstream & map_file);\n");
	fprintf(script, "map<string, vector<string> > map_of_active_vars_for_questions;\n");
	fprintf(script, "map<string, map<int, int> > freq_count;\n");
	fprintf(script, "void write_data_to_disk(const vector<AbstractRuntimeQuestion*>& q_vec, string jno, int32_t ser_no);\n");
	//fprintf(script, "AbstractQuestion * ComputePreviousQuestion(AbstractQuestion * q);\n");

	// all the code generated below has been moved into the ncurses runtime
	//if (program_options_ns::ncurses_flag) {
	//	print_ncurses_func_prototypes(script);
	//}
	fprintf(script, "void SetupSignalHandler();\n");
	fprintf(script, "static void sig_usr(int32_t signo);\n");
	//fprintf(script, "int32_t ComputeJumpToIndex(AbstractQuestion * q);\n");
	//fprintf(script, "void reset_questionnaire();\n");
	//fprintf(script, "void DisplayActiveQuestions();\n");
	fprintf(script, "string output_data_file_name;\n");
	fprintf(script, "string output_qtm_data_file_name;\n");
	fprintf(script, "string output_xtcc_data_file_name;\n");
	fprintf(script, "void GetUserResponse(string& qno, int32_t &qindex);\n");
	// print_array_question_class(script);
	fprintf(script, "string jno = \"%s\";\n", project_name.c_str());
	fprintf(script, "char * flat_file_output_buffer = 0;\n");
	fprintf(script, "char * xtcc_datafile_output_buffer = 0;\n");
	fprintf(script, "int32_t len_flat_file_output_buffer  = 0;\n");
	fprintf(script, "int32_t len_xtcc_datafile_output_buffer  = 0;\n");
	//print_flat_ascii_data_class(script);
	//print_qtm_data_class(script);

	if (program_options_ns::data_export_flag) {
		fprintf(script, "vector <AsciiFlatFileQuestionDiskMap*> ascii_flatfile_question_disk_map;\n");
		fprintf(script, "vector <XtccDataFileDiskMap*> xtcc_question_disk_map;\n");
		fprintf(script, "vector <qtm_data_file_ns::QtmDataDiskMap*> qtm_datafile_question_disk_map;\n");
		fprintf(script, "qtm_data_file_ns::QtmDataFile qtm_data_file;\n");
	} else {
		fprintf(script, "//vector <AsciiFlatFileQuestionDiskMap*> ascii_flatfile_question_disk_map;\n");
		fprintf(script, "//vector <XtccDataFileDiskMap*> xtcc_question_disk_map;\n");
		fprintf(script, "//vector <qtm_data_file_ns::QtmDataDiskMap*> qtm_datafile_question_disk_map;\n");
		fprintf(script, "//qtm_data_file_ns::QtmDataFile qtm_data_file;\n");
	}
	fprintf(script, "void Compute_FlatFileQuestionDiskDataMap(vector<AbstractRuntimeQuestion*> p_question_list);\n");
	fprintf(script, "void load_languages_available(vector<string> & vec_language);\n");
	fprintf(script, "\n");
	if (program_options_ns::emscripten_flag) {
		fprintf(script, "//int process_options(int argc, char * argv[]);\n");
	} else {
		fprintf(script, "int process_options(int argc, char * argv[]);\n");
	}

	/*
	// This is not necessary any more
	if (program_options_ns::ncurses_flag) {
		fprintf(script, "extern	WINDOW 	* question_window,\n"
				"		* stub_list_window,\n"
				"		* data_entry_window,\n"
				"		* help_window;\n"
				);
		fprintf(script, "extern	PANEL 	* question_panel,\n"
				"		* stub_list_panel,\n"
				"		* data_entry_panel,\n"
				"		* help_panel;\n");
	}
	*/
	fprintf(script, "\tDIR * directory_ptr = 0;\n");
	//fprintf(script, "vector <string> vec_language;\n");

	// fprintf(script, "struct TheQuestionnaire\n{\n");
	// fprintf(script, "AbstractQuestion * last_question_answered = 0;\n");
	/* main was here */


}


void print_close(FILE* script, ostringstream & program_code, bool ncurses_flag)
{

	//print_eval_questionnaire(script, program_code, ncurses_flag);
	// fprintf(script, "%s\n", write_data_to_disk_code());
	// print_navigation_support_functions(script);
	// print_reset_questionnaire(script);
	// PrintDisplayActiveQuestions(script);
	// PrintGetUserResponse(script);


	/*
	 * This code is not now moved to the ncurses runtime environment
	if(ncurses_flag){
		PrintSetupNCurses(script);
		if(config_file_parser::PLATFORM == "LINUX"){
			PrintDefineSomePDCursesKeys(script);
		}
	}
	*/
	// 19-feb-2013 - no need for this
	//PrintSignalHandler(script, ncurses_flag);
	//PrintSetupSignalHandler(script);
	//PrintProcessOptions(script);
	//PrintPrintMapHeader(script);
	if (program_options_ns::stdout_flag) {
		print_new_logic_support_functions (script);
		//print_new_logic_support_functions_2 (script);
	}
	if (program_options_ns::wx_flag||program_options_ns::gtk_flag || program_options_ns::wt_flag) {
		print_new_logic_support_functions_2 (script);
	}
	if (program_options_ns::emscripten_flag) {
		print_emscripten_support_functions (script);
	}

}

void print_question_messages(FILE * script)
{

	fprintf (script, "\n");
	fprintf (script, "void print_question_messages(AbstractQuestion * q)\n");
	fprintf (script, "{\n");
	fprintf (script, "	stringstream question_name;\n");
	fprintf (script, "	question_name << q->questionName_;\n");
	fprintf (script, "	for (int i=0; i< q->loop_index_values.size(); ++i) {\n");
	fprintf (script, "		question_name << \"_\" << q->loop_index_values[i];\n");
	fprintf (script, "	}\n");
	fprintf (script, "	for (int i=0; i< q->textExprVec_.size(); ++i) {\n");
	fprintf (script, "		messages << \"<message id=\\\"\" << question_name.str() \n");
	fprintf (script, "			<< \"_\" << i << \"\\\">\" \n");
	fprintf (script, "			<< q->textExprVec_[i]->text_ \n");
	fprintf (script, "			<< \"</message>\\n\" << endl;\n");
	fprintf (script, "	}\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");

}

void print_navigation_support_functions(FILE * script)
{
	fprintf(script, "// The first question before this question that is answered\n");
	fprintf(script, "AbstractQuestion * ComputePreviousQuestion(AbstractQuestion * q)\n");
	fprintf(script, "{\n");
	fprintf(script, "	int32_t current_question_index = -1;\n");
	//fprintf(script, "	for(int32_t i = 0; i < question_list.size(); ++i)\n");
	fprintf(script, "	if (q) {\n");
	fprintf(script, "		for (int32_t i = questions_start_from_here_index; i < question_list.size(); ++i) {\n");
	fprintf(script, "			if (question_list[i] == q) {\n");
	fprintf(script, "				current_question_index = i;\n");
	fprintf(script, "				break;\n");
	fprintf(script, "			}\n");
	fprintf(script, "		}\n");
	fprintf(script, "	} else {\n");
	fprintf(script, "		current_question_index = question_list.size();\n");
	fprintf(script, "	}\n");
	fprintf(script, "	if (current_question_index == -1) {\n");
	fprintf(script, "		cerr << \"internal compiler error at runtime ... filename: \" \n");
	fprintf(script, "			<< __FILE__ \n");
	fprintf(script, "			<< \"line no: \" << __LINE__\n");
	fprintf(script, "			<< endl;\n");
	fprintf(script, "	}\n");
	fprintf(script, "	for (int32_t i = current_question_index-1; i >= 0; --i) {\n");
	fprintf(script, "		if (question_list[i]->isAnswered_) {\n");
	fprintf(script, "			return question_list[i];\n");
	fprintf(script, "		}\n");
	fprintf(script, "	}\n");
	fprintf(script, "// If we reach here just return the 1st question and hope for the best\n");
	fprintf(script, "// This will not work if there is a condition on the 1st question - because of which it should never have been taken\n");
	fprintf(script, "	return question_list[questions_start_from_here_index];\n");
	fprintf(script, "}\n");

	fprintf(script,"int32_t ComputeJumpToIndex(AbstractQuestion * q)\n");
	fprintf(script,"{\n");
	fprintf(script,"	//cout << \"ENTER ComputeJumpToIndex: index:  \";\n");
	fprintf(script,"	//for (int32_t i = 0; i < q->loop_index_values.size(); ++i) {\n");
	fprintf(script,"	//	cout << q->loop_index_values[i] << \" \";\n");
	fprintf(script,"	//}\n");
	fprintf(script,"	//cout << endl;\n");
	fprintf(script,"	int32_t index = 0;\n");
	fprintf(script,"	for (int32_t i = 0; i < q->loop_index_values.size(); ++i) {\n");
	fprintf(script,"		int32_t tmp1=q->loop_index_values[i];\n");
	fprintf(script,"		for (int32_t j = i+1; j < q->dummyArrayQuestion_->array_bounds.size(); ++j) {\n");
	fprintf(script,"			tmp1 *=q->dummyArrayQuestion_->array_bounds[j];\n");
	fprintf(script,"		}\n");
	fprintf(script,"		index+=tmp1;\n");
	fprintf(script,"	}\n");
	fprintf(script,"	//cout << \"EXIT ComputeJumpToIndex: returning : \" << index << endl;\n");
	fprintf(script,"	return index;\n");
	fprintf(script,"}\n");
}

void print_reset_questionnaire(FILE * script)
{
	fprintf(script, "void reset_questionnaire(){\n");
	fprintf(script, "for(int32_t i = 0; i< question_list.size(); ++i){\n");
	fprintf(script, "\tquestion_list[i]->isAnswered_ = false;\n");
	fprintf(script, "\tquestion_list[i]->input_data.clear();\n");
	fprintf(script, "\t}\n");
	fprintf(script, "}\n");

}

void PrintSetupNCurses(FILE * script)
{
	//fprintf(script, "void SetupNCurses(WINDOW * &  question_window,\n");
	//fprintf(script, "			WINDOW * &  stub_list_window,\n");
	//fprintf(script, "			WINDOW * & data_entry_window)\n");

	fprintf(script, "void SetupNCurses(WINDOW * &  question_window,\n"
			"			WINDOW * &  stub_list_window,\n"
			"			WINDOW * & data_entry_window,\n"
			"			WINDOW * & help_window,\n"
			"			PANEL * &  question_panel,\n"
			"			PANEL * &  stub_list_panel,\n"
			"			PANEL * & data_entry_panel,\n"
			"			PANEL * & help_panel)\n");
	fprintf(script, "{\n");
	fprintf(script, "	initscr();\n");
	fprintf(script, "       cbreak();\n");
	//fprintf(script, "       noecho();\n");
	fprintf(script, "       nonl();\n");
	fprintf(script, "       intrflush(stdscr, FALSE);\n");
	fprintf(script, "	if(has_colors() == FALSE)\n");
	fprintf(script, "	{	endwin();\n");
	fprintf(script, "		printf(\"Your terminal does not support color\\n\");\n");
	fprintf(script, "		exit(1);\n");
	fprintf(script, "	}\n");
	fprintf(script, "	start_color();\n");
	fprintf(script, "	chtype space = ' ';");
	fprintf(script, "	init_pair(1, COLOR_RED, COLOR_WHITE);\n");
	fprintf(script, "	init_pair(2, COLOR_GREEN, COLOR_WHITE);\n");
	fprintf(script, "	init_pair(3, COLOR_BLUE, COLOR_WHITE);\n");
	fprintf(script, "	init_pair(4, COLOR_MAGENTA, COLOR_CYAN);\n");
	fprintf(script, "	init_pair(5, COLOR_WHITE, COLOR_RED);\n");






	fprintf(script, "	int32_t maxX, maxY;\n");
	fprintf(script, "	getmaxyx(stdscr, maxY, maxX);\n");
	fprintf(script, "\n");
	fprintf(script, "\n");
	fprintf(script, "	int32_t DATA_ENTRY_WINDOW_HEIGHT=5, DATA_ENTRY_WINDOW_WIDTH=maxX;\n");
	fprintf(script, "\n");
	fprintf(script, "       int32_t starty = maxY-DATA_ENTRY_WINDOW_HEIGHT;\n");
	fprintf(script, "       int32_t startx = 0;\n");
	fprintf(script, "	data_entry_window = create_newwin(DATA_ENTRY_WINDOW_HEIGHT\n");
	fprintf(script, "			, DATA_ENTRY_WINDOW_WIDTH, starty, startx);\n");
	fprintf(script, "	wcolor_set(data_entry_window, COLOR_PAIR(1), 0);\n");
	fprintf(script, "	wattron(data_entry_window, COLOR_PAIR(1));\n");
	fprintf(script, "	wbkgd(data_entry_window, space | COLOR_PAIR(1));\n");
	fprintf(script, "	wattrset(data_entry_window, COLOR_PAIR(1));\n");

	//fprintf(script, "       wrefresh(data_entry_window);\n");
	//fprintf(script, "	mvwprintw(data_entry_window, 1, 1, "data_entry_window: height: %d, width, %d"\n");
	//fprintf(script, "			, DATA_ENTRY_WINDOW_HEIGHT , DATA_ENTRY_WINDOW_WIDTH);\n");
	fprintf(script, "       keypad(data_entry_window, TRUE);\n");
	fprintf(script, "	// Divide the rest of the screen between the question window\n");
	fprintf(script, "	//  and the stub window in the ration 1:2\n");
	fprintf(script, "	int32_t height_left = maxY - DATA_ENTRY_WINDOW_HEIGHT;\n");
	fprintf(script, "	int32_t STUB_LIST_WINDOW_HEIGHT=(height_left / 3)*2, STUB_LIST_WINDOW_WIDTH=maxX;\n");
	//fprintf(script, "	mvwprintw(data_entry_window, 2, 1, "stub_list_window: height: %d, width, %d"\n");
	//fprintf(script, "			, STUB_LIST_WINDOW_HEIGHT , STUB_LIST_WINDOW_WIDTH);\n");
	fprintf(script, "	starty = maxY - DATA_ENTRY_WINDOW_HEIGHT - STUB_LIST_WINDOW_HEIGHT;\n");
	fprintf(script, "	stub_list_window = create_newwin(STUB_LIST_WINDOW_HEIGHT\n");
	fprintf(script, "			, STUB_LIST_WINDOW_WIDTH, starty, startx);\n");
	fprintf(script, "	wcolor_set(stub_list_window, 2, 0);\n");
	fprintf(script, "	wbkgd(stub_list_window, space | COLOR_PAIR(2));\n");
	fprintf(script, "	wattron(stub_list_window, COLOR_PAIR(2));\n");
	fprintf(script, "\n");
	//fprintf(script, "	mvwprintw(stub_list_window, 2, 1, "stub_list_window: height: %d, width, %d"\n");
	//fprintf(script, "			, STUB_LIST_WINDOW_HEIGHT , STUB_LIST_WINDOW_WIDTH);\n");
	//fprintf(script, "	wrefresh(stub_list_window);\n");
	fprintf(script, "\n");
	fprintf(script, "\n");
	fprintf(script, "	int32_t QUESTION_WINDOW_HEIGHT=(height_left%%3) + (height_left/3), QUESTION_WINDOW_WIDTH=maxX;\n");
	fprintf(script, "	starty = 0;\n");
	fprintf(script, "	question_window = create_newwin(QUESTION_WINDOW_HEIGHT\n");
	fprintf(script, "			, QUESTION_WINDOW_WIDTH, starty, startx);\n");
	fprintf(script, "	wbkgd(question_window, space | COLOR_PAIR(3));\n");
	fprintf(script, "	wcolor_set(question_window, 3, 0);\n");
	fprintf(script, "	wattron(question_window, COLOR_PAIR(3));\n");
	//fprintf(script, "	mvwprintw(question_window, 1, 1, "question_window: height: %d, width, %d"\n");
	//fprintf(script, "			, QUESTION_WINDOW_HEIGHT , QUESTION_WINDOW_WIDTH);\n");
	//fprintf(script, "	wrefresh(question_window);\n");
	fprintf(script, "\n");
	fprintf(script, "	wmove(data_entry_window, 1,1);\n");
	//fprintf(script, "	wgetch(data_entry_window);\n");
	if(config_file_parser::PLATFORM == "LINUX"|| config_file_parser::PLATFORM == "UNIX"){
		fprintf(script, "	define_some_pd_curses_keys();\n");
	}
	fprintf(script, "	int32_t HELP_WINDOW_HEIGHT=(int)((float)(2/3)*maxY), HELP_WINDOW_WIDTH=maxX/2;\n");
	fprintf(script, "\n");
	fprintf(script, "       starty = 5;\n");
	fprintf(script, "       startx = 5;\n");
	fprintf(script, "	//help_window = create_newwin(HELP_WINDOW_HEIGHT, HELP_WINDOW_WIDTH, starty, startx);\n");

	fprintf(script, "	question_panel = new_panel(question_window);\n"
			"	stub_list_panel = new_panel(stub_list_window);\n"
			"	data_entry_panel = new_panel(data_entry_window);\n"
			"	//help_panel = new_panel(help_window);\n"
			);
	fprintf(script, "	update_panels();\n"
			"	doupdate();\n");
	fprintf(script, "}\n");
	fprintf(script, "\n");
	fprintf(script, "\n");
	fprintf(script, "\n");
	fprintf(script, "WINDOW *create_newwin(int32_t height, int32_t width, int32_t starty, int32_t startx)\n");
	fprintf(script, "{       WINDOW *local_win;\n");
	fprintf(script, "\n");
	fprintf(script, "        local_win = newwin(height, width, starty, startx);\n");
	fprintf(script, "        box(local_win, 0 , 0);          /* 0, 0 gives default characters \n");
	fprintf(script, "                                         * for the vertical and horizontal\n");
	fprintf(script, "                                         * lines                        */\n");
	// no need for this once we are using panels
	//fprintf(script, "        wrefresh(local_win);            /* Show that box                */\n");
	fprintf(script, "\n");
	fprintf(script, "        return local_win;\n");
	fprintf(script, "}\n");
	fprintf(script, "\n");
}

void PrintDisplayActiveQuestions(FILE *script)
{
	fprintf(script, "void DisplayActiveQuestions()\n{\n\
			\tfor(int32_t i = 0; i<question_list.size(); ++i){\n\
			\t\tif(question_list[i]->isAnswered_)\n\
			\t\t\tcout << question_list[i]->questionName_ << \" \";\n\
			\t}\
			\tcout << endl;\n\
			\n}\n");
}

void PrintGetUserResponse(FILE *script)
{
	fprintf(script, "void GetUserResponse(string & qno, int32_t & qindex)\n{\n\
			char newl;\n\
			cin >> qno;cin.get(newl);\nqindex = 0;\n\
			cout << \"User input qno:\" << qno \n\
				<< \", newl: \" << newl << endl;\n\
			}\n");
}

bool skip_func_type_check(const char * fname)
{
	const char * skip_func_type_check_list[] = {"printf" };
	for(uint32_t i = 0; i < sizeof(skip_func_type_check_list)/sizeof(skip_func_type_check_list[0]); ++i){
		if(!strcmp(fname, skip_func_type_check_list[i])){
			return true;
		}
	}
	return false;
}

int32_t check_parameters(AbstractExpression* e, VariableList* v)
{
	debug_log_file << "check_parameters: called" << endl;
	AbstractExpression* e_ptr = e;
	VariableList* fparam = v;
	bool match = true;
	/* Important point to note: I am not allowing references in ordinary variable decl
	   Only in function parameter list - the object is to allow modifying of variables
	   in a function as in C++
	   */
	cerr << "Fix this function DOES NOT REPORT ERRORS using print_err"
	     << ", line: " << __LINE__
	     << ", file: " << __FILE__
	     << ", function: " << __PRETTY_FUNCTION__ << endl;
	int32_t chk_param_counter = 1;
	while(e_ptr && fparam) {
		//e_ptr->print();
		DataType etype = e_ptr->type_, fptype = fparam->variableType_;
		if((etype >= INT8_TYPE && etype <= DOUBLE_TYPE)
		   && ((fptype >= INT8_TYPE && fptype <= DOUBLE_TYPE)
		       || (fptype >= INT8_REF_TYPE && fptype <= DOUBLE_REF_TYPE))){
			DataType tdt = fptype;
				/* the code below makes a INT8_REF_TYPE -> INT8_TYPE
				   			a INT8_REF_TYPE -> INT8_TYPE
				 thats because we dont care much about references -> C++
				 does all the hard work. For checking types they are equivalent to us
				*/
			if(tdt >= INT8_REF_TYPE) tdt = DataType(INT8_TYPE+tdt-INT8_REF_TYPE);
			if(etype <= tdt) {
				debug_log_file << "varname: "<< fparam->variableName_ << " chk_param_counter: "
					<< chk_param_counter << " passed " << endl;
			}
		} else if ((etype >= INT8_ARR_TYPE&&etype <= DOUBLE_ARR_TYPE)
			   && (fptype >= INT8_ARR_TYPE&&fptype <= DOUBLE_ARR_TYPE)
			   && (etype == fptype)){
			debug_log_file << "varname: "<< fparam->variableName_ << " chk_param_counter: "
					<< chk_param_counter << " passed " << endl;
		} else {
			match = false;
			cerr << "Parameter type mismatch name: " << endl;
			cerr << fparam->variableName_ << " expected type is " << fparam->variableType_
				<< " passed type is " << e_ptr->type_
				<< " line_no: " << line_no << " or currently allowed promotion to: "
				<< e_ptr->type_+INT8_REF_TYPE
				<< endl;
			++no_errors;
		}
		e_ptr = e_ptr->next_;
		fparam = fparam->next_;
		chk_param_counter = chk_param_counter+1;
	}
	if(match == true){
		if(e_ptr == 0 && fparam == 0){
			match = true;
		} else {
			match = false;
			++no_errors;
			cerr << "NOTMATCHED: No of parameters in function call not matching with no of paramters in AbstractExpression: line_no"
				<< line_no << endl;
		}
	}
	if(!match){
		cerr << "function parameter type check FAILURE: line_no " << line_no << endl;
	}
	return match;
}


const char * file_exists_check_code()
{
	const char * file_check_code =
	"\tif (write_data_file_flag||write_qtm_data_file_flag||write_xtcc_data_file_flag) {\n"
	"\t	ser_no = read_a_serial_no();\n"
	"\t	if (ser_no == 0) {\n"
	"\t		exit(1);\n"
	"\t	}\n"
	"\t} else {\n"
	"\t\tint exists = check_if_reg_file_exists(jno, ser_no);\n"
	"\t\tif (exists == 1) {\n"
	"\t\t	map <string, question_disk_data*>  qdd_map;\n"
	"\t\t	load_data (jno, ser_no, &qdd_map);\n"
	"\t\t	//merge_disk_data_into_questions(qscript_stdout, last_question_answered, last_question_visited);\n"
	"\t\t	//merge_disk_data_into_questions2 (qscript_stdout, last_question_answered, last_question_visited, this->question_list, &qdd_map);\n"
	"\t\t}\n\t}\n";
	if (qscript_debug::MAINTAINER_MESSAGES){
		cerr << "fix me : add code for `if file is invalid` case "
			<< __func__ << "FILE: " << __FILE__
			<< ", line: " << __LINE__ << endl;
	}

	return file_check_code;
}

AbstractStatement* setup_stub_manip_stmt(DataType dt
					 , char* stub_list_name
					 , Unary2Expression * p_arr_index
					 , Unary2Expression * p_mask_expr
					 )
{
	bool range_stub = false, question_stub = false;
	named_range * lhs_stub =  named_stub_exists (stub_list_name);
	if (lhs_stub) {
		range_stub = true;
	}
	NamedStubQuestion * lhs_question = 0;
	int32_t index = question_exists (stub_list_name);
	if (index >= 0) {
		question_stub = true;
		lhs_question = dynamic_cast<NamedStubQuestion*>(question_list[index]);
		if (!lhs_question) {
			stringstream err_text;
			err_text << "Question : " << stub_list_name
				<< "is not a named stub Question";
			print_err (compiler_sem_err, err_text.str(),
				line_no, __LINE__, __FILE__);
			return new ErrorStatement(line_no, 0, 0);
		}
	} else  if (index == -1 && lhs_stub == 0)  {
		stringstream err_text;
		err_text << "named stub list does not exist: " << stub_list_name;
		print_err (compiler_sem_err, err_text.str(),
				line_no, __LINE__, __FILE__);
		return new ErrorStatement(line_no, 0, 0);
	}
	struct AbstractStatement* st_ptr  = 0;
	if (range_stub) {
		st_ptr = new StubManipStatement(dt,
				line_no, nest_lev, flagIsAForBody_,
				lhs_stub, p_mask_expr);
	} else {
		st_ptr = new StubManipStatement(dt,
				line_no, nest_lev, flagIsAForBody_,
				lhs_question, p_arr_index,
				p_mask_expr);
	}
	return st_ptr;
}


AbstractStatement* setup_stub_manip_stmt(DataType dt
					 , char* stub_list_name
					 , AbstractExpression * l_l_arr_index
					 , char * question_name
					 , AbstractExpression * l_r_arr_index /* =0 */)
{
	std::stringstream warn_mesg;
	warn_mesg << __PRETTY_FUNCTION__
		<< "looks like param l_l_arr_index is not at all used in this function"
		<< " please revisit";

	LOG_MAINTAINER_MESSAGE(warn_mesg.str());
	using qscript_parser::nest_lev;
	using qscript_parser::flagIsAForBody_;
	bool question_stub = false, range_stub=false;
	NamedStubQuestion * lhs_question = 0, * rhs_question=0;
	named_range * lhs_stub =  named_stub_exists (stub_list_name);
	if (lhs_stub) {
		range_stub = true;
	}
#if 0
	for (int32_t i = 0; i < named_stubs_list.size(); ++i) {
		named_range * nr_ptr = named_stubs_list[i];
		if (nr_ptr->name == stub_list_name) {
			index = i;
			range_stub = true;
			lhs_stub = nr_ptr;
			break;
		}
	}
#endif /* 0  */
	// at this point lhs_stub is valid
#if 0
	for (int32_t i = 0; i < question_list.size(); ++i) {
		if (question_list[i]->questionName_  ==  stub_list_name) {
			index = i;
			question_stub = true;
			lhs_question = dynamic_cast<NamedStubQuestion*>(question_list[i]);
			if (!lhs_question) {
				stringstream err_text;
				err_text << "Question : " << stub_list_name <<
					"is not a named stub Question";
				print_err(compiler_sem_err, err_text.str(),
					line_no, __LINE__, __FILE__);
				return new ErrorStatement(line_no, 0, 0);
			}
			break;
		}
	}
#endif /*  0 */
	int32_t index = question_exists (stub_list_name);
	if (index >= 0) {
		question_stub = true;
		lhs_question = dynamic_cast<NamedStubQuestion*>(question_list[index]);
		if (!lhs_question) {
			stringstream err_text;
			err_text << "Question : " << stub_list_name
				<< "is not a named stub Question";
			print_err (compiler_sem_err, err_text.str(),
				line_no, __LINE__, __FILE__);
			return new ErrorStatement(line_no, 0, 0);
		}
	} else  if (index == -1 && lhs_stub == 0)  {
		stringstream err_text;
		err_text << "named stub list does not exist: " << stub_list_name;
		print_err (compiler_sem_err, err_text.str(),
				line_no, __LINE__, __FILE__);
		return new ErrorStatement(line_no, 0, 0);
	}
	// at this point
	// 	1. if lhs_question is not null it is valid and
	// 	2. we need not do any more checks on the 1st argument


#if 0
	int32_t index_question = -1;
	for (int32_t i = 0; i < question_list.size(); ++i) {
		if(question_list[i]->questionName_  ==  question_name){
			index_question = i;
			rhs_question = dynamic_cast<NamedStubQuestion*>(question_list[i]);
			if (!rhs_question) {
				stringstream err_text;
				err_text << "Question : " << question_name <<
					"is not a named stub Question";
				print_err(compiler_sem_err, err_text.str(),
					line_no, __LINE__, __FILE__);
				return new ErrorStatement(line_no, 0, 0);
			}
			break;
		}
	}
#endif /*  0  */

	int32_t index_question = question_exists (question_name);
	if (index_question >= 0) {
		rhs_question = dynamic_cast<NamedStubQuestion*>(question_list[index_question]);
		if (!rhs_question) {
			stringstream err_text;
			err_text << "Question : " << question_name <<
				"is not a named stub Question";
			print_err(compiler_sem_err, err_text.str(),
				line_no, __LINE__, __FILE__);
			return new ErrorStatement(line_no, 0, 0);
		}
	}

	// 	At this point if rhs_question is not null it is a named stub question
	if (index_question == -1) {
		stringstream err_text;
		err_text << "Question does not exist: " << question_name;
		print_err(compiler_sem_err, err_text.str(),
			line_no, __LINE__, __FILE__);
		return new ErrorStatement(line_no, 0, 0);
	}
	// At this point 2nd argument  is valid

	if (range_stub == true) {
		if(!(rhs_question->nr_ptr->name == stub_list_name) ){
			stringstream err_text;
			err_text << "Question: " << question_name
				<< " named range: " << rhs_question->nr_ptr->name
				<< " and named stub is : " << stub_list_name
				<< " do not match"
				<< endl;
			print_err(compiler_sem_err, err_text.str(),
				line_no, __LINE__, __FILE__);
			return new ErrorStatement(line_no, 0, 0);
		}
		if (l_r_arr_index==0) {
			struct AbstractStatement* st_ptr = new StubManipStatement(dt,
				line_no, nest_lev, flagIsAForBody_, lhs_stub, rhs_question);
			return st_ptr;
		} else {
			struct AbstractStatement* st_ptr = new StubManipStatement(dt,
				line_no, nest_lev, flagIsAForBody_, lhs_stub, rhs_question, l_r_arr_index);
			return st_ptr;
		}
	} else if (question_stub == true) {
		if (!(rhs_question->nr_ptr->name == lhs_question->nr_ptr->name) ) {
			stringstream err_text;
			err_text << "1st arg Question: " << lhs_question->questionName_
				<< " named range: " << lhs_question->nr_ptr->name
				<< " and : "
				<< " 2nd arg Question: " << rhs_question->questionName_
				<< " named range: " << rhs_question->nr_ptr->name
				<< " do not match" << endl;
			print_err(compiler_sem_err, err_text.str(),
				line_no, __LINE__, __FILE__);
			return new ErrorStatement(line_no, 0, 0);
		}
		if (l_r_arr_index==0) {
			struct AbstractStatement* st_ptr = new StubManipStatement (
				dt,
				line_no,
				/* nest_lev */ 0,
				/* flagIsAForBody_ */ 0
				, lhs_question, l_l_arr_index
				, rhs_question, l_r_arr_index);
			return st_ptr;
		} else {
			struct AbstractStatement* st_ptr =
				new StubManipStatement (dt,
				line_no, /* nest_lev */ 0,
				/* flagIsAForBody_ */ 0
				, lhs_question, l_l_arr_index
				, rhs_question, l_r_arr_index);
			return st_ptr;
		}

	}
	return new ErrorStatement(line_no, 0, 0);
}


AbstractStatement* setup_stub_manip_stmt_set_unset(DataType dt
						   , char* stub_list_name)
{
	int32_t index = -1;
	for(int32_t i = 0; i < named_stubs_list.size(); ++i){
		named_range * nr_ptr = named_stubs_list[i];
		if(nr_ptr->name == stub_list_name){
			index = i;
			break;
		}
	}
	if(index == -1){
		stringstream err_text;
		err_text << "named stub list does not exist: " << stub_list_name;
		print_err(compiler_sem_err, err_text.str(),
			line_no, __LINE__, __FILE__);
	}
	struct AbstractStatement* st_ptr = new StubManipStatement(dt,
		line_no, nest_lev, flagIsAForBody_, stub_list_name);

	return st_ptr;
}


AbstractStatement* setup_stub_manip_stmt(DataType dt
					 , char* stub_list_name
					 , AbstractExpression * l_l_arr_index
					 , XtccSet & l_xs)
{
	stringstream warn_mesg;
	warn_mesg << " The code below is common in the setup_stub_manip_stmt functions and should be factored out";
	//cerr << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
	//	<< warn_mesg.str() << endl;

	LOG_MAINTAINER_MESSAGE(warn_mesg.str());
	int32_t index = -1;
	bool question_stub = false, range_stub=false;
	NamedStubQuestion * lhs_question = 0;
	named_range * lhs_stub = 0;
	for (int32_t i = 0; i < named_stubs_list.size(); ++i) {
		named_range * nr_ptr = named_stubs_list[i];
		if(nr_ptr->name == stub_list_name){
			index = i;
			range_stub = true;
			lhs_stub = nr_ptr;
			break;
		}
	}
	// at this point lhs_stub is valid
	for (int32_t i = 0; i < question_list.size(); ++i) {
		if (question_list[i]->questionName_  ==  stub_list_name) {
			index = i;
			question_stub = true;
			lhs_question = dynamic_cast<NamedStubQuestion*>(question_list[i]);
			if (!lhs_question) {
				stringstream err_text;
				err_text << "Question : " << stub_list_name <<
					"is not a named stub Question";
				print_err(compiler_sem_err, err_text.str(),
					line_no, __LINE__, __FILE__);
				return new ErrorStatement(line_no, 0, 0);
			}
			break;
		}
	}

	if (index == -1) {
		stringstream err_text;
		err_text << "named stub list does not exist: " << stub_list_name;
		print_err(compiler_sem_err, err_text.str(),
				line_no, __LINE__, __FILE__);
		return new ErrorStatement(line_no, 0, 0);
	}
	// at this point
	// 	1. if lhs_question is not null it is valid and
	// 	2. we need not do any more checks on the 1st argument
	if (range_stub == true) {
		struct AbstractStatement* st_ptr = new StubManipStatement(dt,
						line_no,
						nest_lev, flagIsAForBody_,
						lhs_stub, l_xs);
		return st_ptr;
	} else if (question_stub == true) {
		if (l_l_arr_index == 0) {
			struct AbstractStatement* st_ptr = new StubManipStatement(dt,
						line_no,
						nest_lev, flagIsAForBody_,
						lhs_question, l_xs);
			return st_ptr;
		} else {
			struct AbstractStatement* st_ptr = new StubManipStatement(dt,
						line_no,
						nest_lev, flagIsAForBody_,
						lhs_question, l_l_arr_index, l_xs);
			return st_ptr;
		}
	}
	return new ErrorStatement(line_no, 0, 0);
}

const char * write_data_to_disk_code()
{
	const char * write_data_disk_code =
	"\tvoid write_data_to_disk(const vector<AbstractQuestion*>& q_vec\n"
	"\t	, string jno\n"
	"\t	, int32_t ser_no) {\n"
	"\t	stringstream fname_str;\n"
	"\t	fname_str << jno << \"_\" << ser_no << \".dat\";\n"
	"\t	//FILE * fptr = fopen(fname_str.str().c_str(), \"w+b\");\n"
	"\t\n"
	"\t\n"
	"\t	std::ofstream data_file;\n"
	"\t	data_file.exceptions(std::ios::failbit | std::ios::badbit);\n"
	"\t	data_file.open(fname_str.str().c_str(), ios_base::ate);\n"
	"\t\n"
	"\t	for(int32_t i = 0; i < question_list.size(); ++i){\n"
	"\t		question_list[i]->WriteDataToDisk(data_file);\n"
	"\t		/*\n"
	"\t		fprintf(fptr, \"%s: \", question_list[i]->name.c_str());\n"
	"\t		for( set<int32_t>::iterator iter = question_list[i]->input_data.begin();\n"
	"\t				iter != question_list[i]->input_data.end(); ++iter){\n"
	"\t			fprintf(fptr, \"%d \", *iter);\n"
	"\t		}\n"
	"\t		fprintf(fptr, \"\n\");\n"
	"\t		question_list[i]->input_data.clear();\n"
	"\t		*/\n"
	"\t	}\n"
	"\t	data_file.flush();\n"
	"\t	data_file.close();\n"
	"\t	//fclose(fptr);\n"
	"\t}\n"
	"\n";
	return write_data_disk_code;
}


void print_array_question_class(FILE* script)
{
	fprintf(script, "class ArrayQuestion\n");
	fprintf(script, "{\n");
	fprintf(script, "public: \n");
	fprintf(script, "\tvector<AbstractQuestion*> questionList;\n");
	fprintf(script, "\tvector<int32_t> arrayBounds;\n");
	fprintf(script, "\tArrayQuestion(vector<int32_t>& l_arrayBounds): arrayBounds(l_arrayBounds)\n");
	fprintf(script, "\t{\n");
	fprintf(script, "\t\tint bounds = 1;\n");
	fprintf(script, "\t\tfor(int32_t i = 0; i<arrayBounds.size(); ++i){\n");
	fprintf(script, "\t\t\tbounds*=arrayBounds[i];\n");
	fprintf(script, "\t\t}\n");
	fprintf(script, "\t\tquestionList.reserve(bounds);\n");
	fprintf(script, "\t}\n");
	fprintf(script, "};\n\n");

}

#if 0
void print_flat_ascii_data_class(FILE *script)
{

	fprintf(script, "class AsciiFlatFileQuestionDiskMap\n");
	fprintf(script, "{\n");
	fprintf(script, "public:\n");
	fprintf(script, "	AbstractQuestion *q;\n");
	fprintf(script, "	int32_t start_pos;\n");
	fprintf(script, "	int32_t width;\n");
	fprintf(script, "	int32_t total_length;\n");
	fprintf(script, "	AsciiFlatFileQuestionDiskMap(AbstractQuestion * p_q, int32_t p_start_pos/*,\n");
	fprintf(script, "					int32_t p_width, int32_t p_total_length*/) \n");
	fprintf(script, "		:\n");
	fprintf(script, "		q(p_q), start_pos(p_start_pos)/*, width(p_width), \n");
	fprintf(script, "		total_length(p_total_length)*/\n");
	fprintf (script, "	{\n");
	fprintf (script, "		int max_code = q->GetMaxCode();\n");
	fprintf (script, "		if (max_code < 10) {\n");
	fprintf (script, "			width = 1;\n");
	fprintf (script, "		} else if (max_code < 100) {\n");
	fprintf (script, "			width = 2;\n");
	fprintf (script, "		} else if (max_code < 1000) {\n");
	fprintf (script, "			width = 3;\n");
	fprintf (script, "		} else if (max_code < 10000) {\n");
	fprintf (script, "			width = 4;\n");
	fprintf (script, "		} else if (max_code < 100000) {\n");
	fprintf (script, "			width = 5;\n");
	fprintf (script, "		} else if (max_code < 1000000) {\n");
	fprintf (script, "			width = 6;\n");
	fprintf (script, "		} else if (max_code < 10000000) {\n");
	fprintf (script, "			width = 7;\n");
	fprintf (script, "		} else if (max_code < 100000000) {\n");
	fprintf (script, "			width = 8;\n");
	fprintf (script, "		} else if (max_code < 1000000000) {\n");
	fprintf (script, "			width = 9;\n");
	fprintf (script, "		} else { cout << \" max_code \" << max_code << \" for question: \" << q->questionName_ << \" exceeds max length = 9 we are programmed to handled ... exiting \" << __FILE__ << \",\"  << __LINE__ << \",\"  << __PRETTY_FUNCTION__ << endl;\n exit(1);}\n");
	fprintf (script, "		total_length = width * q->no_mpn;\n");
	fprintf (script, "	}\n");
	fprintf (script, "\n");

	fprintf(script, "	int GetTotalLength() { return total_length; }\n");
	fprintf(script, "	void write_data (char * output_buffer)");

	fprintf(script, "		{\n");
	fprintf(script, "			char * ptr = output_buffer + start_pos;\n");
	fprintf(script, "			int no_responses_written = 0;\n");
	fprintf(script, "			for (set<int>::iterator it = q->input_data.begin();\n");
	fprintf(script, "					it != q->input_data.end(); ++it) {\n");
	fprintf(script, "				int code = *it;\n");
	fprintf(script, "				stringstream code_str;\n");
	fprintf(script, "				code_str << code;\n");
	fprintf(script, "				cout << \"writing code: \" << code << \" to output_buffer: length: \" << code_str.str().length() << \"\\n\";\n");
	fprintf(script, "				if (code_str.str().length() > width) {\n");
	fprintf(script, "					cerr << \" internal programming error - width of code exceeds width allocated ... exiting\\n\";\n");
	fprintf(script, "					exit(1);\n");
	fprintf(script, "				}\n");
	fprintf(script, "				// int bytes_written = snprintf(ptr, code_str.str().length(), \"%%s\", code_str.str().c_str());\n");
	fprintf(script, "				// int bytes_written = snprintf(ptr, code_str.str().length(), \"%%d\", code);\n");

	fprintf(script, "				for (int i=0; i<code_str.str().length(); ++i) {\n");
	fprintf(script, "					ptr[i] = (code_str.str())[i];\n");
	fprintf(script, "				}\n");

	fprintf(script, "				// ptr[bytes_written] = ' ';\n");
	fprintf(script, "				//if (bytes_written > width) {\n");
	fprintf(script, "				//	cerr << \"impossible internal programming error - width of code exceeds width allocated ... exiting\\n\";\n");
	fprintf(script, "				//	exit(1);\n");
	fprintf(script, "				//}\n");
	fprintf(script, "				ptr += width;\n");
	fprintf(script, "				++no_responses_written;\n");
	fprintf(script, "				if (no_responses_written > q->no_mpn) {\n");
	fprintf(script, "					cerr << \" no of responses in question : \" << q->questionName_ << \" exceeds no allocated ... exiting\\n\";\n");
	fprintf(script, "					exit(1);\n");
	fprintf(script, "				}\n");
	fprintf(script, "			}\n");
	fprintf(script, "		}\n");

	fprintf(script, "	void print_map(fstream & map_file)\n{\n");
	fprintf(script, "	map_file << q->questionName_;\n");
	fprintf(script, "	if (q->loop_index_values.size()) {\n");
	fprintf(script, "		for (int i=0; i< q->loop_index_values.size(); ++i) {\n");
	fprintf(script, "			map_file << \".\" << q->loop_index_values[i];\n");
	fprintf(script, "		}\n");
	fprintf(script, "	}\n");
	fprintf(script, "	map_file << \",\t\t\t\";\n");
	fprintf(script, "	map_file << width << \",\t\";\n");
	fprintf(script, "	map_file << q->no_mpn << \",\t\";\n");
	fprintf(script, "	map_file << start_pos+1 << \",\t\";\n");
	fprintf(script, "	map_file << start_pos + total_length  << \"\\n\";\n");
	fprintf(script, "}\n");

	fprintf(script, "};\n");
	fprintf(script, "\n");
}
#endif /* 0 */

#if 0
void print_qtm_data_class(FILE *script)
{

	fprintf(script, "class QtmDataDiskMap\n");
	fprintf(script, "{\n");
	fprintf(script, "public:\n");
	fprintf(script, "	AbstractQuestion *q;\n");
	fprintf(script, "	int32_t start_pos;\n");
	fprintf(script, "	int32_t width;\n");
	fprintf(script, "	int32_t total_length;\n");
	fprintf(script, "	QtmDataDiskMap(AbstractQuestion * p_q, int32_t p_start_pos/*,\n");
	fprintf(script, "					int32_t p_width, int32_t p_total_length*/) \n");
	fprintf(script, "		:\n");
	fprintf(script, "		q(p_q), start_pos(p_start_pos)/*, width(p_width), \n");
	fprintf(script, "		total_length(p_total_length)*/\n");
	fprintf (script, "	{\n");
	fprintf (script, "		int max_code = q->GetMaxCode();\n");
	fprintf (script, "		if (max_code < 10) {\n");
	fprintf (script, "			width = 1;\n");
	fprintf (script, "		} else if (max_code < 100) {\n");
	fprintf (script, "			width = 2;\n");
	fprintf (script, "		} else if (max_code < 1000) {\n");
	fprintf (script, "			width = 3;\n");
	fprintf (script, "		} else if (max_code < 10000) {\n");
	fprintf (script, "			width = 4;\n");
	fprintf (script, "		} else if (max_code < 100000) {\n");
	fprintf (script, "			width = 5;\n");
	fprintf (script, "		} else if (max_code < 1000000) {\n");
	fprintf (script, "			width = 6;\n");
	fprintf (script, "		} else if (max_code < 10000000) {\n");
	fprintf (script, "			width = 7;\n");
	fprintf (script, "		} else if (max_code < 100000000) {\n");
	fprintf (script, "			width = 8;\n");
	fprintf (script, "		} else if (max_code < 1000000000) {\n");
	fprintf (script, "			width = 9;\n");
	fprintf (script, "		} else { cout << \" max_code \" << max_code << \" for question: \" << q->questionName_ << \" exceeds max length = 9 we are programmed to handled ... exiting \" << __FILE__ << \",\"  << __LINE__ << \",\"  << __PRETTY_FUNCTION__ << endl;\n exit(1);}\n");
	fprintf (script, "		total_length = width * q->no_mpn;\n");
	fprintf (script, "	}\n");
	fprintf (script, "\n");

	fprintf(script, "	int GetTotalLength() { return total_length; }\n");
	fprintf(script, "	void write_data (char * output_buffer)");

	fprintf(script, "		{\n");
	fprintf(script, "			char * ptr = output_buffer + start_pos;\n");
	fprintf(script, "			int no_responses_written = 0;\n");
	fprintf(script, "			for (set<int>::iterator it = q->input_data.begin();\n");
	fprintf(script, "					it != q->input_data.end(); ++it) {\n");
	fprintf(script, "				int code = *it;\n");
	fprintf(script, "				stringstream code_str;\n");
	fprintf(script, "				code_str << code;\n");
	fprintf(script, "				cout << \"writing code: \" << code << \" to output_buffer: length: \" << code_str.str().length() << \"\\n\";\n");
	fprintf(script, "				if (code_str.str().length() > width) {\n");
	fprintf(script, "					cerr << \" internal programming error - width of code exceeds width allocated ... exiting\\n\";\n");
	fprintf(script, "					exit(1);\n");
	fprintf(script, "				}\n");
	fprintf(script, "				// int bytes_written = snprintf(ptr, code_str.str().length(), \"%%s\", code_str.str().c_str());\n");
	fprintf(script, "				// int bytes_written = snprintf(ptr, code_str.str().length(), \"%%d\", code);\n");

	fprintf(script, "				for (int i=0; i<code_str.str().length(); ++i) {\n");
	fprintf(script, "					ptr[i] = (code_str.str())[i];\n");
	fprintf(script, "				}\n");

	fprintf(script, "				// ptr[bytes_written] = ' ';\n");
	fprintf(script, "				//if (bytes_written > width) {\n");
	fprintf(script, "				//	cerr << \"impossible internal programming error - width of code exceeds width allocated ... exiting\\n\";\n");
	fprintf(script, "				//	exit(1);\n");
	fprintf(script, "				//}\n");
	fprintf(script, "				ptr += width;\n");
	fprintf(script, "				++no_responses_written;\n");
	fprintf(script, "				if (no_responses_written > q->no_mpn) {\n");
	fprintf(script, "					cerr << \" no of responses in question : \" << q->questionName_ << \" exceeds no allocated ... exiting\\n\";\n");
	fprintf(script, "					exit(1);\n");
	fprintf(script, "				}\n");
	fprintf(script, "			}\n");
	fprintf(script, "		}\n");

	fprintf(script, "	void print_map(fstream & map_file)\n{\n");
	fprintf(script, "	map_file << q->questionName_;\n");
	fprintf(script, "	if (q->loop_index_values.size()) {\n");
	fprintf(script, "		for (int i=0; i< q->loop_index_values.size(); ++i) {\n");
	fprintf(script, "			map_file << \".\" << q->loop_index_values[i];\n");
	fprintf(script, "		}\n");
	fprintf(script, "	}\n");
	fprintf(script, "	map_file << \",\t\t\t\";\n");
	fprintf(script, "	map_file << width << \",\t\";\n");
	fprintf(script, "	map_file << q->no_mpn << \",\t\";\n");
	fprintf(script, "	map_file << start_pos+1 << \",\t\";\n");
	fprintf(script, "	map_file << start_pos + total_length  << \"\\n\";\n");
	fprintf(script, "}\n");

	fprintf(script, "};\n");
	fprintf(script, "\n");
}
#endif /* 0 */

void PrintActiveVariablesAtScope(vector <Scope*> & active_scope_list
				 , vector <ActiveVariableInfo*> & output_info)
{
	for(uint32_t i = 0; i< active_scope_list.size(); ++i){
		Scope* sc_ptr= active_scope_list[i];
		sc_ptr->print_scope(output_info);
		//sc_ptr->print_scope(name, active_push_vars, active_pop_vars);
	}
}

void PrintSignalHandler(FILE * script, bool ncurses_flag)
{
	fprintf(script, "static void sig_usr(int32_t signo)\n");
	fprintf(script, "{\n");
	fprintf(script, "	if(signo == SIGSEGV){\n");
	fprintf(script, "		printf(\"received SIGSEGV\\n\");\n");
	fprintf(script, "	} else if(signo == SIGILL){\n");
	fprintf(script, "		printf(\"received SIGILL\\n\");\n");
	fprintf(script, "} else if(signo == SIGHUP) {\n");
	fprintf(script, "	printf(\"received, SIGHUP: ignore this signal\\n\");\n");
	fprintf(script, "	return;\n");
	fprintf(script, "} else {\n");
	fprintf(script, "	fprintf(stderr, \"received signal : %%d\\n\", signo);\n");
	fprintf(script, "}\n");
	fprintf(script, "	fflush(qscript_stdout);\n");
	if (ncurses_flag) {
		fprintf(script, "	 endwin();\n");
	}
	fprintf(script, "	exit(1);\n");
	fprintf(script, "}\n");
}

void PrintSetupSignalHandler(FILE * script)
{
	fprintf(script, "void SetupSignalHandler()\n{\n");
	fprintf(script, "	if (signal (SIGSEGV, sig_usr) == SIG_ERR) {\n");
	fprintf(script, "		fprintf(stderr, \"cannot catch SIGSEGV\\n\");\n");
	fprintf(script, "		exit(1);\n");
	fprintf(script, "	}  else if (signal (SIGHUP, SIG_IGN) == SIG_ERR) {\n");
	fprintf(script, "		fprintf(stderr, \"cannot ignore SIGHUP\\n\");\n");
	fprintf(script, "		exit(1);\n");
	fprintf(script, "	}  else if (signal (SIGILL, sig_usr) == SIG_ERR) {\n");
	fprintf(script, "		fprintf(stderr, \"cannot catch SIGILL\\n\");\n");
	fprintf(script, "		exit(1);\n");
	fprintf(script, "	}\n");
	fprintf(script, "}\n\n");
}

// Returns 0 on failure, 1 on success
int32_t ReadQScriptConfig()
{
	cerr << "Enter qscript_parser::ReadQScriptConfig" << endl;
	using namespace std;
	//string QSCRIPT_HOME = getenv("QSCRIPT_HOME");
	string QSCRIPT_HOME = program_options_ns::QSCRIPT_HOME;
	string::size_type contains_space = QSCRIPT_HOME.find_last_of(" ");
	if (contains_space != string::npos) {
		QSCRIPT_HOME.erase(contains_space);
	}
	string QSCRIPT_CONFIG = QSCRIPT_HOME + "/config/qscript.config";
	FILE * qscript_confin = fopen(QSCRIPT_CONFIG.c_str(), "rb");
	qscript_confrestart(qscript_confin);
	if(!qscript_confin){
		cout << "unable to open " <<  QSCRIPT_CONFIG <<" for reading ... exiting\n";
		return 0;
	}
	cerr << "opened : " << QSCRIPT_CONFIG << endl;

	if(!qscript_confparse()){
		cout << "Successfully parsed " << QSCRIPT_CONFIG << endl;
	} else {
		cerr << "there were errors in parsing configuration file" << QSCRIPT_CONFIG << endl;
		return 0;
	}
	cout << "qscript.config: values are : " << endl
		<< "NCURSES_INCLUDE_DIR: " << config_file_parser::NCURSES_INCLUDE_DIR << endl
		<< "NCURSES_LIB_DIR: " << config_file_parser::NCURSES_LIB_DIR << endl
		<< "NCURSES_LINK_LIBRARY_NAME: " << config_file_parser::NCURSES_LINK_LIBRARY_NAME << endl
		<< "PLATFORM: " << config_file_parser::PLATFORM << endl
		<< endl;
	if(config_file_parser::PLATFORM == "WINDOWS"
	   || config_file_parser::PLATFORM == "LINUX"
	   || config_file_parser::PLATFORM == "UNIX"
		){
	} else {
		cerr << "Unknown platform ... please set it to one of\
			LINUX, UNIX, WINDOWS ... exiting\n";
		exit(1);
	}

	return 1;
}

// ReadQScriptConfig would have already been called
// before this function is invoked - we work on that assumuption
void CompileGeneratedCode(const string & src_file_name)
{
	if(qscript_debug::DEBUG_qscript_parser)
		cerr << "ENTER qscript_parser::CompileGeneratedCode" << endl;

	/*
# You will need to modify the variable below
#QSCRIPT_HOME=/media/sda3/home/nxd/xtcc_sourceforge_copy/xtcc/xtcc/qscript/stubs/simple_compiler
# if you have setup everything under ../INSTALL_CUSTOM.readme the you will not need to change
#the variables below
# when running the generated exe you will need to use
# LD_LIBRARY_PATH=$(QSCRIPT_RUNTIME) ./test_script

QSCRIPT_RUNTIME=$(QSCRIPT_HOME)/lib
QSCRIPT_INCLUDE_DIR=$(QSCRIPT_HOME)/include

test_script: test_script.o
	$(CXX) -g -o $@ -L$(QSCRIPT_RUNTIME) test_script.o -lqscript_runtime -lreadline

test_script.o: test_script.C
	$(CXX) -I$(QSCRIPT_INCLUDE_DIR) -g -c $<
	*/
	string executable_file_name = ExtractBaseFileName(src_file_name);
	string intermediate_file_name = executable_file_name + ".C";
	executable_file_name += "-wq2.exe";
	//string QSCRIPT_HOME = getenv("QSCRIPT_HOME");
	string QSCRIPT_HOME = program_options_ns::QSCRIPT_HOME;
	cout << "QSCRIPT_HOME: " << QSCRIPT_HOME << endl;
	string QSCRIPT_RUNTIME = QSCRIPT_HOME + "/lib";
	cout << "QSCRIPT_RUNTIME: " << QSCRIPT_RUNTIME << endl;

	string QSCRIPT_INCLUDE_DIR = QSCRIPT_HOME + "/include_wq2";
	string cpp_compile_command ;
	if (program_options_ns::ncurses_flag) {
		cpp_compile_command = string("g++ -g -o ")
			+ executable_file_name + string(" -L") + QSCRIPT_RUNTIME
			+ string(" -I") + QSCRIPT_INCLUDE_DIR
			+ string(" -I") + config_file_parser::NCURSES_INCLUDE_DIR
			+ string(" -L") + config_file_parser::NCURSES_LIB_DIR
			+ string(" ") + intermediate_file_name
			+ string(" -lqscript_runtime_wq2 -lpanel -lwt -lboost_filesystem ")
			+ string(" -l") + config_file_parser::NCURSES_LINK_LIBRARY_NAME;
	} else if (program_options_ns::microhttpd_flag) {
		cpp_compile_command = string("g++ -g -o ")
			+ executable_file_name + string(" -L") + QSCRIPT_RUNTIME
			+ string(" -I") + QSCRIPT_INCLUDE_DIR
			+ string(" -I") + config_file_parser::NCURSES_INCLUDE_DIR
			+ string(" -L") + config_file_parser::NCURSES_LIB_DIR
			+ string(" ") + intermediate_file_name
#ifndef _WIN32
			+ string(" -lmicrohttpd -lpanel -lncurses -lqscript_runtime_wq2");
#else
			+ string(" -lmicrohttpd -lpdcurses -lqscript_runtime_wq2");
#endif /* _WIN32 */
	} else if (program_options_ns::wt_flag) {
		QSCRIPT_INCLUDE_DIR = QSCRIPT_HOME + "/runtime/cpp/common";
		string QSCRIPT_WT_INCLUDE_DIR = QSCRIPT_HOME + "/runtime/cpp/wt";
		QSCRIPT_RUNTIME = QSCRIPT_HOME + "/runtime/build/common";
		string WT_OBJ_FILE = QSCRIPT_HOME + "/runtime/build/wt/question_wt_runtime.o";
		cpp_compile_command = string("g++ -g -o ")
			+ executable_file_name
			+ string(" -L") + QSCRIPT_RUNTIME
			+ string(" -I") + QSCRIPT_INCLUDE_DIR
			+ string(" -I") + QSCRIPT_WT_INCLUDE_DIR
			+ string(" ") + intermediate_file_name
			+ string(" ") + WT_OBJ_FILE
			+ string(" -lwt -lwthttp -lqscript_runtime_common -lboost_signals ");
	} else if (program_options_ns::stdout_flag) {
		string QSCRIPT_RUNTIME = QSCRIPT_HOME + "/runtime";
		cpp_compile_command = string("g++ -g -o ")
			+ executable_file_name
			+ string(" -I") + QSCRIPT_RUNTIME + "/cpp/common "
			+ string(" -L") + QSCRIPT_RUNTIME + "/build/common "
			//+ string(" -I") + config_file_parser::NCURSES_INCLUDE_DIR
			//+ string(" -L") + config_file_parser::NCURSES_LIB_DIR
			+ string(" ") + intermediate_file_name
			+ string(" ") + QSCRIPT_RUNTIME + string("/build/stdout/question_stdout_runtime.o ")
			+ string(" -lqscript_runtime_common ")
			;
	} else if (program_options_ns::wx_flag) {
		string QSCRIPT_RUNTIME = QSCRIPT_HOME + "/runtime";
		cpp_compile_command = string("g++ -g -o ")
			+ executable_file_name
			+ string(" -I") + QSCRIPT_RUNTIME + "/cpp/common "
			+ string(" -L") + QSCRIPT_RUNTIME + "/build/common "
			//+ string(" ") + QSCRIPT_HOME + string("/src/question_wx2_runtime.C ")
			//+ string(" -I") + config_file_parser::NCURSES_INCLUDE_DIR
			//+ string(" -L") + config_file_parser::NCURSES_LIB_DIR
			+ string(" ") + intermediate_file_name
			+ string(" ") + QSCRIPT_RUNTIME + string("/build/wx/question_wx2_runtime.o ")
			+ string(" `wx-config --cppflags` ")
			+ string(" `wx-config --libs core,base,media` ")
			+ string(" -lqscript_runtime_common ")
			;
	}
	cout << "cpp_compile_command: " << cpp_compile_command << endl;
	//int32_t ret_val = 0;
	int32_t ret_val = system(cpp_compile_command.c_str());
	if(ret_val != 0){
		cerr << "Failed in compiling generated code : test_script.C ";
	} else {
		cout << endl;
		cout << "Generated executable. You can run it by\n shell_prompt> LD_LIBRARY_PATH=$QSCRIPT_HOME/lib ./"
			 <<  executable_file_name
			<< endl;
		cout << endl;
	}
}

void CompileGeneratedCodeEmscripten(const string & src_file_name)
{
	if (qscript_debug::DEBUG_qscript_parser) {
		cerr << "ENTER qscript_parser::" << __PRETTY_FUNCTION__ << endl;
	}
	string base_name = ExtractBaseFileName(src_file_name);
	string executable_file_name  = base_name;
	string intermediate_cpp_file_name = base_name + ".C";
	string intermediate_cpp_file_name2 = base_name + ".cpp";
	string intermediate_obj_file_name = executable_file_name + ".o";
	executable_file_name += ".html";
	string QSCRIPT_HOME = program_options_ns::QSCRIPT_HOME;
	string QSCRIPT_INCLUDE_DIR = QSCRIPT_HOME + "/runtime/cpp-emscripten";
	string QSCRIPT_EMSCRIPTEN_BUILD_DIR = QSCRIPT_HOME + "/runtime/emscript-build";

	string emscripten_mv_cmd =
		  "mv " + intermediate_cpp_file_name + string(" ") + intermediate_cpp_file_name2;
	int32_t ret_val = system(emscripten_mv_cmd.c_str());
	if (ret_val != 0)  {
		cerr << "unable to rename .C file to .cpp, emcc will fail if we can't do this"
			<< "exiting" << endl;
		exit(1);
	}

	string emscripten_cc_intermediate_file_cmd =
		  "emcc -Wunused-function -I" + QSCRIPT_INCLUDE_DIR
		//+ " -s ASM_JS=0 "
		+ " -s OUTLINING_LIMIT=20000 "
		+ " -s DISABLE_EXCEPTION_CATCHING=1 "
		+ " -s INLINING_LIMIT=50 "
		+ " -s TOTAL_MEMORY=33554432 "
		+ " -s TOTAL_STACK=10485760 "
		+ " -s RELOOPER_BUFFER_SIZE=41943040 "
		//+ " -s ALLOW_MEMORY_GROWTH=1  " 
		+ " -s EXPORTED_FUNCTIONS=\"['_called_from_the_dom','_callback_return_serial','_navigate_previous']\" "
		//+ " -O2 -c " + intermediate_cpp_file_name2 + string(" ")
		+ " -O2 -c " + intermediate_cpp_file_name2 + string(" ")
		;
	cout << "intermediate cpp_compile_command: " << endl << emscripten_cc_intermediate_file_cmd << endl;
	ret_val = system(emscripten_cc_intermediate_file_cmd.c_str());
	if (ret_val != 0) {
		cerr << "Failed in compiling intermediate cpp file to obj : " << intermediate_cpp_file_name
			<< endl;
		exit(1);
	}

	string output_shell_filename; 
	string sed_command;

	if (program_options_ns::browser_only_flag == false) {
		output_shell_filename = string("/tmp/") + string("shell-phonegap-dom-callback-") + project_name + ".html";
		sed_command = "sed \"s/JOB_NAME/" + project_name + "/\" " + QSCRIPT_INCLUDE_DIR + string("/shell-phonegap-dom-callback.html > ")
					+ output_shell_filename;
	} else {
		output_shell_filename = string("/tmp/") + string("shell-browser-dom-callback-") + project_name + ".html";
		sed_command = "sed \"s/JOB_NAME/" + project_name + "/\" " + QSCRIPT_INCLUDE_DIR + string("/shell-browser-dom-callback.html > ")
					+ output_shell_filename;
	}

	cout << "sed command: " << endl
		<< sed_command 
		<< endl;
	if (system (sed_command.c_str()) != 0) {
		cout << "sed command to create temp shell file failed ... exiting" << endl;
		exit(1);
	}


	cout << "output_shell_filename: " << output_shell_filename << endl;

	string emscripten_cc_cmd =
		//"emcc -Wunused-function  -o " + executable_file_name + string(" ")
		"emcc -Wunused-function --llvm-opts 1 --llvm-lto 1 -O2 -o " + executable_file_name + string(" ")
		+ string(" --shell-file ") 
		//+ QSCRIPT_INCLUDE_DIR + string("/shell-phonegap-dom-callback.html ")
		+ output_shell_filename + string(" ")
		+ " --js-library " + QSCRIPT_INCLUDE_DIR + "/dom_manip_funcs.js "
		+ " -s OUTLINING_LIMIT=20000 "
		+ " -s DISABLE_EXCEPTION_CATCHING=1 "
		//+ " -s ASM_JS=0 "
		+ " -s INLINING_LIMIT=50 "
		+ " -s TOTAL_MEMORY=33554432 "
		+ " -s TOTAL_STACK=10485760 "
		+ " -s RELOOPER_BUFFER_SIZE=41943040 "
		//+ " -s ALLOW_MEMORY_GROWTH=1  " 
		+ "-s EXPORTED_FUNCTIONS=\"['_called_from_the_dom','_main','_callback_return_serial','_navigate_previous']\" ";
	string obj_files_list = 
		  QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/AbstractQuestionnaire.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/data_entry.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/log_mesg.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/named_attributes.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/named_range.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/qscript_data.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/qscript_debug.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/qscript_lib.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/qscript_parser_common.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/QuestionAttributes.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/question_common.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/question_logic.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/question_runtime.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/read_disk_data.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/scan_data.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/utils_common.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/xtcc_set.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/question_stdout_runtime.o "
		//+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/json.o "
		+ QSCRIPT_EMSCRIPTEN_BUILD_DIR + "/stub_pair.o "
		+ intermediate_obj_file_name + string(" ")
		;
	emscripten_cc_cmd += obj_files_list;
	cout << "cpp_compile_command: " << emscripten_cc_cmd << endl;
	ret_val = system(emscripten_cc_cmd.c_str());
	if (ret_val != 0) {
		cerr << "Failed in compiling generated code : test_script.C ";
	} else {
		cout << "Generated executable. You can run it by\n shell_prompt> LD_LIBRARY_PATH=$QSCRIPT_HOME/lib ./"
			<<  executable_file_name
			<< endl;
	}

}

void CompileGeneratedCodeStatic(const string & src_file_name)
{
	cerr << "ENTER qscript_parser::CompileGeneratedCodeStatic" << endl;

	/*
# You will need to modify the variable below
#QSCRIPT_HOME=/media/sda3/home/nxd/xtcc_sourceforge_copy/xtcc/xtcc/qscript/stubs/simple_compiler
# if you have setup everything under ../INSTALL_CUSTOM.readme the you will not need to change
#the variables below
# when running the generated exe you will need to use
# LD_LIBRARY_PATH=$(QSCRIPT_RUNTIME) ./test_script

QSCRIPT_RUNTIME=$(QSCRIPT_HOME)/lib
QSCRIPT_INCLUDE_DIR=$(QSCRIPT_HOME)/include

test_script: test_script.o
	$(CXX) -g -o $@ -L$(QSCRIPT_RUNTIME) test_script.o -lqscript_runtime -lreadline

test_script.o: test_script.C
	$(CXX) -I$(QSCRIPT_INCLUDE_DIR) -g -c $<
	*/
	string executable_file_name = ExtractBaseFileName(src_file_name);
	string intermediate_file_name = executable_file_name + ".C";
	executable_file_name += "-wq2.exe";
	//string QSCRIPT_HOME = getenv("QSCRIPT_HOME");
	string QSCRIPT_HOME = program_options_ns::QSCRIPT_HOME;
	string::size_type contains_space = QSCRIPT_HOME.find_last_of(" ");
	if (contains_space != string::npos) {
		QSCRIPT_HOME.erase(contains_space);
	}
	cout << "QSCRIPT_HOME: " << QSCRIPT_HOME << endl;
	string QSCRIPT_RUNTIME = QSCRIPT_HOME + "/lib";
	cout << "QSCRIPT_RUNTIME: " << QSCRIPT_RUNTIME << endl;
	/*
	string QSCRIPT_INCLUDE_DIR = QSCRIPT_HOME + "/include";
	string cpp_compile_command = string("c:\\MinGW\\bin\\g++ -static -g -o ")
				+ executable_file_name
				+ string(" -L") + QSCRIPT_RUNTIME
				+ string(" -L") + QSCRIPT_CURSES_LIB_DIR
				+ string(" -I") + QSCRIPT_INCLUDE_DIR
				+ string(" -I") + QSCRIPT_CURSES_INCLUDE_DIR
				+ string(" ") + intermediate_file_name
				+ string(" -lqscript_runtime -lpdcurses ");
	*/

	string QSCRIPT_INCLUDE_DIR = QSCRIPT_HOME + "/include_wq2";
	string cpp_compile_command = string("g++ -static -g -o ")
			+ executable_file_name + string(" -L") + QSCRIPT_RUNTIME
			+ string(" -I") + QSCRIPT_INCLUDE_DIR
			+ string(" -I") + config_file_parser::NCURSES_INCLUDE_DIR
			+ string(" -L") + config_file_parser::NCURSES_LIB_DIR
			+ string(" ") + intermediate_file_name
			+ string(" -lqscript_runtime_wq2 ")
			+ string(" -l") + config_file_parser::NCURSES_LINK_LIBRARY_NAME;

	cout << "cpp_compile_command: " << cpp_compile_command << endl;
	//int32_t ret_val = 0;
	int32_t ret_val = system(cpp_compile_command.c_str());
	if(ret_val != 0){
		cerr << "Failed in compiling generated code : test_script.C ";
	} else {
		cout << "Generated executable. You can run it by\n shell_prompt> LD_LIBRARY_PATH=$QSCRIPT_HOME/lib ./"
			 <<  executable_file_name
			<< endl;
	}
}

void PrintDefineSomePDCursesKeys(FILE * script)
{
	fprintf(script, "void define_some_pd_curses_keys()\n");
	fprintf(script, "{\n\
			string ctrl_left_arrow;\n\
			ctrl_left_arrow.append(1, 27);\n\
			ctrl_left_arrow.append(1, 91);\n\
			ctrl_left_arrow.append(1, 49);\n\
			ctrl_left_arrow.append(1, 59);\n\
			ctrl_left_arrow.append(1, 53);\n\
			ctrl_left_arrow.append(1, 68);\n\
			\n\
			string ctrl_right_arrow;\n\
			ctrl_right_arrow.append(1, 27);\n\
			ctrl_right_arrow.append(1, 91);\n\
			ctrl_right_arrow.append(1, 49);\n\
			ctrl_right_arrow.append(1, 59);\n\
			ctrl_right_arrow.append(1, 53);\n\
			ctrl_right_arrow.append(1, 67);\n\
			string ctl_del;\n\
			ctl_del.append(1, 27);\n\
			ctl_del.append(1, 91);\n\
			ctl_del.append(1, 51);\n\
			ctl_del.append(1, 59);\n\
			ctl_del.append(1, 53);\n\
			ctl_del.append(1, 126);\n\
			string alt_del;\n\
			alt_del.append(1, 27);\n\
			alt_del.append(1, 91);\n\
			alt_del.append(1, 51);\n\
			alt_del.append(1, 59);\n\
			alt_del.append(1, 51);\n\
			alt_del.append(1, 126);\n\
			\n\
			string shift_del;\n\
			shift_del.append(1, 27);\n\
			shift_del.append(1, 91);\n\
			shift_del.append(1, 51);\n\
			shift_del.append(1, 59);\n\
			shift_del.append(1, 50);\n\
			shift_del.append(1, 126);\n\
			define_key(ctrl_left_arrow.c_str(), CTL_LEFT);\n\
			define_key(ctrl_right_arrow.c_str(), CTL_RIGHT);\n\
			define_key(ctl_del.c_str(), CTL_DEL);\n\
			define_key(alt_del.c_str(), ALT_DEL);\n\
			define_key(shift_del.c_str(), SHF_DC);\n\
		}\n");
}

void PrintPDCursesKeysHeader(FILE * script)
{
	fprintf(script, "\
			#ifndef a_few_pd_curses_keys_h\n\
			#define a_few_pd_curses_keys_h\n\
			#define CTL_LEFT 	0x1bb\n\
			#define CTL_RIGHT 	0x1bc\n\
			#define CTL_DEL 	0x20f\n\
			#define ALT_DEL 	0x1de\n\
			#undef KEY_SDC /* redefined as per PD curses below */\n\
			#define SHF_DC 		0x21a\n\
			#endif /* a_few_pd_curses_keys_h */\n\
			");
}

void PrintProcessOptions(FILE * script)
{
	fprintf(script, "int process_options(int argc, char * argv[])\n");
	fprintf(script, "{\n");
	fprintf(script, "	//int32_t opterr=1, c;\n");
	fprintf(script, "	std::cout << __PRETTY_FUNCTION__ << std::endl;\n");
	fprintf(script, "	extern int32_t optind, opterr, optopt;\n");
	fprintf(script, "	extern char * optarg;\n");
	fprintf(script, "	int c;\n");
	fprintf(script, "	while ( (c = getopt(argc, argv, \"mx::w::q::\")) != -1) {\n");
	fprintf(script, "		char ch = optopt;\n");
	fprintf(script, "		switch (c) {\n");

	fprintf(script, "		case 'w': {\n");
	fprintf(script, "			  write_data_file_flag = true;\n");
	fprintf(script, "			  if (optarg) {\n");
	fprintf(script, "				  output_data_file_name = optarg;\n");
	fprintf(script, "			  } else {\n");
	fprintf(script, "				  output_data_file_name = \"datafile.dat\";\n");
	fprintf(script, "			  }\n");
	fprintf(script, "		}\n");
	fprintf(script, "		break;\n");


	fprintf(script, "		case 'x': {\n");
	fprintf(script, "			  write_xtcc_data_file_flag = true;\n");
	fprintf(script, "			  if (optarg) {\n");
	fprintf(script, "				  output_xtcc_data_file_name = optarg;\n");
	fprintf(script, "			  } else {\n");
	fprintf(script, "				  output_xtcc_data_file_name = \"xtcc_datafile.dat\";\n");
	fprintf(script, "			  }\n");
	fprintf(script, "		}\n");
	fprintf(script, "		break;\n");

	fprintf(script, "		case 'q': {\n");
	fprintf(script, "			  write_qtm_data_file_flag = true;\n");
	fprintf(script, "			  if (optarg) {\n");
	fprintf(script, "				  output_qtm_data_file_name = optarg;\n");
	fprintf(script, "			  } else {\n");
	fprintf(script, "				  output_qtm_data_file_name = \"qtm_datafile.dat\";\n");
	fprintf(script, "			  }\n");
	fprintf(script, "		}\n");
	fprintf(script, "		break;\n");

	fprintf(script, "		case 'm': {\n");
	fprintf(script, "			  write_messages_flag = true;\n");
	fprintf(script, "		}\n");
	fprintf(script, "		break;\n");

	fprintf(script, "		case '?' : {\n");
	fprintf(script, "				   cout << \" invalid option, optopt:\" << optopt << endl;\n");
	fprintf(script, "				   exit(1);\n");
	fprintf(script, "			   }\n");
	fprintf(script, "			  break;\n");
	fprintf(script, "		default:\n");
	fprintf(script, "			  cerr << \"invalid options: ch: \" << ch << \", c: \" << c << endl;\n");
	fprintf(script, "		}\n");
	fprintf(script, "	}\n");
	fprintf(script, "	cout << \"output_data_file_name: \" << output_data_file_name << endl;\n");
	fprintf(script, "	cout << \"write_data_file_flag: \" << write_data_file_flag << endl;\n");
	fprintf(script, "	cout << \"output_qtm_data_file_name: \" << output_qtm_data_file_name << endl;\n");
	fprintf(script, "	cout << \"write_qtm_data_file_flag: \" << write_qtm_data_file_flag << endl;\n");
	fprintf(script, "	//exit(1);\n");
	fprintf(script, "}\n");
}

void PrintPrintMapHeader(FILE * script)
{
	fprintf(script, "\tvoid print_map_header(fstream & map_file )\n{\n");
	fprintf(script, "map_file << \"Question No\t\t\t,width,\tno responses,\tstart position,\tend position\\n\";\n");
	fprintf(script, "}\n");
}

void PrintWxSupport_1 (FILE * script)
{
	fprintf (script, "struct TheQuestionnaire * make_questionnaire ()\n");
	fprintf (script, "{\n");
	fprintf (script, "	TheQuestionnaire * theQuestionnaire = new TheQuestionnaire (jno);\n");
	fprintf (script, "	theQuestionnaire->base_text_vec.push_back(BaseText(\"All Respondents\"));\n");
	fprintf (script, "	return theQuestionnaire;\n");
	fprintf (script, "}\n");
}

void PrintStdoutMain (FILE * script)
{
	fprintf (script, "\nint callback_get_ser_no_from_ui (int p_ser_no);\n");
	fprintf (script, "int32_t main(int argc, char * argv[])\n");
	fprintf (script, "{\n");
	fprintf (script, "	process_options(argc, argv);\n");
	fprintf (script, "	if (write_data_file_flag||write_qtm_data_file_flag||write_xtcc_data_file_flag)\n");
	fprintf (script, "	{\n");
	fprintf (script, "		qtm_data_file_ns::init();\n");
	fprintf (script, "		qtm_data_file_ns::init_exceptions();\n");
	fprintf (script, "		directory_ptr = opendir(\".\");\n");
	fprintf (script, "		if (! directory_ptr)\n");
	fprintf (script, "		{\n");
	fprintf (script, "			cout << \" unable to open . (current directory) for reading\\n\";\n");
	fprintf (script, "			exit(1);\n");
	fprintf (script, "		}\n");
	fprintf (script, "	}\n");
	fprintf (script, "	bool using_ncurses = true;\n");
	fprintf (script, "	qscript_stdout = fopen(qscript_stdout_fname.c_str(), \"w\");\n");
	fprintf (script, "	using namespace std;\n");
	fprintf (script, "	SetupSignalHandler();\n");
	fprintf (script, "	setup_ui (argc, argv);\n");
	fprintf (script, "	prompt_user_for_serial_no (callback_get_ser_no_from_ui);\n");
	fprintf (script, "\n");
	fprintf (script, "} /* close main */\n");
	fprintf (script, "\n");
}

void PrintNCursesMain (FILE * script, bool ncurses_flag)
{

	fprintf (script, "enum EvalMode { USER_NAVIGATION, NORMAL_FLOW };\n\n");






	fprintf (script, "void outer_question_eval_loop (EvalMode qnre_mode, UserNavigation navg, AbstractQuestion * last_question_visited, AbstractQuestion* jump_to_question, TheQuestionnaire * qnre);\n\n");

	fprintf(script, "int32_t main(int argc, char * argv[]){\n");
	fprintf(script, "\tprocess_options(argc, argv);\n");
	//fprintf(script, "\tDIR * directory_ptr = 0;\n");
	fprintf(script, "\tif (write_data_file_flag||write_qtm_data_file_flag||write_xtcc_data_file_flag) {\n");
	fprintf(script, "\t	qtm_data_file_ns::init();\n");
	fprintf(script, "\t	qtm_data_file_ns::init_exceptions();\n");
	fprintf(script, "\t	directory_ptr = opendir(\".\");\n");
	fprintf(script, "\t	if (! directory_ptr) {\n");
	fprintf(script, "\t		cout << \" unable to open . (current directory) for reading\\n\";\n");
	fprintf(script, "\t		exit(1);\n");
	fprintf(script, "\t	}\n");
	fprintf(script, "\t}\n");
	fprintf(script, "bool using_ncurses = %s;\n", (ncurses_flag) ?  "true": "false");
	fprintf(script, "qscript_stdout = fopen(qscript_stdout_fname.c_str(), \"w\");\n");
	fprintf(script, "	using namespace std;\n");

	/*
	fprintf(script, "	WINDOW 	* question_window = 0,\n"
			"		* stub_list_window = 0,\n"
			"		* data_entry_window = 0,\n"
			"		* help_window = 0;\n"
			);
	fprintf(script, "	PANEL 	* question_panel = 0,\n"
			"		* stub_list_panel = 0,\n"
			"		* data_entry_panel = 0,\n"
			"		* help_panel = 0;\n");
	*/

	if(ncurses_flag) {
		// this is not necessary any more
		//fprintf(script, "	SetupNCurses(question_window, stub_list_window, data_entry_window, help_window, question_panel, stub_list_panel, data_entry_panel, help_panel);\n");
		//fprintf(script, "	if(question_window == 0 || stub_list_window == 0 || data_entry_window == 0\n\t\t /* || help_window == 0 */\n\t\t ){\n");
		//fprintf(script, "		cerr << \"Unable to create windows ... exiting\" << endl;\n");
		//fprintf(script, "		return 1;\n");
		//fprintf(script, "	}\n");
		fprintf (script, "setup_ui();\n");

	}
	fprintf(script, "	SetupSignalHandler();\n");
	fprintf(script, "TheQuestionnaire * theQuestionnaire = new TheQuestionnaire (jno);\n"
			"theQuestionnaire->base_text_vec.push_back(BaseText(\"All Respondents\"));\n"
			"theQuestionnaire->compute_flat_file_map_and_init();\n"
			"UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;\n\n"
			"AbstractQuestion * last_question_visited = 0;\n"
			"AbstractQuestion * jump_to_question = 0;\n"
			"EvalMode qnre_mode = NORMAL_FLOW;\n"
			"\n"
			"outer_question_eval_loop (qnre_mode, qnre_navigation_mode, last_question_visited, jump_to_question, theQuestionnaire);\n"
			);
	/*
	if(ncurses_flag) {
		fprintf(script, "\tif (!(write_data_file_flag|| write_qtm_data_file_flag)) {\n");
		fprintf(script, "\t\tint n_printed = mvwprintw(data_entry_window, 1, 1, \"Enter Serial No (0) to exit: \");\n");
		fprintf(script, "\t\tmvwscanw(data_entry_window, 1, 40, \"%%d\", & ser_no);\n");
		fprintf(script, "\t}\n");
	} else	{
		fprintf(script, "\tif (!(write_data_file_flag|| write_qtm_data_file_flag)) {\n");
		fprintf(script, "\t\tcout << \"Enter Serial No (0) to exit: \" << flush;\n");
		fprintf(script, "\t\tchar  newl; cin >> ser_no;cin.get(newl);\n");
		fprintf(script, "\t}\n");
	}
	*/

#if 0
	fprintf(script, "#if 0\n");
	fprintf(script, "	do {\n");
	fprintf(script, "		theQuestionnaire.reset_questionnaire();\n");
	fprintf(script, "		if (write_data_file_flag||write_qtm_data_file_flag)\n");
	fprintf(script, "		{\n");
	fprintf(script, "			theQuestionnaire.ser_no = theQuestionnaire.read_a_serial_no();\n");
	fprintf(script, "			if (theQuestionnaire.ser_no == 0)\n");
	fprintf(script, "			{\n");
	fprintf(script, "				exit(1);\n");
	fprintf(script, "			}\n");
	fprintf(script, "		}\n");
	fprintf(script, "		else\n");
	fprintf(script, "		{\n");
	fprintf(script, "			theQuestionnaire.prompt_user_for_serial_no();\n");
	fprintf(script, "			if (theQuestionnaire.ser_no == 0)\n");
	fprintf(script, "			{\n");
	fprintf(script, "				break;\n");
	fprintf(script, "			}\n");
	fprintf(script, "			int exists = check_if_reg_file_exists(theQuestionnaire.jno, theQuestionnaire.ser_no);\n");
	fprintf(script, "			if(exists == 1)\n");
	fprintf(script, "			{\n");
	fprintf(script, " 				map <string, question_disk_data*>  qdd_map;\n");
	fprintf(script, "				load_data (theQuestionnaire.jno, theQuestionnaire.ser_no, &qdd_map);\n");
	fprintf(script, "				merge_disk_data_into_questions2(qscript_stdout, theQuestionnaire.last_question_answered, theQuestionnaire.last_question_visited, theQuestionnaire.question_list, &qdd_map);\n");
	fprintf(script, "			}\n");
	fprintf(script, "		}\n");
	fprintf(script, "\n");


	fprintf(script, "\twhile(theQuestionnaire.ser_no != 0 || (write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)){\n");
	fprintf(script, "\t\tfprintf(qscript_stdout, \"reached top of while loop:\\n\");");
	fprintf(script, "\t\t      re_eval_from_start:\n");
	fprintf(script, "\t\t	AbstractQuestion * q =\n");
	fprintf(script, "\t\t	    theQuestionnaire.eval2 ( /*last_question_answered, last_question_visited, */ \n");
	fprintf(script, "\t\t				   qnre_navigation_mode);\n");

	fprintf(script, "\t		if (!q) {\n");
	fprintf(script, "\t			if (write_data_file_flag) {\n");
	fprintf(script, "\t				theQuestionnaire.write_ascii_data_to_disk();\n");
	fprintf(script, "\t			} else if (write_qtm_data_file_flag) {\n");
	fprintf(script, "\t				theQuestionnaire.write_qtm_data_to_disk();\n");
	fprintf(script, "\t			} else {\n");
	fprintf(script, "\t				char end_of_question_navigation;\n");
	fprintf(script, "\t				label_end_of_qnre_navigation:\n");
	fprintf(script, "\t				wclear(data_entry_window);\n");
	fprintf(script, "\t				mvwprintw(data_entry_window, 1, 1,\"End of Questionnaire: ((s)ave, (p)revious question, question (j)ump list)\");\n");
	fprintf(script, "\t				mvwscanw(data_entry_window, 1, 75, \"%%c\", & end_of_question_navigation);\n");
	fprintf(script, "\t				if(end_of_question_navigation == 's') {\n");
	fprintf(script, "\t					theQuestionnaire.write_data_to_disk(theQuestionnaire.question_list, theQuestionnaire.jno, theQuestionnaire.ser_no);\n");
	fprintf(script, "\t				} else if (end_of_question_navigation == 'p') {\n");
	fprintf(script, "\t					AbstractQuestion * target_question = theQuestionnaire.ComputePreviousQuestion(theQuestionnaire.last_question_answered);\n");
	fprintf(script, "\t					if(target_question->type_ == QUESTION_ARR_TYPE)\n");
	fprintf(script, "\t					{\n");
	fprintf(script, "\t						theQuestionnaire.jumpToIndex = theQuestionnaire.ComputeJumpToIndex(target_question);\n");
	fprintf(script, "\t					}\n");
	fprintf(script, "\t					theQuestionnaire.jumpToQuestion = target_question->questionName_;\n");
	fprintf(script, "\t					//if (data_entry_window == 0) cout << \"target question: \" << jumpToQuestion;\n");
	fprintf(script, "\t					theQuestionnaire.back_jump = true;\n");
	fprintf(script, "\t					user_navigation = NOT_SET;\n");
	fprintf(script, "\t					//goto start_of_questions;\n");
	fprintf(script, "\t					goto re_eval_from_start;\n");
	fprintf(script, "\t				} else if (end_of_question_navigation == 'j') {\n");
	fprintf(script, "\t					theQuestionnaire.DisplayActiveQuestions();\n");
	fprintf(script, "\t					theQuestionnaire.GetUserResponse(theQuestionnaire.jumpToQuestion, theQuestionnaire.jumpToIndex);\n");
	fprintf(script, "\t					user_navigation = NOT_SET;\n");
	fprintf(script, "\t					//goto start_of_questions;\n");
	fprintf(script, "\t					goto re_eval_from_start;\n");
	fprintf(script, "\t				} else if (end_of_question_navigation == 'q') {\n");
	fprintf(script, "\t					//theQuestionnaire.reset_questionnaire();\n");
	fprintf(script, "\t					break;\n");
	fprintf(script, "\t				} else {\n");
	fprintf(script, "\t					goto label_end_of_qnre_navigation;\n");
	fprintf(script, "\t				}\n");
	fprintf(script, "\t				// wclear(data_entry_window);\n");
	fprintf(script, "\t				// mvwprintw(data_entry_window, 1, 1, \"Enter Serial No (0) to exit: \");\n");
	fprintf(script, "\t				// mvwscanw(data_entry_window, 1, 40, \"%%d\", & ser_no);\n");
	fprintf(script, "\t				//theQuestionnaire.prompt_user_for_serial_no();\n");
	fprintf(script, "\t				//if (theQuestionnaire.ser_no ==0) break;\n");
	fprintf(script, "\t				break;\n");
	fprintf(script, "\t			}\n");
	fprintf(script, "\t		}\n");
	fprintf(script, "\t\t	else\n{\n");
	fprintf(script, "\t\t	fprintf(qscript_stdout, \"eval2 returned %%s\\n\",\n");
	fprintf(script, "\t\t		q->questionName_.c_str());\n");
	fprintf(script, "\t\t      re_eval:\n");
	fprintf(script, "\t\t	q->eval(question_window, stub_list_window, data_entry_window);\n");
	fprintf(script, "\t\t\n");
	fprintf(script, "\t\t	if (user_navigation == NAVIGATE_PREVIOUS) {\n");
	fprintf(script, "\t\t	    fprintf(qscript_stdout,\n");
	fprintf(script, "\t\t		    \"user_navigation == NAVIGATE_PREVIOUS\\n\");\n");
	fprintf(script, "\t\t	    AbstractQuestion *target_question =\n");
	fprintf(script, "\t\t		theQuestionnaire.ComputePreviousQuestion(q);\n");
	fprintf(script, "\t\t	    if (target_question == 0)\n");
	fprintf(script, "\t\t		goto re_eval;\n");
	fprintf(script, "\t\t	    else {\n");
	fprintf(script, "\t\t		theQuestionnaire.jumpToQuestion = target_question->questionName_;\n");
	fprintf(script, "\t\t		if (target_question->type_ == QUESTION_ARR_TYPE) {\n");
	fprintf(script, "\t\t		    theQuestionnaire.jumpToIndex =\n");
	fprintf(script, "\t\t			theQuestionnaire.\n");
	fprintf(script, "\t\t			ComputeJumpToIndex(target_question);\n");
	fprintf(script, "\t\t		}\n");
	fprintf(script, "\t\t		// if (data_entry_window == 0)\n");
	fprintf(script, "\t\t		//     cout << \"target question: \" << jumpToQuestion;\n");
	fprintf(script, "\t\t		// if (data_entry_window == 0)\n");
	fprintf(script, "\t\t		//     cout << \"target question Index: \" << theQuestionnaire.jumpToIndex;\n");
	fprintf(script, "\t\t		theQuestionnaire.back_jump = true;\n");
	fprintf(script, "\t\t		user_navigation = NOT_SET;\n");
	fprintf(script, "\t\t		//goto start_of_questions;\n");
	fprintf(script, "\t\t		goto re_eval_from_start;\n");
	fprintf(script, "\t\t	    }\n");
	fprintf(script, "\t\t	} else if (user_navigation == NAVIGATE_NEXT) {\n");
	fprintf(script, "\t\t	    fprintf(qscript_stdout, \"user_navigation == NAVIGATE_NEXT\\n\");\n");
	fprintf(script, "\t\t	    if (q->isAnswered_ == false\n");
	fprintf(script, "\t\t		&& q->question_attributes.isAllowBlank() == false) {\n");
	fprintf(script, "\t\t		fprintf(qscript_stdout,\n");
	fprintf(script, "\t\t			\"questionName_ %%s: going back to re_eval\\n\",\n");
	fprintf(script, "\t\t			q->questionName_.c_str());\n");
	fprintf(script, "\t\t		goto re_eval;\n");
	fprintf(script, "\t\t	    }\n");
	fprintf(script, "\t\t	    qnre_navigation_mode = NAVIGATE_NEXT;\n");
	fprintf(script, "\t\t	    // stopAtNextQuestion = true;\n");
	fprintf(script, "\t\t	    user_navigation = NOT_SET;\n");
	fprintf(script, "\t\t	} else if (user_navigation == JUMP_TO_QUESTION) {\n");
	fprintf(script, "\t\t	    theQuestionnaire.DisplayActiveQuestions();\n");
	fprintf(script, "\t\t	    theQuestionnaire.GetUserResponse(theQuestionnaire.jumpToQuestion, theQuestionnaire.jumpToIndex);\n");
	fprintf(script, "\t\t	    user_navigation = NOT_SET;\n");
	fprintf(script, "\t\t	    //goto start_of_questions;\n");
	fprintf(script, "\t\t	    goto re_eval_from_start;\n");
	fprintf(script, "\t\t	} else if (user_navigation == SAVE_DATA) {\n");
	fprintf(script, "\t\t	    theQuestionnaire.write_data_to_disk(theQuestionnaire.question_list, theQuestionnaire.jno,\n");
	fprintf(script, "\t\t						theQuestionnaire.ser_no);\n");
	fprintf(script, "\t\t	    if (data_entry_window)\n");
	fprintf(script, "\t\t		mvwprintw(data_entry_window, 2, 50, \"saved partial data\");\n");
	fprintf(script, "\t\t	    else\n");
	fprintf(script, "\t\t		cout << \"saved partial data\\n\";\n");
	fprintf(script, "\t\t	    if (q->isAnswered_ == false) {\n");
	fprintf(script, "\t\t		//goto label_eval_q2;\n");
	fprintf(script, "\t\t		goto re_eval;\n");
	fprintf(script, "\t\t	    }\n");
	fprintf(script, "\t\t	} else {\n");
	fprintf(script, "\t\t	    theQuestionnaire.last_question_answered = q;\n");
	fprintf(script, "\t\t	}\n");
	fprintf(script, "\t\t}\n");
	fprintf(script, "\t} /* close while */\n");
	fprintf(script, "} while(theQuestionnaire.ser_no != 0); /* close do */\n");
	fprintf(script, "#endif /*  0 */\n");
#endif /*  0 */


	if(ncurses_flag)
		fprintf(script, "\tendwin();\n");
	fprintf(script, "\n} /* close main */\n");


	fprintf (script, "void question_eval_loop (EvalMode qnre_mode,\n");
	fprintf (script, "UserNavigation qnre_navigation_mode, AbstractQuestion * last_question_visited,\n");
	fprintf (script, "AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire)\n");
	fprintf (script, "{\n");
	fprintf (script, "\n");
	fprintf (script, "	//while(theQuestionnaire->ser_no != 0 || (write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag))\n");
	fprintf (script, "	//{\n");
	fprintf (script, "	fprintf(qscript_stdout, \"reached top of while loop:\\n\");\n");
	fprintf (script, "re_eval_from_start:\n");
	fprintf (script, "	AbstractQuestion * q =\n");
	fprintf (script, "		theQuestionnaire->eval2 (\n");
	fprintf (script, "		qnre_navigation_mode, last_question_visited, jump_to_question);\n");
	fprintf (script, "	// Currently lets not worry about the data writing path\n");
	fprintf (script, "	// hence if we are in data writing mode - just exit with a message\n");
	fprintf (script, "	if (!q)\n");
	fprintf (script, "	{\n");
	fprintf (script, "		if (write_data_file_flag)\n");
	fprintf (script, "		{\n");
	fprintf (script, "			theQuestionnaire->write_ascii_data_to_disk();\n");
	fprintf (script, "			cerr << \"Not considering data writing path at the moment\" << endl;\n");
	fprintf (script, "			exit(1);\n");
	fprintf (script, "		}\n");
	fprintf (script, "		else if (write_qtm_data_file_flag)\n");
	fprintf (script, "		{\n");
	fprintf (script, "			theQuestionnaire->write_qtm_data_to_disk();\n");
	fprintf (script, "			cerr << \"Not considering data writing path at the moment\" << endl;\n");
	fprintf (script, "			exit(1);\n");
	fprintf (script, "		}\n");
	fprintf (script, "		else\n");
	fprintf (script, "		{\n");
	fprintf (script, "			//cerr << \"Not considering What happens when we reach end of qnre at the moment - just lets exit\" << endl;\n");
	fprintf (script, "			//exit(1);\n");
	fprintf (script, "			// thanks to the exit above - the code that follow is redundant in this block\n");
	fprintf (script, "			char end_of_question_navigation = get_end_of_question_response();\n");
	//fprintf (script, "label_end_of_qnre_navigation:\n");
	//fprintf (script, "			wclear(data_entry_window);\n");
	//fprintf (script, "			mvwprintw(data_entry_window, 1, 1,\"End of Questionnaire: ((s)ave, (p)revious question, question (j)ump list)\");\n");
	//fprintf (script, "			mvwscanw(data_entry_window, 1, 75, \"%%c\", & end_of_question_navigation);\n");
	fprintf (script, "			if(end_of_question_navigation == 's')\n");
	fprintf (script, "			{\n");
	fprintf (script, "				theQuestionnaire->write_data_to_disk(theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);\n");
	fprintf (script, "				return;\n");
	fprintf (script, "			}\n");
	fprintf (script, "			else if (end_of_question_navigation == 'p')\n");
	fprintf (script, "			{\n");
	fprintf (script, "				AbstractQuestion * target_question = theQuestionnaire->ComputePreviousQuestion(theQuestionnaire->last_question_answered);\n");
	fprintf (script, "				//if(target_question->type_ == QUESTION_ARR_TYPE)\n");
	fprintf (script, "				//{\n");
	fprintf (script, "				//	theQuestionnaire->jumpToIndex = theQuestionnaire->ComputeJumpToIndex(target_question);\n");
	fprintf (script, "				//}\n");
	fprintf (script, "				//theQuestionnaire->jumpToQuestion = target_question->questionName_;\n");
	fprintf (script, "				////if (data_entry_window == 0) cout << \"target question: \" << jumpToQuestion;\n");
	fprintf (script, "				//theQuestionnaire->back_jump = true;\n");
	fprintf (script, "				//user_navigation = NOT_SET;\n");
	fprintf (script, "				//goto start_of_questions;\n");
	fprintf (script, "				//goto re_eval_from_start;\n");
	fprintf (script, "				question_eval_loop (USER_NAVIGATION,\n");
	fprintf (script, "					NAVIGATE_PREVIOUS, /* last_question_visited */ q,\n");
	fprintf (script, "					/*  jump_to_question */ target_question, theQuestionnaire);\n");
	fprintf (script, "			}\n");
	fprintf (script, "			else if (end_of_question_navigation == 'j')\n");
	fprintf (script, "			{\n");
	fprintf (script, "				theQuestionnaire->DisplayActiveQuestions();\n");
	fprintf (script, "				GetUserResponse(theQuestionnaire->jumpToQuestion, theQuestionnaire->jumpToIndex);\n");
	fprintf (script, "				user_navigation = NOT_SET;\n");
	fprintf (script, "				//goto start_of_questions;\n");
	fprintf (script, "				//goto re_eval_from_start;\n");
	fprintf (script, "			}\n");
	fprintf (script, "			else if (end_of_question_navigation == 'q')\n");
	fprintf (script, "			{\n");
	fprintf (script, "				//change to break again when we remove the exit from above\n");
	fprintf (script, "				//break;\n");
	fprintf (script, "				//endwin();\n");
	fprintf (script, "				//exit(1);\n");
	fprintf (script, "				return;\n");
	fprintf (script, "			}\n");
	fprintf (script, "			else\n");
	fprintf (script, "			{\n");
	fprintf (script, "				//goto label_end_of_qnre_navigation;\n");
	fprintf (script, "			}\n");
	fprintf (script, "			// wclear(data_entry_window);\n");
	fprintf (script, "			// mvwprintw(data_entry_window, 1, 1, \"Enter Serial No (0) to exit: \");\n");
	fprintf (script, "			// mvwscanw(data_entry_window, 1, 40, \"%%d\", & ser_no);\n");
	fprintf (script, "			//theQuestionnaire.prompt_user_for_serial_no();\n");
	fprintf (script, "			//if (theQuestionnaire.ser_no ==0) break;\n");
	fprintf (script, "			//change to break again when we remove the exit from above\n");
	fprintf (script, "			//actually this should be un-reachable code\n");
	fprintf (script, "			//break;\n");
	fprintf (script, "			//\n");
	fprintf (script, "			exit(1);\n");
	fprintf (script, "		}\n");
	fprintf (script, "	}\n");
	fprintf (script, "	else\n");
	fprintf (script, "	{\n");
	fprintf (script, "		fprintf(qscript_stdout, \"eval2 returned %%s\\n\",\n");
	fprintf (script, "			q->questionName_.c_str());\n");
	fprintf (script, "re_eval:\n");
	fprintf (script, "		//q->eval(question_window, stub_list_window, data_entry_window);\n");
	fprintf (script, "		ncurses_eval (q);\n");
	fprintf (script, "\n");
	fprintf (script, "		if (user_navigation == NAVIGATE_PREVIOUS)\n");
	fprintf (script, "		{\n");
	fprintf (script, "			fprintf(qscript_stdout,\n");
	fprintf (script, "				\"user_navigation == NAVIGATE_PREVIOUS\\n\");\n");
	fprintf (script, "			AbstractQuestion *target_question =\n");
	fprintf (script, "				theQuestionnaire->ComputePreviousQuestion(q);\n");
	fprintf (script, "			if (target_question == 0) {\n");
	fprintf (script, "				//goto re_eval;\n");
	fprintf (script, "				//void question_eval_loop (EvalMode qnre_mode,\n");
	fprintf (script, "				//UserNavigation qnre_navigation_mode, AbstractQuestion * last_question_visited,\n");
	fprintf (script, "				//AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire)\n");
	fprintf (script, "				question_eval_loop (USER_NAVIGATION,\n");
	fprintf (script, "					NAVIGATE_PREVIOUS, /* last_question_visited */ q,\n");
	fprintf (script, "					/*  jump_to_question */ q, theQuestionnaire);\n");
	fprintf (script, "			} else {\n");
	fprintf (script, "				//theQuestionnaire->jumpToQuestion = target_question->questionName_;\n");
	fprintf (script, "				//if (target_question->type_ == QUESTION_ARR_TYPE)\n");
	fprintf (script, "				//{\n");
	fprintf (script, "				//	theQuestionnaire->jumpToIndex =\n");
	fprintf (script, "				//		theQuestionnaire->\n");
	fprintf (script, "				//		ComputeJumpToIndex(target_question);\n");
	fprintf (script, "				//}\n");
	fprintf (script, "				// if (data_entry_window == 0)\n");
	fprintf (script, "				//     cout << \"target question: \" << jumpToQuestion;\n");
	fprintf (script, "				// if (data_entry_window == 0)\n");
	fprintf (script, "				//     cout << \"target question Index: \" << theQuestionnaire.jumpToIndex;\n");
	fprintf (script, "				theQuestionnaire->back_jump = true;\n");
	fprintf (script, "				//user_navigation = NOT_SET;\n");
	fprintf (script, "				//goto start_of_questions;\n");
	fprintf (script, "				question_eval_loop (USER_NAVIGATION,\n");
	fprintf (script, "					NAVIGATE_PREVIOUS, /* last_question_visited */ q,\n");
	fprintf (script, "					/*  jump_to_question */ target_question, theQuestionnaire);\n");
	fprintf (script, "				//goto re_eval_from_start;\n");
	fprintf (script, "			}\n");
	fprintf (script, "		}\n");
	fprintf (script, "		else if (user_navigation == NAVIGATE_NEXT)\n");
	fprintf (script, "		{\n");
	fprintf (script, "			//fprintf(qscript_stdout, \"user_navigation == NAVIGATE_NEXT\\n\");\n");
	fprintf (script, "			//if (q->isAnswered_ == false\n");
	fprintf (script, "			//	&& q->question_attributes.isAllowBlank() == false)\n");
	fprintf (script, "			//{\n");
	fprintf (script, "			//	fprintf(qscript_stdout,\n");
	fprintf (script, "			//		\"questionName_ %%s: going back to re_eval\\n\",\n");
	fprintf (script, "			//		q->questionName_.c_str());\n");
	fprintf (script, "			//	goto re_eval;\n");
	fprintf (script, "			//}\n");
	fprintf (script, "			//qnre_navigation_mode = NAVIGATE_NEXT;\n");
	fprintf (script, "			// stopAtNextQuestion = true;\n");
	fprintf (script, "			//user_navigation = NOT_SET;\n");
	fprintf (script, "			question_eval_loop (USER_NAVIGATION,\n");
	fprintf (script, "				NAVIGATE_NEXT, /* last_question_visited */ q,\n");
	fprintf (script, "				/*  jump_to_question */ 0, theQuestionnaire);\n");
	fprintf (script, "		}\n");
	fprintf (script, "		else if (user_navigation == JUMP_TO_QUESTION)\n");
	fprintf (script, "		{\n");
	fprintf (script, "			theQuestionnaire->DisplayActiveQuestions();\n");
	fprintf (script, "			GetUserResponse(theQuestionnaire->jumpToQuestion, theQuestionnaire->jumpToIndex);\n");
	fprintf (script, "			user_navigation = NOT_SET;\n");
	fprintf (script, "			//goto start_of_questions;\n");
	fprintf (script, "			goto re_eval_from_start;\n");
	fprintf (script, "		}\n");
	fprintf (script, "		else if (user_navigation == SAVE_DATA)\n");
	fprintf (script, "		{\n");
	fprintf (script, "			theQuestionnaire->write_data_to_disk(theQuestionnaire->question_list, theQuestionnaire->jno,\n");
	fprintf (script, "				theQuestionnaire->ser_no);\n");
	fprintf (script, "			print_save_partial_data_message_success ();\n");
	//fprintf (script, "			if (data_entry_window)\n");
	//fprintf (script, "				mvwprintw(data_entry_window, 2, 50, \"saved partial data\");\n");
	//fprintf (script, "			else\n");
	//fprintf (script, "				cout << \"saved partial data\\n\";\n");
	fprintf (script, "			//if (q->isAnswered_ == false)\n");
	fprintf (script, "			//{\n");
	fprintf (script, "			//	//goto label_eval_q2;\n");
	fprintf (script, "			//	goto re_eval;\n");
	fprintf (script, "			//}\n");
	fprintf (script, "			question_eval_loop (NORMAL_FLOW,\n");
	fprintf (script, "				NAVIGATE_NEXT, /* last_question_visited */ q,\n");
	fprintf (script, "				/*  jump_to_question */ jump_to_question, theQuestionnaire);\n");
	fprintf (script, "		}\n");
	fprintf (script, "		else\n");
	fprintf (script, "		{\n");
	fprintf (script, "			theQuestionnaire->last_question_answered = q;\n");
	fprintf (script, "			question_eval_loop (NORMAL_FLOW,\n");
	fprintf (script, "				NAVIGATE_NEXT, /* last_question_visited */ q,\n");
	fprintf (script, "				/*  jump_to_question */ 0, theQuestionnaire);\n");
	fprintf (script, "		}\n");
	fprintf (script, "	}\n");
	fprintf (script, "	//}						 /* close while */\n");
	fprintf (script, "\n");
	fprintf (script, "\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");


	fprintf (script, "void outer_question_eval_loop (EvalMode qnre_mode,\n");
	fprintf (script, "		UserNavigation qnre_navigation_mode, AbstractQuestion * last_question_visited,\n");
	fprintf (script, "		AbstractQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire)\n");
	fprintf (script, "{\n");
	fprintf (script, "	do\n");
	fprintf (script, "	{\n");
	fprintf (script, "		theQuestionnaire->reset_questionnaire();\n");
	fprintf (script, "		if (write_data_file_flag||write_qtm_data_file_flag)\n");
	fprintf (script, "		{\n");
	fprintf (script, "			theQuestionnaire->ser_no = \n");
	fprintf (script, "				read_a_serial_no (directory_ptr, jno, theQuestionnaire);\n");
	fprintf (script, "			if (theQuestionnaire->ser_no == 0)\n");
	fprintf (script, "			{\n");
	fprintf (script, "				exit(1);\n");
	fprintf (script, "			}\n");
	fprintf (script, "		}\n");
	fprintf (script, "		else\n");
	fprintf (script, "		{\n");
	fprintf (script, "			theQuestionnaire->ser_no = prompt_user_for_serial_no();\n");
	fprintf (script, "			if (theQuestionnaire->ser_no == 0)\n");
	fprintf (script, "			{\n");
	fprintf (script, "				break;\n");
	fprintf (script, "			}\n");
	fprintf (script, "			int exists = check_if_reg_file_exists(theQuestionnaire->jno, theQuestionnaire->ser_no);\n");
	fprintf (script, "			if(exists == 1)\n");
	fprintf (script, "			{\n");
	fprintf (script, "				map <string, question_disk_data*>  qdd_map;\n");
	fprintf (script, "				load_data (theQuestionnaire->jno, theQuestionnaire->ser_no, &qdd_map);\n");
	fprintf (script, "				merge_disk_data_into_questions2(qscript_stdout, theQuestionnaire->last_question_answered, theQuestionnaire->last_question_visited, theQuestionnaire->question_list, &qdd_map);\n");
	fprintf (script, "			}\n");
	fprintf (script, "		}\n");
	fprintf (script, "\n");
	fprintf (script, "	question_eval_loop (qnre_mode,\n"
			 " 		qnre_navigation_mode, last_question_visited,\n"
			" 		jump_to_question, theQuestionnaire);\n\n");

#if 0
	fprintf (script, "#if 0\n");
	fprintf (script, "		while(theQuestionnaire->ser_no != 0 || (write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag))\n");
	fprintf (script, "		{\n");
	fprintf (script, "			fprintf(qscript_stdout, \"reached top of while loop:\\n\");              re_eval_from_start:\n");
	fprintf (script, "			AbstractQuestion * q =\n");
	fprintf (script, "				theQuestionnaire->eval2 (\n");
	fprintf (script, "				qnre_navigation_mode, last_question_visited, jump_to_question);\n");
	fprintf (script, "			if (!q)\n");
	fprintf (script, "			{\n");
	fprintf (script, "				if (write_data_file_flag)\n");
	fprintf (script, "				{\n");
	fprintf (script, "					theQuestionnaire->write_ascii_data_to_disk();\n");
	fprintf (script, "				}\n");
	fprintf (script, "				else if (write_qtm_data_file_flag)\n");
	fprintf (script, "				{\n");
	fprintf (script, "					theQuestionnaire->write_qtm_data_to_disk();\n");
	fprintf (script, "				}\n");
	fprintf (script, "				else\n");
	fprintf (script, "				{\n");
	fprintf (script, "					char end_of_question_navigation;\n");
	fprintf (script, "					label_end_of_qnre_navigation:\n");
	fprintf (script, "					wclear(data_entry_window);\n");
	fprintf (script, "					mvwprintw(data_entry_window, 1, 1,\"End of Questionnaire: ((s)ave, (p)revious question, question (j)ump list)\");\n");
	fprintf (script, "					mvwscanw(data_entry_window, 1, 75, \"%%c\", & end_of_question_navigation);\n");
	fprintf (script, "					if(end_of_question_navigation == 's')\n");
	fprintf (script, "					{\n");
	fprintf (script, "						theQuestionnaire->write_data_to_disk(theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);\n");
	fprintf (script, "					}\n");
	fprintf (script, "					else if (end_of_question_navigation == 'p')\n");
	fprintf (script, "					{\n");
	fprintf (script, "						AbstractQuestion * target_question = theQuestionnaire->ComputePreviousQuestion(theQuestionnaire->last_question_answered);\n");
	fprintf (script, "						if(target_question->type_ == QUESTION_ARR_TYPE)\n");
	fprintf (script, "						{\n");
	fprintf (script, "							theQuestionnaire->jumpToIndex = theQuestionnaire->ComputeJumpToIndex(target_question);\n");
	fprintf (script, "						}\n");
	fprintf (script, "						theQuestionnaire->jumpToQuestion = target_question->questionName_;\n");
	fprintf (script, "						//if (data_entry_window == 0) cout << \"target question: \" << jumpToQuestion;\n");
	fprintf (script, "						theQuestionnaire->back_jump = true;\n");
	fprintf (script, "						user_navigation = NOT_SET;\n");
	fprintf (script, "						//goto start_of_questions;\n");
	fprintf (script, "						goto re_eval_from_start;\n");
	fprintf (script, "					}\n");
	fprintf (script, "					else if (end_of_question_navigation == 'j')\n");
	fprintf (script, "					{\n");
	fprintf (script, "						theQuestionnaire->DisplayActiveQuestions();\n");
	fprintf (script, "						theQuestionnaire->GetUserResponse(theQuestionnaire->jumpToQuestion, theQuestionnaire->jumpToIndex);\n");
	fprintf (script, "						user_navigation = NOT_SET;\n");
	fprintf (script, "						//goto start_of_questions;\n");
	fprintf (script, "						goto re_eval_from_start;\n");
	fprintf (script, "					}\n");
	fprintf (script, "					else if (end_of_question_navigation == 'q')\n");
	fprintf (script, "					{\n");
	fprintf (script, "						//theQuestionnaire.reset_questionnaire();\n");
	fprintf (script, "						break;\n");
	fprintf (script, "					}\n");
	fprintf (script, "					else\n");
	fprintf (script, "					{\n");
	fprintf (script, "						goto label_end_of_qnre_navigation;\n");
	fprintf (script, "					}\n");
	fprintf (script, "					// wclear(data_entry_window);\n");
	fprintf (script, "					// mvwprintw(data_entry_window, 1, 1, \"Enter Serial No (0) to exit: \");\n");
	fprintf (script, "					// mvwscanw(data_entry_window, 1, 40, \"%%d\", & ser_no);\n");
	fprintf (script, "					//theQuestionnaire.prompt_user_for_serial_no();\n");
	fprintf (script, "					//if (theQuestionnaire.ser_no ==0) break;\n");
	fprintf (script, "					break;\n");
	fprintf (script, "				}\n");
	fprintf (script, "			}\n");
	fprintf (script, "			else\n");
	fprintf (script, "			{\n");
	fprintf (script, "				fprintf(qscript_stdout, \"eval2 returned %%s\\n\",\n");
	fprintf (script, "					q->questionName_.c_str());\n");
	fprintf (script, "				re_eval:\n");
	fprintf (script, "				q->eval(question_window, stub_list_window, data_entry_window);\n");
	fprintf (script, "\n");
	fprintf (script, "				if (user_navigation == NAVIGATE_PREVIOUS)\n");
	fprintf (script, "				{\n");
	fprintf (script, "					fprintf(qscript_stdout,\n");
	fprintf (script, "						\"user_navigation == NAVIGATE_PREVIOUS\\n\");\n");
	fprintf (script, "					AbstractQuestion *target_question =\n");
	fprintf (script, "						theQuestionnaire->ComputePreviousQuestion(q);\n");
	fprintf (script, "					if (target_question == 0)\n");
	fprintf (script, "						goto re_eval;\n");
	fprintf (script, "					else\n");
	fprintf (script, "					{\n");
	fprintf (script, "						theQuestionnaire->jumpToQuestion = target_question->questionName_;\n");
	fprintf (script, "						if (target_question->type_ == QUESTION_ARR_TYPE)\n");
	fprintf (script, "						{\n");
	fprintf (script, "							theQuestionnaire->jumpToIndex =\n");
	fprintf (script, "								theQuestionnaire->\n");
	fprintf (script, "								ComputeJumpToIndex(target_question);\n");
	fprintf (script, "						}\n");
	fprintf (script, "						// if (data_entry_window == 0)\n");
	fprintf (script, "						//     cout << \"target question: \" << jumpToQuestion;\n");
	fprintf (script, "						// if (data_entry_window == 0)\n");
	fprintf (script, "						//     cout << \"target question Index: \" << theQuestionnaire.jumpToIndex;\n");
	fprintf (script, "						theQuestionnaire->back_jump = true;\n");
	fprintf (script, "						user_navigation = NOT_SET;\n");
	fprintf (script, "						//goto start_of_questions;\n");
	fprintf (script, "						goto re_eval_from_start;\n");
	fprintf (script, "					}\n");
	fprintf (script, "				}\n");
	fprintf (script, "				else if (user_navigation == NAVIGATE_NEXT)\n");
	fprintf (script, "				{\n");
	fprintf (script, "					fprintf(qscript_stdout, \"user_navigation == NAVIGATE_NEXT\\n\");\n");
	fprintf (script, "					if (q->isAnswered_ == false\n");
	fprintf (script, "						&& q->question_attributes.isAllowBlank() == false)\n");
	fprintf (script, "					{\n");
	fprintf (script, "						fprintf(qscript_stdout,\n");
	fprintf (script, "							\"questionName_ %%s: going back to re_eval\\n\",\n");
	fprintf (script, "							q->questionName_.c_str());\n");
	fprintf (script, "						goto re_eval;\n");
	fprintf (script, "					}\n");
	fprintf (script, "					qnre_navigation_mode = NAVIGATE_NEXT;\n");
	fprintf (script, "					// stopAtNextQuestion = true;\n");
	fprintf (script, "					user_navigation = NOT_SET;\n");
	fprintf (script, "				}\n");
	fprintf (script, "				else if (user_navigation == JUMP_TO_QUESTION)\n");
	fprintf (script, "				{\n");
	fprintf (script, "					theQuestionnaire->DisplayActiveQuestions();\n");
	fprintf (script, "					theQuestionnaire->GetUserResponse(theQuestionnaire->jumpToQuestion, theQuestionnaire->jumpToIndex);\n");
	fprintf (script, "					user_navigation = NOT_SET;\n");
	fprintf (script, "					//goto start_of_questions;\n");
	fprintf (script, "					goto re_eval_from_start;\n");
	fprintf (script, "				}\n");
	fprintf (script, "				else if (user_navigation == SAVE_DATA)\n");
	fprintf (script, "				{\n");
	fprintf (script, "					theQuestionnaire->write_data_to_disk(theQuestionnaire->question_list, theQuestionnaire->jno,\n");
	fprintf (script, "						theQuestionnaire->ser_no);\n");
	fprintf (script, "					if (data_entry_window)\n");
	fprintf (script, "						mvwprintw(data_entry_window, 2, 50, \"saved partial data\");\n");
	fprintf (script, "					else\n");
	fprintf (script, "						cout << \"saved partial data\\n\";\n");
	fprintf (script, "					if (q->isAnswered_ == false)\n");
	fprintf (script, "					{\n");
	fprintf (script, "						//goto label_eval_q2;\n");
	fprintf (script, "						goto re_eval;\n");
	fprintf (script, "					}\n");
	fprintf (script, "				}\n");
	fprintf (script, "				else\n");
	fprintf (script, "				{\n");
	fprintf (script, "					theQuestionnaire->last_question_answered = q;\n");
	fprintf (script, "				}\n");
	fprintf (script, "			}\n");
	fprintf (script, "		}						 /* close while */\n");
	fprintf(script, "#endif /*  0 */\n");
#endif /*  0 */

	fprintf (script, "								 /* close do */\n");
	fprintf (script, "	} while(theQuestionnaire->ser_no != 0);\n");
	fprintf (script, "endwin();\n");
	fprintf (script, "\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");



}


void PrintMicrohttpdMain (FILE * script, bool ncurses_flag)
{
	fprintf (script, "int32_t main(int argc, char * argv[])\n");
	fprintf (script, "{\n");
	fprintf (script, "	process_options(argc, argv);\n");
	fprintf (script, "	if (write_data_file_flag||write_qtm_data_file_flag)\n");
	fprintf (script, "	{\n");
	fprintf (script, "		qtm_data_file_ns::init_exceptions();\n");
	fprintf (script, "		directory_ptr = opendir(\".\");\n");
	fprintf (script, "		if (! directory_ptr)\n");
	fprintf (script, "		{\n");
	fprintf (script, "			cout << \" unable to open . (current directory) for reading\\n\";\n");
	fprintf (script, "			exit(1);\n");
	fprintf (script, "		}\n");
	fprintf (script, "	}\n");
	fprintf (script, "	bool using_ncurses = true;\n");
	fprintf (script, "	qscript_stdout = fopen(qscript_stdout_fname.c_str(), \"w\");\n");
	fprintf (script, "	using namespace std;\n");
	fprintf (script, "	SetupSignalHandler();\n");
	fprintf (script, "	setup_and_run_MHD_daemon();\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");
}

void PrintComputeFlatFileMap(StatementCompiledCode & compute_flat_map_code)
{
	compute_flat_map_code.program_code << "void compute_flat_file_map_and_init()\n{\n";
	compute_flat_map_code.program_code
		<< "if (write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)\n"
		<< "{\n"
		<< "\tint current_map_pos = 0;\n"
		<< "\tint current_xtcc_map_pos = 0;\n";
	compute_flat_map_code.program_code << "\tif (write_qtm_data_file_flag) {\n"
		<< "\t\tqtm_datafile_conf_parser_ns::load_config_file(jno);\n"
		<< "\t\tqtm_data_file.Initialize();\n"
		<< "\t}\n";

	compute_flat_map_code.program_code << "\tif (write_data_file_flag) {\n";
	compute_flat_map_code.program_code << "		stringstream asc_datafile_conf_str;\n";
	compute_flat_map_code.program_code << "		asc_datafile_conf_str << jno\n";
	compute_flat_map_code.program_code << "			<< \".asc_data.conf\";\n";
	compute_flat_map_code.program_code << "		fstream asc_datafile_conf(asc_datafile_conf_str.str().c_str(), ios_base::in);\n";
	compute_flat_map_code.program_code << "		if (!asc_datafile_conf) {\n";
	compute_flat_map_code.program_code << "			cerr << \" could not open : \" << asc_datafile_conf_str.str()\n";
	compute_flat_map_code.program_code << "				<< \" for reading\" << endl;\n";
	compute_flat_map_code.program_code << "			exit(1);\n";
	compute_flat_map_code.program_code << "		}\n";
	compute_flat_map_code.program_code << "		string ser_no_token; string equal_token; ser_no_pos=-1; string semi_colon_token;\n";
	compute_flat_map_code.program_code << "		asc_datafile_conf >> ser_no_token;\n";
	compute_flat_map_code.program_code << "		if ( ser_no_token != string(\"SER_NO_COLS\")) {\n";
	compute_flat_map_code.program_code << "			cerr << \"expected token SER_NO_COLS\" << endl;\n";
	compute_flat_map_code.program_code << "			exit(1);\n";
	compute_flat_map_code.program_code << "		}\n";
	compute_flat_map_code.program_code << "		asc_datafile_conf >> equal_token;\n";

	compute_flat_map_code.program_code << "		if (equal_token != string(\"=\") ) {\n";
	compute_flat_map_code.program_code << "			cerr << \"expected token =\" << endl;\n";
	compute_flat_map_code.program_code << "			exit(1);\n";
	compute_flat_map_code.program_code << "		}\n";
	compute_flat_map_code.program_code << "		asc_datafile_conf >> ser_no_pos;\n";
	compute_flat_map_code.program_code << "		if (ser_no_pos == -1) {\n";
	compute_flat_map_code.program_code << "			cerr << \"invalid no of positions reserved for serial no: \";\n";
	compute_flat_map_code.program_code << "			exit(1);\n";
	compute_flat_map_code.program_code << "		}\n";
	compute_flat_map_code.program_code << "		current_map_pos += (ser_no_pos-1);\n";
	compute_flat_map_code.program_code << "	}\n";

	compute_flat_map_code.program_code << "\tif (write_xtcc_data_file_flag) {\n";
	compute_flat_map_code.program_code << "\t\tcurrent_xtcc_map_pos += 4; // serial no is 4 bytes fixed\n";
	compute_flat_map_code.program_code << "\t}\n";


	tree_root->Generate_ComputeFlatFileMap(compute_flat_map_code);

	compute_flat_map_code.program_code << "\tstring map_file_name(jno + string(\".map\"));\n";
	compute_flat_map_code.program_code << "\tfstream map_file(map_file_name.c_str(), ios_base::out|ios_base::ate);\n";
	compute_flat_map_code.program_code << "\t print_map_header(map_file);\n";
	compute_flat_map_code.program_code << "\tfor (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {\n"
		<< "\t\tascii_flatfile_question_disk_map[i]->print_map(map_file);\n"
		<< "\t}\n";
	print_write_spss_file_for_ascii_data_to_disk(compute_flat_map_code);
	compute_flat_map_code.program_code << "\tstring xtcc_map_file_name(jno + string(\".xmap\"));\n";
	compute_flat_map_code.program_code << "\tfstream xtcc_map_file(xtcc_map_file_name.c_str(), ios_base::out|ios_base::ate);\n";
	compute_flat_map_code.program_code << "\tprint_map_header(xtcc_map_file);\n";
	compute_flat_map_code.program_code
		<< "\tfor (int i=0; i<xtcc_question_disk_map.size(); ++i) {\n"
		<< "\t\txtcc_question_disk_map[i]->print_map(xtcc_map_file);\n"
		<< "\t}\n";

	compute_flat_map_code.program_code << "\tlen_flat_file_output_buffer = current_map_pos+1;\n";
	compute_flat_map_code.program_code << "\tlen_xtcc_datafile_output_buffer = current_xtcc_map_pos+1;\n";
	compute_flat_map_code.program_code << "\tflat_file_output_buffer = new char[len_flat_file_output_buffer];\n";
	compute_flat_map_code.program_code << "\txtcc_datafile_output_buffer = new char[len_xtcc_datafile_output_buffer];\n";
	compute_flat_map_code.program_code << "\tmemset(flat_file_output_buffer, ' ', len_flat_file_output_buffer-1);\n";
	compute_flat_map_code.program_code << "\tmemset(xtcc_datafile_output_buffer, '\\0', len_xtcc_datafile_output_buffer-1);\n";
	compute_flat_map_code.program_code << "\tflat_file_output_buffer[len_flat_file_output_buffer-1] = 0;\n";
	compute_flat_map_code.program_code << "\txtcc_datafile_output_buffer[len_xtcc_datafile_output_buffer-1] = 0;\n";
	compute_flat_map_code.program_code << "\tstring flat_file_name(jno + string(\".dat\"));\n";
	compute_flat_map_code.program_code << "\tflat_file.open(flat_file_name.c_str(), ios_base::out | ios_base::trunc);\n";
	compute_flat_map_code.program_code << "\tstring xtcc_datafile_name(jno + string(\".xdat\"));\n";
	compute_flat_map_code.program_code << "\txtcc_datafile.open(xtcc_datafile_name.c_str(), ios_base::out | ios_base::trunc);\n";

	if (config_file_parser::PLATFORM != "WINDOWS") {
		compute_flat_map_code.program_code
			<< "\t\t{struct stat dir_exists; stringstream s1;\n"
			<< "\t\ts1 << \"setup-\" << jno;\n"
			<< "\t\tif (stat(s1.str().c_str(), &dir_exists) <0) {\n"
			<< "\t\t\tif (errno == ENOENT)\n"
			<< "\t\t\t\tif (mkdir(s1.str().c_str(), S_IRUSR | S_IWUSR | S_IXUSR) <0) {\n"
			<< "\t\t\t\t\tperror(\"unable to create directory for setup files\");\n}\n"
			<< "\t\t\telse\n"
			<< "\t\t\t\tperror(\"stating directory failed\");\n"
			<< "\t\t\t}\n}\n"
			;
	} else {
		compute_flat_map_code.program_code
			<< "\t\t{struct stat dir_exists; stringstream s1;\n"
			<< "\t\t\ts1 << \"setup-\" << jno;\n"
			<< "\t\t\tif (stat(s1.str().c_str(), &dir_exists) <0) {\n"
			<< "\t\t\t\tif (errno == ENOENT)\n"
			<< "\t\t\t\t\tif (mkdir(s1.str().c_str()) <0) {\n"
			<< "\t\t\t\t\t\tperror(\"unable to create directory for setup files\");\n"
			<< "\t\t\t\t\t} else\n"
			<< "\t\t\t\t\t\tperror(\"stating directory failed\");\n"
			<< "\t\t\t}\n}\n"
			;
	}

	compute_flat_map_code.program_code << "\tif (write_qtm_data_file_flag) {\n";


	compute_flat_map_code.program_code << "\t\tstring qtm_map_file_name(string(\"setup-\") + jno + string(\"/\") + jno + string(\".qmap\"));\n";
	compute_flat_map_code.program_code << "\t\tfstream qtm_map_file(qtm_map_file_name.c_str(), ios_base::out|ios_base::ate);\n";
	compute_flat_map_code.program_code << "\t\tprint_map_header(qtm_map_file);\n";
	compute_flat_map_code.program_code << "\t\tfor (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {\n"
		<< "\t\t\tqtm_datafile_question_disk_map[i]->print_map(qtm_map_file);\n"
		<< "\t\t}\n";


	compute_flat_map_code.program_code << "\t\tstring qtm_qax_file_name( string(\"setup-\")+jno+string(\"/\") + jno + string(\".qax\"));\n";
	compute_flat_map_code.program_code << "\t\tfstream qtm_qax_file(qtm_qax_file_name.c_str(), ios_base::out|ios_base::ate);\n"
		"\t\tmap <string, vector<qtm_data_file_ns::QtmDataDiskMap*> > summary_tables;\n";
	compute_flat_map_code.program_code << "\t\tfor (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {\n"
		<< "\t\t\tqtm_datafile_question_disk_map[i]->print_qax(qtm_qax_file, string(\"setup-\")+jno);\n"
		<< "\t\t\tstring questionName = qtm_datafile_question_disk_map[i]->q->questionName_;\n"
		<< "\t\t\tif (qtm_datafile_question_disk_map[i]->q->loop_index_values.size() > 0) {\n"
		<< "\t\t\t\tsummary_tables[questionName].push_back(qtm_datafile_question_disk_map[i]);\n"
		<< "\t\t\t}\n"
		<< "\t\t}\n"
		<< "\t\tfor ( map <string, vector<qtm_data_file_ns::QtmDataDiskMap*> >::iterator it= summary_tables.begin();\n"
		<< "\t\t		it != summary_tables.end(); ++it) {\n"
		<< "\t\t	print_summary_axis(it->second, qtm_qax_file);\n"
		<< "\t\t}\n";
	compute_flat_map_code.program_code
		<< "\t\tqtm_datafile_question_disk_map[0]->print_run(jno);"
		<< endl;
	compute_flat_map_code.program_code << "\t\tstring tab_file_name(string(\"setup-\")+ jno + string(\"/\") + jno + string(\".tab\"));\n";
	compute_flat_map_code.program_code << "\t\tfstream tab_file(tab_file_name.c_str(), ios_base::out|ios_base::ate);\n";
	compute_flat_map_code.program_code << "\t\tfor (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {\n"
		<< "\t\t\tstring questionName = qtm_datafile_question_disk_map[i]->q->questionName_;\n"
		<< "\t\t\tAbstractRuntimeQuestion * q = qtm_datafile_question_disk_map[i]->q;\n"
		<< "\t\t\ttab_file << \"tab \" << q->questionName_;\n"
		<< "\t\t\tfor(int j=0; j<q->loop_index_values.size(); ++j) {\n"
		<< "\t\t\t\ttab_file << \"_\" << q->loop_index_values[j];\n"
		<< "\t\t\t}\n"
		<< "\t\t\ttab_file << \" &ban\" << endl;\n"
		<< "\t\t}\n";


	compute_flat_map_code.program_code << "\t\tqtm_datafile_question_disk_map[0]->qtmDataFile_.AllocateCards();\n"
		<< "\t\tqtm_datafile_question_disk_map[0]->qtmDataFile_.Reset();\n";
	compute_flat_map_code.program_code << "\t\tstring qtm_disk_file_name(jno + string(\".qdat\"));\n";
	compute_flat_map_code.program_code << "\t\tqtm_disk_file.open(qtm_disk_file_name.c_str(), ios_base::out | ios_base::trunc);\n";
	compute_flat_map_code.program_code << "\t}\n";

	compute_flat_map_code.program_code
		<< "\tif (write_xtcc_data_file_flag) {\n"
		<< "\t\tstring xtcc_ax_file_name(string(\"setup-\")+jno+string(\"/\") + jno + string(\".xtcc\"));\n"
		<< "\t\tfstream xtcc_ax_file(xtcc_ax_file_name.c_str(), ios_base::out | ios_base::ate);\n"
		<< "\t\txtcc_ax_file << \"data_struct;rec_len=\" << len_xtcc_datafile_output_buffer << \";\\n\";\n"
		<< "\t\txtcc_ax_file << \"ed_start\\n\";\n"
		<< "\t\t xtcc_ax_file << \"\tint32_t edit_data();\\n\";\n"
		<< "\t\t xtcc_ax_file << \"\tint32_t all;\\n\";\n"
		<< "\t\t xtcc_ax_file << \"\tint32_t ser_no;\\n\";\n"
		<< "\t\tfor (int i=0; i<xtcc_question_disk_map.size(); ++i) {\n"
		<< "\t\t\txtcc_question_disk_map[i]->print_edit_var_defns(xtcc_ax_file, string(\"setup-\")+jno+string(\"/\"));\n"
		<< "\t\t}\n"
		<< "\t\t xtcc_ax_file << \"\tint32_t edit_data()\\n{\\n\";\n"
		<< "\t\t xtcc_ax_file << \"\tall = 1;\\n\";\n"
		<< "\t\t xtcc_ax_file << \"\tser_no = c[0,3];\\n\";\n"
		<< "\t\tfor (int i=0; i<xtcc_question_disk_map.size(); ++i) {\n"
		<< "\t\t\txtcc_question_disk_map[i]->print_xtcc_edit_load(xtcc_ax_file, string(\"setup-\")+jno+string(\"/\"));\n"
		<< "\t\t}\n"
		<< "\t\t xtcc_ax_file << \"\t}\\n\";\n"
		<< "\t\txtcc_ax_file << \"ed_end\\n\";\n"
		<< "\t\txtcc_ax_file << \"tabstart {\\n\";\n"
		<< "\t\tfor (int i=0; i<xtcc_question_disk_map.size(); ++i) {\n"
		<< "\t\t\txtcc_question_disk_map[i]->print_xtcc_tab(xtcc_ax_file, string(\"setup-\")+jno+string(\"/\"));\n"
		<< "\t\t}\n"
		<< "\t\txtcc_ax_file << \"}\\n\";\n"
		<< "\t\txtcc_ax_file << \"axstart {\\n\";\n"

		<< "\t\txtcc_ax_file << \"ax tot_ax;\\n\";\n"
		<< "\t\txtcc_ax_file << \"ttl; \\\"Total\\\";\\n\";\n"
		<< "\t\txtcc_ax_file << \"cnt; \\\"All\\\"; c= all==1;\\n\";\n"

		<< "\t\tfor (int i=0; i<xtcc_question_disk_map.size(); ++i) {\n"
		<< "\t\t\txtcc_question_disk_map[i]->print_xtcc_ax(xtcc_ax_file, string(\"setup-\")+jno+string(\"/\"));\n"
		<< "\t\t}\n"
		<< "\t\txtcc_ax_file << \"}\\n\";\n"
		<< "\t}\n";

	compute_flat_map_code.program_code << "}\n";
	compute_flat_map_code.program_code << "}\n";
}

void print_eval_questionnaire (FILE* script, ostringstream & program_code, bool ncurses_flag)
{
	fprintf(script, "/* vector<AbstractRuntimeQuestion *> */ EvalReturnValue eval2 ( /*AbstractRuntimeQuestion * p_last_question_answered,\n"
			"\t\t AbstractRuntimeQuestion * p_last_question_visited,*/\n"
			"\t\t UserNavigation p_navigation_mode, const vector<AbstractRuntimeQuestion *> & p_last_question_visited, AbstractRuntimeQuestion * p_jump_to_index, const string & p_jump_to_group_name)\n{\n");

	fprintf(script, "//if (last_question_visited)\n\t//fprintf (qscript_stdout, \"entered eval2: last_question_visited: %%s, stopAtNextQuestion: %%d\\n\", last_question_visited->questionName_.c_str(), stopAtNextQuestion);\n");



	fprintf(script, "\t/*\n");
	fprintf(script, "%s\n", file_exists_check_code());
	fprintf(script, "\t*/\n");
	fprintf(script, "\tvector<string> error_messages_vec;\n");
	fprintf(script, "\terror_messages_vec.clear();\n");

	fprintf(script, "\tstart_of_questions:\n");
	fprintf(script, "\tif(back_jump == true){\n");
	fprintf(script, "\t//fprintf(qscript_stdout, \"have reached start_of_questions with back_jump: jumpToQuestion: %%s, jumpToIndex: %%d\\n\", jumpToQuestion.c_str(), jumpToIndex);\n");
	fprintf(script, "\t}\n");

	fprintf(script, "%s\n", program_code.str().c_str());


	//fprintf(script, "\t{ vector<AbstractRuntimeQuestion*> empty_vec; return empty_vec;}\n");
	fprintf(script, "\t{ EvalReturnValue ev_ret_val; return ev_ret_val;}\n");
	fprintf(script, "} /* close eval */\n");

}

void print_read_a_serial_no (FILE * script)
{
	fprintf (script, "\n");
	fprintf (script, "    int read_a_serial_no()\n");
	fprintf (script, "    {\n");
	fprintf (script, "	//cout << \"ENTER: \"  << __FILE__ << \", \" << __LINE__ << \", \" << __PRETTY_FUNCTION__ << endl;\n");
	fprintf (script, "restart:\n");
	fprintf (script, "	struct dirent *directory_entry = readdir(directory_ptr);\n");
	fprintf (script, "	if (directory_entry == NULL) {\n");
	fprintf (script, "	    // we have read upto the last record in the directory\n");
	fprintf (script, "	    cout << \"finished reading all data files ... exiting\"\n");
	fprintf (script, "		<< endl;\n");
	fprintf (script, "	    return 0;\n");
	fprintf (script, "	}\n");
	fprintf (script, "	string dir_entry_name(directory_entry->d_name);\n");
	fprintf (script, "	int len_entry = dir_entry_name.length();\n");
	fprintf (script, "	if (len_entry > 4 &&\n");
	fprintf (script, "	    dir_entry_name[len_entry - 1] == 't' &&\n");
	fprintf (script, "	    dir_entry_name[len_entry - 2] == 'a' &&\n");
	fprintf (script, "	    dir_entry_name[len_entry - 3] == 'd' &&\n");
	fprintf (script, "	    dir_entry_name[len_entry - 4] == '.') {\n");
	fprintf (script, "	    if (dir_entry_name.length() < jno.length() + 6\n");
	fprintf (script, "		/* \"_1.dat\" is the shortest possible datafile name for our study */\n");
	fprintf (script, "		) {\n");
	fprintf (script, "		// cannot be our data file\n");
	fprintf (script, "		goto restart;\n");
	fprintf (script, "	    }\n");
	fprintf (script, "	    bool not_our_file = false;\n");
	fprintf (script, "	    for (int i = 0; i < jno.length(); ++i) {\n");
	fprintf (script, "		if (!(jno[i] == dir_entry_name[i])) {\n");
	fprintf (script, "		    // cannot be our data file\n");
	fprintf (script, "		    not_our_file = true;\n");
	fprintf (script, "		    break;\n");
	fprintf (script, "		}\n");
	fprintf (script, "	    }\n");
	fprintf (script, "	    if (not_our_file) {\n");
	fprintf (script, "		//continue;\n");
	fprintf (script, "		goto restart;\n");
	fprintf (script, "	    }\n");
	fprintf (script, "	    // all our data files are expected\n");
	fprintf (script, "	    // to have a \".dat\" ending and '_' after job number\n");
	fprintf (script, "	    // find the \".\"\n");
	fprintf (script, "	    cout << dir_entry_name << endl;\n");
	fprintf (script, "	    if (dir_entry_name[jno.length()] != '_') {\n");
	fprintf (script, "		not_our_file = true;\n");
	fprintf (script, "		//continue;\n");
	fprintf (script, "		goto restart;\n");
	fprintf (script, "	    }\n");
	fprintf (script, "	    stringstream file_ser_no_str;\n");
	fprintf (script, "	    for (int i = jno.length() + 1;\n");
	fprintf (script, "		 i < dir_entry_name.length(); ++i) {\n");
	fprintf (script, "		if (isdigit(dir_entry_name[i])) {\n");
	fprintf (script, "		    file_ser_no_str << dir_entry_name[i];\n");
	fprintf (script, "		} else {\n");
	fprintf (script, "		    if ((i + 4 == dir_entry_name.length())\n");
	fprintf (script, "			&& dir_entry_name[i] == '.'\n");
	fprintf (script, "			&& dir_entry_name[i + 1] == 'd'\n");
	fprintf (script, "			&& dir_entry_name[i + 2] == 'a'\n");
	fprintf (script, "			&& dir_entry_name[i + 3] == 't') {\n");
	fprintf (script, "			//its most probably our file \n");
	fprintf (script, "			// need to check leading digit is not 0\n");
	fprintf (script, "			break;\n");
	fprintf (script, "		    } else {\n");
	fprintf (script, "			// it's not our file \n");
	fprintf (script, "			not_our_file = true;\n");
	fprintf (script, "			goto restart;\n");
	fprintf (script, "		    }\n");
	fprintf (script, "		}\n");
	fprintf (script, "	    }\n");
	fprintf (script, "	    if (not_our_file) {\n");
	fprintf (script, "		    goto restart;\n");
	fprintf (script, "	    }\n");
	fprintf (script, "	    if ((file_ser_no_str.str())[0] == '0') {\n");
	fprintf (script, "		// the leading digit of our data file\n");
	fprintf (script, "		// can never be zero - so its not our file\n");
	fprintf (script, "		goto restart;\n");
	fprintf (script, "	    }\n");
	fprintf (script, "	    cout << \"got a data file: \" << dir_entry_name << endl;\n");
	fprintf (script, "	    int file_ser_no = atoi(file_ser_no_str.str().c_str());\n");
	fprintf (script, " 		map <string, question_disk_data*>  qdd_map;\n");
	fprintf (script, "	    load_data(jno, file_ser_no, &qdd_map);\n");
	fprintf (script, "	    merge_disk_data_into_questions2(qscript_stdout, last_question_answered, last_question_visited, this->question_list, &qdd_map);\n");
	fprintf (script, "		for (map<string, question_disk_data*>:: iterator it \n");
	fprintf (script, "				= qdd_map.begin();\n");
	fprintf (script, "				it != qdd_map.end();\n");
	fprintf (script, "				++it) {\n");
	fprintf (script, "			delete it->second;\n");
	fprintf (script, "		}\n");
	fprintf (script, "	    return file_ser_no;\n");
	fprintf (script, "	} else {\n");
	fprintf (script, "	    // not our data file\n");
	fprintf (script, "	    goto restart;\n");
	fprintf (script, "	}\n");
	fprintf (script, "    }\n");
	fprintf (script, "\n");
}

void print_write_qtm_data_to_disk(FILE *script)
{
	fprintf(script, "void write_qtm_data_to_disk()\n {\n");
	fprintf(script, "	using qtm_data_file_ns::qtm_data_file_writer_log;\n");
	fprintf(script, "	qtm_data_file_writer_log << \"writing serial no: \" << ser_no << \" to disk \\n\";\n");
	fprintf(script, "	for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {\n");
	fprintf(script, "		qtm_datafile_question_disk_map[i]->write_data ();\n");
	fprintf(script, "	}\n");
	fprintf(script, "	qtm_datafile_question_disk_map[0]->qtmDataFile_.write_record_to_disk(qtm_disk_file, ser_no);\n");
	fprintf(script, "	qtm_datafile_question_disk_map[0]->qtmDataFile_.Reset();\n");
	fprintf(script, "	//qtm_datafile_question_disk_map[0]->Reset();\n");
	fprintf(script, "	for (int32_t i = 0; i < qtm_datafile_question_disk_map.size(); ++i) {\n");
	fprintf(script, "		qtm_datafile_question_disk_map[i]->Reset();\n");
	fprintf(script, "	}\n");
	fprintf(script, "	do_freq_counts();\n");
	/*
	fprintf(script, "       for (int32_t i = 0; i < question_list.size(); ++i) {\n");
	fprintf(script, "                       AbstractQuestion * q = question_list[i];\n");
	fprintf(script, "			stringstream question_name_str;\n");
	fprintf(script, "			question_name_str << q->questionName_;\n");
	fprintf(script, "		    if (q->loop_index_values.size()) {\n");
	fprintf(script, "				for (int j=0; j<q->loop_index_values.size(); ++j) {\n");
	fprintf(script, "					question_name_str << \".\" << q->loop_index_values[j];\n");
	fprintf(script, "				}\n");
	fprintf(script, "		    }\n");
	fprintf(script, "                       map<int , int> q_freq_map = freq_count[question_name_str.str()];\n");
	fprintf(script, "                       for (set<int32_t>::iterator it = q->input_data.begin();\n");
	fprintf(script, "                                       it != q->input_data.end(); ++it) {\n");
	fprintf(script, "                               q_freq_map[*it] ++;\n");
	fprintf(script, "                       }\n");
	fprintf(script, "                       freq_count[question_name_str.str()] = q_freq_map;\n");
	fprintf(script, "       }\n");
	*/
	fprintf(script, "}\n");
}

void print_do_freq_counts(FILE *script)
{
	fprintf(script, "void do_freq_counts()\n{\n");
	fprintf(script, "\tfor (int32_t i = 0; i < question_list.size(); ++i) {\n");
	fprintf(script, "\t\tAbstractQuestion * q = question_list[i];\n");
	fprintf(script, "\t\tstringstream question_name_str;\n");
	fprintf(script, "\t\tquestion_name_str << q->questionName_;\n");
	fprintf(script, "\t\tif (q->loop_index_values.size()) {\n");
	fprintf(script, "\t\t\tfor (int j=0; j<q->loop_index_values.size(); ++j) {\n");
	fprintf(script, "\t\t\t\tquestion_name_str << \".\" << q->loop_index_values[j];\n");
	fprintf(script, "\t\t\t}\n");
	fprintf(script, "\t\t}\n");
	fprintf(script, "\t\tmap<int , int> q_freq_map = freq_count[question_name_str.str()];\n");
	fprintf(script, "\t\tfor (set<int32_t>::iterator it = q->input_data.begin();\n");
	fprintf(script, "\t\t\tit != q->input_data.end(); ++it) {\n");
	fprintf(script, "\t\t\t\tq_freq_map[*it] ++;\n");
	fprintf(script, "\t\t}\n");
	fprintf(script, "\t\tfreq_count[question_name_str.str()] = q_freq_map;\n");
	fprintf(script, "\t}\n");
	fprintf(script, "}\n");
}

void print_write_ascii_data_to_disk(FILE *script)
{
	fprintf(script, "void write_ascii_data_to_disk()\n{\n");
	fprintf(script, "	stringstream temp_ser_no_str;\n");
	fprintf(script, "	temp_ser_no_str << ser_no;\n");
	fprintf(script, "	if (temp_ser_no_str.str().length() > ser_no_pos) {\n");
	fprintf(script, "		cerr << \"space reserved to hold serial no: \" \n");
	fprintf(script, "			<< ser_no_pos << \" is not enough\"\n");
	fprintf(script, "			<< \" to hold this serial no: \" \n");
	fprintf(script, "			<< ser_no << endl;\n");
	fprintf(script, "		exit(1);\n");
	fprintf(script, "	} else {\n");
	fprintf(script, "		//char * ptr = flat_file_output_buffer;\n");
	fprintf(script, "		for (int i=0; i<temp_ser_no_str.str().length(); ++i) {\n");
	fprintf(script, "			flat_file_output_buffer[i] = temp_ser_no_str.str()[i];\n");
	fprintf(script, "		//cout << \"writing digit \" << temp_ser_no_str[i] << \" to flat_file_output_buffer\" << endl;\n");
	fprintf(script, "		}\n");
	fprintf(script, "	}\n");
	fprintf(script, "\n");
	fprintf(script, "	for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {\n");
	fprintf(script, "		ascii_flatfile_question_disk_map[i]->write_data (flat_file_output_buffer);\n");
	fprintf(script, "	}\n");
	fprintf(script, "	// cout << \"output_buffer: \" << flat_file_output_buffer;\n");
	fprintf(script, "	flat_file << flat_file_output_buffer << endl;\n");
	fprintf(script, "	memset(flat_file_output_buffer, ' ', len_flat_file_output_buffer-1);\n");
	fprintf(script, "	do_freq_counts();\n");
	fprintf(script, "}\n");
}

void print_write_spss_file_for_ascii_data_to_disk(/*FILE *script*/StatementCompiledCode & compute_flat_map_code)
{
	compute_flat_map_code.program_code << "\tstring spss_syn_file_name(jno + string(\"-flat-ascii.sps\"));\n";
	compute_flat_map_code.program_code << "\tfstream spss_syn_file(spss_syn_file_name.c_str(), ios_base::out|ios_base::ate);\n";
	compute_flat_map_code.program_code << "\t spss_syn_file << \"DATA LIST FILE='\" << "
		<< " jno << \".dat'\\n\"<< endl << \"/RESPID\t\t\t1-6\\n\";\n";
	compute_flat_map_code.program_code << "\tfor (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {\n"
		<< "\t\tascii_flatfile_question_disk_map[i]->write_spss_pull_data(spss_syn_file);\n"
		<< "\t}\n";
	compute_flat_map_code.program_code << "\t spss_syn_file << \".\\n\";\n";
	compute_flat_map_code.program_code << "\n spss_syn_file << \"exe.\\n\";\n";
	compute_flat_map_code.program_code << "\tfor (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {\n"
		<< "\t\tascii_flatfile_question_disk_map[i]->write_spss_variable_labels(spss_syn_file);\n"
		<< "\t}\n";
	compute_flat_map_code.program_code << "\n spss_syn_file << \"exe.\\n\";\n";
	compute_flat_map_code.program_code << "\tfor (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {\n"
		<< "\t\tascii_flatfile_question_disk_map[i]->write_spss_value_labels(spss_syn_file);\n"
		<< "\t}\n";
	compute_flat_map_code.program_code << "\n spss_syn_file << \"exe.\\n\";\n";
	compute_flat_map_code.program_code << "\n spss_syn_file << \"save outfile=\\\"\" << jno << \".sav\\\"\\n\";\n";

	//compute_flat_map_code.program_code << "\t\tfor (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {\n"
	//	<< "\t\t\tqtm_datafile_question_disk_map[i]->print_qax(qtm_qax_file, string(\"setup-\")+jno);\n"
	//	<< "\t\t\tstring questionName = qtm_datafile_question_disk_map[i]->q->questionName_;\n"
	//	<< "\t\t\tif (qtm_datafile_question_disk_map[i]->q->loop_index_values.size() > 0) {\n"
	//	<< "\t\t\t\tsummary_tables[questionName].push_back(qtm_datafile_question_disk_map[i]);\n"
	//	<< "\t\t\t}\n"

}

void print_write_xtcc_data_to_disk(FILE *script)
{
	fprintf(script, "void write_xtcc_data_to_disk()\n {\n");
	// serial number goes into the 1st 4 bytes
	fprintf(script, "	void * void_ptr = &ser_no;\n");
	fprintf(script, "	char * char_ptr = static_cast<char*>(void_ptr);\n");
	fprintf(script, "	char * my_data_ptr = xtcc_datafile_output_buffer;\n");
	fprintf(script, "	for (int i=0; i<sizeof(int); ++i) {\n");
	fprintf(script, "		*my_data_ptr++ = *char_ptr++;\n");
	fprintf(script, "	}\n");
	fprintf(script, "\n");
	fprintf(script, "	for (int i=0; i<xtcc_question_disk_map.size(); ++i) {\n");
	fprintf(script, "		xtcc_question_disk_map[i]->write_data (xtcc_datafile_output_buffer);\n");
	fprintf(script, "	}\n");
	fprintf(script, "	//cout << \"output_buffer: \" << xtcc_datafile_output_buffer;\n");
	fprintf(script, "	xtcc_datafile . write(xtcc_datafile_output_buffer, len_xtcc_datafile_output_buffer);\n");
	fprintf(script, "	memset(xtcc_datafile_output_buffer, 0, len_xtcc_datafile_output_buffer-1);\n");
	fprintf(script, "	do_freq_counts();\n");
	fprintf(script, "	cout << \"len_xtcc_datafile_output_buffer: \" << len_xtcc_datafile_output_buffer << endl;\n");
	fprintf(script, "}\n");
}


void print_summary_axis(FILE * script)
{

	fprintf (script, "void print_summary_axis (vector<qtm_data_file_ns::QtmDataDiskMap*> & v, fstream & qtm_qax_file) \n");
	fprintf (script, "{\n");
	fprintf (script, "	AbstractQuestion * q = v[0]->q;\n");
	fprintf (script, "	if (q->q_type == spn) {\n");
	fprintf (script, "		int n_digits = 0;\n");
	fprintf (script, "		int rat_scale = 0;\n");
	fprintf (script, "		if (NamedStubQuestion * n_q = dynamic_cast<NamedStubQuestion*>(q)) {\n");
	fprintf (script, "			if (n_q->nr_ptr) {\n");
	fprintf (script, "				string & stub_name = n_q->nr_ptr->name;\n");
	fprintf (script, "				int multiplier = 1;\n");
	fprintf (script, "				for (int i=stub_name.length()-1; i>0; --i) {\n");
	fprintf (script, "					if ( isdigit(stub_name[i]) ) {\n");
	fprintf (script, "						int c = stub_name[i] - '0';\n");
	fprintf (script, "						++n_digits;\n");
	fprintf (script, "						rat_scale = rat_scale + c * multiplier;\n");
	fprintf (script, "						multiplier *= 10;\n");
	fprintf (script, "					} else {\n");
	fprintf (script, "						break;\n");
	fprintf (script, "					}\n");
	fprintf (script, "				}\n");
	fprintf (script, "			}\n");
	fprintf (script, "		}\n");
	fprintf (script, "		if (n_digits > 0) {\n");
	fprintf (script, "			string include_file_name;\n");
	fprintf (script, "			string mean_score_include_file;\n");
	fprintf (script, "			if (v[0]->width_ == 1) {\n");
	fprintf (script, "				include_file_name = \"rat1c.qin\";\n");
	fprintf (script, "				mean_score_include_file = \"mn1c.qin\";\n");
	fprintf (script, "			} else if (v[0]->width_ == 2) {\n");
	fprintf (script, "				include_file_name = \"rat2c.qin\";\n");
	fprintf (script, "				mean_score_include_file = \"mn2c.qin\";\n");
	fprintf (script, "			} else if (v[0]->width_ == 3) {\n");
	fprintf (script, "				include_file_name = \"rat3c.qin\";\n");
	fprintf (script, "				mean_score_include_file = \"mn3c.qin\";\n");
	fprintf (script, "			} else {\n");
	fprintf (script, "				include_file_name = \"unhandled width syntax error\";\n");
	fprintf (script, "				mean_score_include_file = \"unhandled width syntax error\";\n");
	fprintf (script, "			}\n");
	fprintf (script, "\n");

	fprintf (script, "			if (rat_scale == 5) {\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 5 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top2\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 5 << \", \" << 4 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot2\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \", \" << 2 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_mn\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << mean_score_include_file\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \":\" << 5 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "			}\n");

	fprintf (script, "			else if (rat_scale == 7) {\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 7 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top2\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 7 << \", \" << 6 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top3\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 5 << \":\" << 7 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot2\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \", \" << 2 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_mn\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << mean_score_include_file\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \":\" << 7 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot3\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \":\" << 3 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "			}\n");

	fprintf (script, "			else if (rat_scale == 10) {\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 10 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top2\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 10 << \", \" << 9 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_top3\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 8 << \":\" << 10 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot2\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \", \" << 2 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_mn\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << mean_score_include_file\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \":\" << 10 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "				qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "				qtm_qax_file << \"l \" << q->questionName_ << \"_bot3\" << endl;\n");
	fprintf (script, "				qtm_qax_file << \"ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "				for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "					qtm_qax_file << \"*include \" << include_file_name\n");
	fprintf (script, "						<< \";qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 \n");
	fprintf (script, "						<< \";myrange=(\" << 1 << \":\" << 3 << \")\"\n");
	fprintf (script, "						<< endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "\n");
	fprintf (script, "			}\n");

	fprintf (script, "		} else {\n");
	fprintf (script, "			qtm_qax_file << \"/* summary table for: \" << v[0]->q->questionName_ << endl;\n");
	fprintf (script, "			qtm_qax_file << \"/*l \" << q->questionName_ << \"_sum\" << endl;\n");
	fprintf (script, "			qtm_qax_file << \"/*ttl\" << q->questionName_ << \".\" << v[0]->q->textExprVec_[0]->text_ << endl;\n");
	fprintf (script, "			for (int i=0; i<v.size(); ++i) {\n");
	fprintf (script, "				qtm_qax_file << \"/**include summ.qin;qatt=&at\" << i << \"t;\" << \"col(a)=\" << v[i]->startPosition_+1 << endl;\n");
	fprintf (script, "			}\n");
	fprintf (script, "		}\n");
	fprintf (script, "	}\n");
	fprintf (script, "	cout << endl;\n");
	fprintf (script, "}\n");
}

void print_prompt_user_for_serial_no(FILE * script)
{
	fprintf(script, "	void prompt_user_for_serial_no()\n");
	fprintf(script, "	{\n");
	fprintf(script, "		wclear(data_entry_window);\n");
	fprintf(script, "		mvwprintw(data_entry_window, 1, 1, \"Enter Serial No (0) to exit: \");\n");
	fprintf(script, "		mvwscanw(data_entry_window, 1, 40, \"%%d\", & ser_no);\n");
	fprintf(script, "	}\n\n");
}

void print_ncurses_include_files (FILE * script)
{
	fprintf(script, "#include <curses.h>\n");
	fprintf(script, "#include <panel.h>\n");
}

void print_ncurses_func_prototypes (FILE * script)
{
	fprintf(script, "WINDOW *create_newwin(int32_t height, int32_t width, int32_t starty, int32_t startx);\n");
	fprintf(script, "void SetupNCurses(WINDOW * &  question_window,\n"
			"			WINDOW * &  stub_list_window,\n"
			"			WINDOW * & data_entry_window,\n"
			"			WINDOW * & help_window,\n"
			"			PANEL * &  question_panel,\n"
			"			PANEL * &  stub_list_panel,\n"
			"			PANEL * & data_entry_panel,\n"
			"			PANEL * & help_panel);\n");
	fprintf(script, "void define_some_pd_curses_keys();\n");
}

void print_microhttpd_web_support (FILE * script)
{
	fprintf (script, " \n");
	fprintf (script, "#define MHD_PORT_NUMBER 	8888\n");
	fprintf (script, "//struct MHD_Daemon * setup_and_run_MHD_daemon()\n");
	fprintf (script, "int setup_and_run_MHD_daemon()\n");
	fprintf (script, "{\n");
	fprintf (script, "  struct MHD_Daemon *d;\n");
	fprintf (script, "  struct timeval tv;\n");
	fprintf (script, "  struct timeval *tvp;\n");
	fprintf (script, "  fd_set rs;\n");
	fprintf (script, "  fd_set ws;\n");
	fprintf (script, "  fd_set es;\n");
	fprintf (script, "  int max;\n");
	fprintf (script, "  unsigned MHD_LONG_LONG mhd_timeout;\n");
	fprintf (script, "\n");
	fprintf (script, "  /* initialize PRNG */\n");
	fprintf (script, "  srandom ((unsigned int) time (NULL));\n");
	fprintf (script, "  d = MHD_start_daemon (MHD_USE_DEBUG,\n");
	fprintf (script, "                        MHD_PORT_NUMBER,\n");
	fprintf (script, "                        NULL, NULL, \n");
	fprintf (script, "			&create_response, NULL, \n");
	fprintf (script, "			MHD_OPTION_CONNECTION_TIMEOUT, (unsigned int) 15,\n");
	fprintf (script, "			MHD_OPTION_NOTIFY_COMPLETED, &request_completed_callback, NULL,\n");
	fprintf (script, "			MHD_OPTION_END);\n");
	fprintf (script, "  if (NULL == d)\n");
	fprintf (script, "    return 1;\n");
	fprintf (script, "  while (1)\n");
	fprintf (script, "    {\n");
	fprintf (script, "      //expire_sessions ();\n");
	fprintf (script, "      max = 0;\n");
	fprintf (script, "      FD_ZERO (&rs);\n");
	fprintf (script, "      FD_ZERO (&ws);\n");
	fprintf (script, "      FD_ZERO (&es);\n");
	fprintf (script, "      if (MHD_YES != MHD_get_fdset (d, &rs, &ws, &es, &max))\n");
	fprintf (script, "	break; /* fatal internal error */\n");
	fprintf (script, "      if (MHD_get_timeout (d, &mhd_timeout) == MHD_YES)	\n");
	fprintf (script, "	{\n");
	fprintf (script, "	  tv.tv_sec = mhd_timeout / 1000;\n");
	fprintf (script, "	  tv.tv_usec = (mhd_timeout - (tv.tv_sec * 1000)) * 1000;\n");
	fprintf (script, "	  tvp = &tv;	  \n");
	fprintf (script, "	}\n");
	fprintf (script, "      else\n");
	fprintf (script, "	tvp = NULL;\n");
	fprintf (script, "      select (max + 1, &rs, &ws, &es, tvp);\n");
	fprintf (script, "      MHD_run (d);\n");
	fprintf (script, "    }\n");
	fprintf (script, "  MHD_stop_daemon (d);\n");
	fprintf (script, "  return 0;\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");
	fprintf (script, "\n");
	fprintf (script, "static void\n");
	fprintf (script, "request_completed_callback (void *cls,\n");
	fprintf (script, "			    struct MHD_Connection *connection,\n");
	fprintf (script, "			    void **con_cls,\n");
	fprintf (script, "			    enum MHD_RequestTerminationCode toe)\n");
	fprintf (script, "{\n");
	fprintf (script, "  struct Request *request = (struct Request *) *con_cls;\n");
	fprintf (script, "\n");
	fprintf (script, "  if (NULL == request)\n");
	fprintf (script, "    return;\n");
	fprintf (script, "  if (NULL != request->session)\n");
	fprintf (script, "    request->session->rc--;\n");
	fprintf (script, "  if (NULL != request->pp)\n");
	fprintf (script, "    MHD_destroy_post_processor (request->pp);\n");
	fprintf (script, "  free (request);\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");
	fprintf (script, "\n");
	fprintf (script, "static int\n");
	fprintf (script, "create_response (void *cls,\n");
	fprintf (script, "		 struct MHD_Connection *connection,\n");
	fprintf (script, "		 const char *url,\n");
	fprintf (script, "		 const char *method,\n");
	fprintf (script, "		 const char *version,\n");
	fprintf (script, "		 const char *upload_data, \n");
	fprintf (script, "		 size_t *upload_data_size,\n");
	fprintf (script, "		 void **ptr)\n");
	fprintf (script, "{\n");
	fprintf (script, "	struct MHD_Response *response;\n");
	fprintf (script, "	struct Request *request;\n");
	fprintf (script, "	struct Session *session;\n");
	fprintf (script, "	int ret;\n");
	fprintf (script, "	unsigned int i;\n");
	fprintf (script, "\n");
	fprintf (script, "	printf(\"ENTER: %%s\\n\", __PRETTY_FUNCTION__);\n");
	fprintf (script, "\n");
	fprintf (script, "	request = (struct Request*) *ptr;\n");
	fprintf (script, "	if (NULL == request) {\n");
	fprintf (script, "		printf(\"func: %%s, called the first time creating MHD_create_post_processor\\n\", __PRETTY_FUNCTION__);\n");
	fprintf (script, "		request = (struct Request *) calloc (1, sizeof (struct Request));\n");
	fprintf (script, "		if (NULL == request) {\n");
	fprintf (script, "			fprintf (stderr, \"calloc error: %%s\\n\", strerror (errno));\n");
	fprintf (script, "			return MHD_NO;\n");
	fprintf (script, "		}\n");
	fprintf (script, "		*ptr = request;\n");
	fprintf (script, "		if (0 == strcmp (method, MHD_HTTP_METHOD_POST)) {\n");
	fprintf (script, "			request->pp = MHD_create_post_processor (connection, 1024,\n");
	fprintf (script, "							   &post_iterator, request);\n");
	fprintf (script, "			if (NULL == request->pp) {\n");
	fprintf (script, "				fprintf (stderr, \"Failed to setup post processor for `%%s'\\n\",\n");
	fprintf (script, "					url);\n");
	fprintf (script, "				return MHD_NO; /* internal error */\n");
	fprintf (script, "			}\n");
	fprintf (script, "		}\n");
	fprintf (script, "		printf(\"func: %%s, called the first time successfully created a MHD_create_post_processor\\n\", __PRETTY_FUNCTION__);\n");
	fprintf (script, "		return MHD_YES;\n");
	fprintf (script, "	} else {\n");
	fprintf (script, "		printf(\"func: %%s post processor already created continuing to handle request\\n\", __PRETTY_FUNCTION__); \n");
	fprintf (script, "	}\n");
	fprintf (script, "	if (NULL == request->session) {\n");
	fprintf (script, "		printf(\"func: %%s, creating a session\\n\", __PRETTY_FUNCTION__);\n");
	fprintf (script, "		request->session = get_session (connection);\n");
	fprintf (script, "		if (NULL == request->session) {\n");
	fprintf (script, "			fprintf (stderr, \"Failed to setup session for `%%s'\\n\",\n");
	fprintf (script, "				url);\n");
	fprintf (script, "			return MHD_NO; /* internal error */\n");
	fprintf (script, "		}\n");
	fprintf (script, "	}\n");
	fprintf (script, "	session = request->session;\n");
	fprintf (script, "	session->start = time (NULL);\n");
	fprintf (script, "	if (0 == strcmp (method, MHD_HTTP_METHOD_POST)) {\n");
	fprintf (script, "		/* evaluate POST data */\n");
	fprintf (script, "		printf(\"func: %%s, MHD_HTTP_METHOD_POST\\n\", __PRETTY_FUNCTION__);\n");
	fprintf (script, "		MHD_post_process (request->pp,\n");
	fprintf (script, "				upload_data,\n");
	fprintf (script, "				*upload_data_size);\n");
	fprintf (script, "		if (0 != *upload_data_size) {\n");
	fprintf (script, "			*upload_data_size = 0;\n");
	fprintf (script, "			return MHD_YES;\n");
	fprintf (script, "		}\n");
	fprintf (script, "		/* done with POST data, serve response */\n");
	fprintf (script, "		MHD_destroy_post_processor (request->pp);\n");
	fprintf (script, "		request->pp = NULL;\n");
	fprintf (script, "		method = MHD_HTTP_METHOD_GET; /* fake 'GET' */\n");
	fprintf (script, "		if (NULL != request->post_url)\n");
	fprintf (script, "			url = request->post_url;\n");
	fprintf (script, "\n");
	fprintf (script, "		printf(\"func: %%s, done with post processor : requested url is: %%s\\n\"\n");
	fprintf (script, "				, __PRETTY_FUNCTION__, url);\n");
	fprintf (script, "	}\n");
	fprintf (script, "\n");
	fprintf (script, "	if ( (0 == strcmp (method, MHD_HTTP_METHOD_GET)) ||\n");
	fprintf (script, "		(0 == strcmp (method, MHD_HTTP_METHOD_HEAD)) ) {\n");
	fprintf (script, "	/* find out which page to serve */\n");
	fprintf (script, "	    /*\n");
	fprintf (script, "	printf(\"func: %%s, url %%s\\n\", __PRETTY_FUNCTION__, url);\n");
	fprintf (script, "	i=0;\n");
	fprintf (script, "	while ( (pages[i].url != NULL) &&\n");
	fprintf (script, "	      (0 != strcmp (pages[i].url, url)) )\n");
	fprintf (script, "	i++;\n");
	fprintf (script, "\n");
	fprintf (script, "	printf(\"i == %%d\\n\", i);\n");
	fprintf (script, "	ret = pages[i].handler (pages[i].handler_cls, \n");
	fprintf (script, "			      pages[i].mime,\n");
	fprintf (script, "			      session, connection);\n");
	fprintf (script, "	*/\n");
	fprintf (script, "		ret = serve_question(session, connection);\n");
	fprintf (script, "		if (ret != MHD_YES)\n");
	fprintf (script, "			fprintf (stderr, \"Failed to create page for `%%s'\\n\",\n");
	fprintf (script, "				url);\n");
	fprintf (script, "		return ret;\n");
	fprintf (script, "	}\n");
	fprintf (script, "	/* unsupported HTTP method */\n");
	fprintf (script, "	response = MHD_create_response_from_buffer (strlen (METHOD_ERROR),\n");
	fprintf (script, "					      (void *) METHOD_ERROR,\n");
	fprintf (script, "					      MHD_RESPMEM_PERSISTENT);\n");
	fprintf (script, "	ret = MHD_queue_response (connection, \n");
	fprintf (script, "			    MHD_HTTP_METHOD_NOT_ACCEPTABLE, \n");
	fprintf (script, "			    response);\n");
	fprintf (script, "	MHD_destroy_response (response);\n");
	fprintf (script, "	return ret;\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");
	fprintf (script, "\n");
	fprintf (script, "static int\n");
	fprintf (script, "post_iterator (void *cls,\n");
	fprintf (script, "	       enum MHD_ValueKind kind,\n");
	fprintf (script, "	       const char *key,\n");
	fprintf (script, "	       const char *filename,\n");
	fprintf (script, "	       const char *content_type,\n");
	fprintf (script, "	       const char *transfer_encoding,\n");
	fprintf (script, "	       const char *data, uint64_t off, size_t size)\n");
	fprintf (script, "{\n");
	fprintf (script, "	struct Request *request = (struct Request *) cls;\n");
	fprintf (script, "	struct Session *session = request->session;\n");
	fprintf (script, "\n");
	fprintf (script, "	printf(\"func: %%s, key: %%s, filename: %%s, content_type: %%s, transfer_encoding: %%s, offset: %%ld, size of data avlbl: %%ld\\n\",\n");
	fprintf (script, "		  __PRETTY_FUNCTION__, key, filename, content_type, transfer_encoding, off, size);\n");
	fprintf (script, "\n");
	// fprintf (script, "	if (0 == strcmp (\"DONE\", key)) {\n");
	// fprintf (script, "		fprintf (stdout,\n");
	// fprintf (script, "		       \"Session `%%s' submitted `%%s', `%%s'\\n\",\n");
	// fprintf (script, "		       session->sid,\n");
	// fprintf (script, "		       session->value_1,\n");
	// fprintf (script, "		       session->value_2);\n");
	// fprintf (script, "		cout << \"post_iterator finished\" << endl;\n");
	// fprintf (script, "		return MHD_YES;\n");
	// fprintf (script, "	}\n");
	fprintf (script, "\n");
	fprintf (script, "	if (0 == strcmp (\"last_question_answered\", key)) {\n");
	fprintf (script, "		if (size + off > sizeof(session->last_question_answered))\n");
	fprintf (script, "		size = sizeof (session->last_question_answered) - off;\n");
	fprintf (script, "		memcpy (&session->last_question_answered[off],\n");
	fprintf (script, "		      data,\n");
	fprintf (script, "		      size);\n");
	fprintf (script, "		if (size + off < sizeof (session->last_question_answered))\n");
	fprintf (script, "			session->last_question_answered[size+off] = '\\0';\n");
	fprintf (script, "		cout << \"post_iterator finished\" << endl;\n");
	fprintf (script, "		return MHD_YES;\n");
	fprintf (script, "	}\n");
	fprintf (script, "\n");
	fprintf (script, "	if (0 == strcmp (\"question_response\", key)) {\n");
	fprintf (script, "		if (size + off > sizeof(session->question_response))\n");
	fprintf (script, "		size = sizeof (session->question_response) - off;\n");
	fprintf (script, "		memcpy (&session->question_response[off],\n");
	fprintf (script, "		      data,\n");
	fprintf (script, "		      size);\n");
	fprintf (script, "		if (size + off < sizeof (session->question_response))\n");
	fprintf (script, "			session->question_response[size+off] = '\\0';\n");
	fprintf (script, "		cout << \"question_response : \" << session->question_response << endl;\n");
	fprintf (script, "		cout << \"post_iterator finished\" << endl;\n");
	fprintf (script, "		return MHD_YES;\n");
	fprintf (script, "	}\n");
	fprintf (script, "\n");
	fprintf (script, "	if (0 == strcmp (\"user_navigation\", key)) {\n");
	fprintf (script, "		if (size + off > sizeof(session->user_navigation))\n");
	fprintf (script, "		size = sizeof (session->user_navigation) - off;\n");
	fprintf (script, "		memcpy (&session->user_navigation[off],\n");
	fprintf (script, "		      data,\n");
	fprintf (script, "		      size);\n");
	fprintf (script, "		if (size + off < sizeof (session->user_navigation))\n");
	fprintf (script, "			session->user_navigation[size+off] = '\\0';\n");
	fprintf (script, "		cout << \"user_navigation : \" << session->user_navigation << endl;\n");
	fprintf (script, "		cout << \"post_iterator finished\" << endl;\n");
	fprintf (script, "		return MHD_YES;\n");
	fprintf (script, "	}\n");
	fprintf (script, "\n");
	fprintf (script, "	/*\n");
	fprintf (script, "	if (0 == strcmp (\"last_question_visited\", key))\n");
	fprintf (script, "	{\n");
	fprintf (script, "	if (size + off > sizeof(session->last_question_visited))\n");
	fprintf (script, "	size = sizeof (session->last_question_visited) - off;\n");
	fprintf (script, "	memcpy (&session->last_question_visited[off],\n");
	fprintf (script, "	      data,\n");
	fprintf (script, "	      size);\n");
	fprintf (script, "	if (size + off < sizeof (session->last_question_visited))\n");
	fprintf (script, "	session->last_question_visited[size+off] = '\\0';\n");
	fprintf (script, "	return MHD_YES;\n");
	fprintf (script, "	}\n");
	fprintf (script, "	*/\n");
	fprintf (script, "\n");
	fprintf (script, "	/* copy current_question to last_question_visited */\n");
	fprintf (script, "	if (0 == strcmp (\"current_question\", key)) {\n");
	fprintf (script, "		if (size + off > sizeof(session->last_question_visited))\n");
	fprintf (script, "		size = sizeof (session->last_question_visited) - off;\n");
	fprintf (script, "		memcpy (&session->last_question_visited[off],\n");
	fprintf (script, "		      data,\n");
	fprintf (script, "		      size);\n");
	fprintf (script, "		if (size + off < sizeof (session->last_question_visited))\n");
	fprintf (script, "		session->last_question_visited[size+off] = '\\0';\n");
	fprintf (script, "		cout << \"post_iterator finished\" << endl;\n");
	fprintf (script, "		return MHD_YES;\n");
	fprintf (script, "	}\n");

	fprintf (script, "\n");
	fprintf (script, "	fprintf (stderr, \"Unsupported form value `%%s'\\n\", key);\n");
	fprintf (script, "	return MHD_YES;\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");
	fprintf (script, "static struct Session *\n");
	fprintf (script, "get_session (struct MHD_Connection *connection)\n");
	fprintf (script, "{\n");
	fprintf (script, "  struct Session *ret;\n");
	fprintf (script, "  const char *cookie;\n");
	fprintf (script, "\n");
	fprintf (script, "  cookie = MHD_lookup_connection_value (connection,\n");
	fprintf (script, "					MHD_COOKIE_KIND,\n");
	fprintf (script, "					COOKIE_NAME);\n");
	fprintf (script, "  if (cookie != NULL)\n");
	fprintf (script, "    {\n");
	fprintf (script, "      /* find existing session */\n");
	fprintf (script, "      ret = sessions;\n");
	fprintf (script, "      while (NULL != ret)\n");
	fprintf (script, "	{\n");
	fprintf (script, "	  if (0 == strcmp (cookie, ret->sid))\n");
	fprintf (script, "	    break;\n");
	fprintf (script, "	  ret = ret->next;\n");
	fprintf (script, "	}\n");
	fprintf (script, "      if (NULL != ret)\n");
	fprintf (script, "	{\n");
	fprintf (script, "	  ret->rc++;\n");
	fprintf (script, "	  return ret;\n");
	fprintf (script, "	}\n");
	fprintf (script, "    }\n");
	fprintf (script, "  /* create fresh session */\n");
	fprintf (script, "\n");
	fprintf (script, "  /*\n");
	fprintf (script, "  ret = (struct Session *) calloc (1, sizeof (struct Session));\n");
	fprintf (script, "  ret->questionnaire = new TheQuestionnaire();\n");
	fprintf (script, "  if (NULL == ret)\n");
	fprintf (script, "    {						\n");
	fprintf (script, "      fprintf (stderr, \"calloc error: %%s\\n\", strerror (errno));\n");
	fprintf (script, "      return NULL; \n");
	fprintf (script, "    }\n");
	fprintf (script, "  snprintf (ret->sid,\n");
	fprintf (script, "	    sizeof (ret->sid),\n");
	fprintf (script, "	    \"%%X%%X%%X%%X\",\n");
	fprintf (script, "	    (unsigned int) random (),\n");
	fprintf (script, "	    (unsigned int) random (),\n");
	fprintf (script, "	    (unsigned int) random (),\n");
	fprintf (script, "	    (unsigned int) random ());\n");
	fprintf (script, "  ret->rc++;  \n");
	fprintf (script, "  ret->start = time (NULL);\n");
	fprintf (script, "  */\n");
	fprintf (script, "  ret = new Session();\n");
	fprintf (script, "  ret->next = sessions;\n");
	fprintf (script, "  sessions = ret;\n");
	fprintf (script, "  return ret;\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");
	fprintf (script, "static void\n");
	fprintf (script, "add_session_cookie (struct Session *session,\n");
	fprintf (script, "		    struct MHD_Response *response)\n");
	fprintf (script, "{\n");
	fprintf (script, "  char cstr[256];\n");
	fprintf (script, "  snprintf (cstr,\n");
	fprintf (script, "	    sizeof (cstr),\n");
	fprintf (script, "	    \"%%s=%%s\",\n");
	fprintf (script, "	    COOKIE_NAME,\n");
	fprintf (script, "	    session->sid);\n");
	fprintf (script, "  if (MHD_NO == \n");
	fprintf (script, "      MHD_add_response_header (response,\n");
	fprintf (script, "			       MHD_HTTP_HEADER_SET_COOKIE,\n");
	fprintf (script, "			       cstr))\n");
	fprintf (script, "    {\n");
	fprintf (script, "      fprintf (stderr, \n");
	fprintf (script, "	       \"Failed to set session cookie header!\\n\");\n");
	fprintf (script, "    }\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");
	fprintf (script, "\n");
	fprintf (script, "/*\n");
	fprintf (script, "static int\n");
	fprintf (script, "serve_simple_form (const void *cls,\n");
	fprintf (script, "		   const char *mime,\n");
	fprintf (script, "		   struct Session *session,\n");
	fprintf (script, "		   struct MHD_Connection *connection)\n");
	fprintf (script, "{\n");
	fprintf (script, "  int ret;\n");
	fprintf (script, "  const char *form = (const char *) cls;\n");
	fprintf (script, "  struct MHD_Response *response;\n");
	fprintf (script, "\n");
	fprintf (script, "  //  return static form \n");
	fprintf (script, "  response = MHD_create_response_from_buffer (strlen (form),\n");
	fprintf (script, "					      (void *) form,\n");
	fprintf (script, "					      MHD_RESPMEM_PERSISTENT);\n");
	fprintf (script, "  add_session_cookie (session, response);\n");
	fprintf (script, "  MHD_add_response_header (response,\n");
	fprintf (script, "			   MHD_HTTP_HEADER_CONTENT_ENCODING,\n");
	fprintf (script, "			   mime);\n");
	fprintf (script, "  ret = MHD_queue_response (connection, \n");
	fprintf (script, "			    MHD_HTTP_OK, \n");
	fprintf (script, "			    response);\n");
	fprintf (script, "  MHD_destroy_response (response);\n");
	fprintf (script, "  return ret;\n");
	fprintf (script, "}\n");
	fprintf (script, "*/\n");
	fprintf (script, "\n");
	fprintf (script, "static int\n");
	fprintf (script, "not_found_page (const void *cls,\n");
	fprintf (script, "		const char *mime,\n");
	fprintf (script, "		struct Session *session,\n");
	fprintf (script, "		struct MHD_Connection *connection)\n");
	fprintf (script, "{\n");
	fprintf (script, "  int ret;\n");
	fprintf (script, "  struct MHD_Response *response;\n");
	fprintf (script, "\n");
	fprintf (script, "  /* unsupported HTTP method */\n");
	fprintf (script, "  response = MHD_create_response_from_buffer (strlen (NOT_FOUND_ERROR),\n");
	fprintf (script, "					      (void *) NOT_FOUND_ERROR,\n");
	fprintf (script, "					      MHD_RESPMEM_PERSISTENT);\n");
	fprintf (script, "  ret = MHD_queue_response (connection, \n");
	fprintf (script, "			    MHD_HTTP_NOT_FOUND, \n");
	fprintf (script, "			    response);\n");
	fprintf (script, "  MHD_add_response_header (response,\n");
	fprintf (script, "			   MHD_HTTP_HEADER_CONTENT_ENCODING,\n");
	fprintf (script, "			   mime);\n");
	fprintf (script, "  MHD_destroy_response (response);\n");
	fprintf (script, "  return ret;\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");
	fprintf (script, "#include \"qscript_readline.h\"\n");

	fprintf (script, "bool verify_web_data (std::string p_question_data, \n");
	fprintf (script, "		UserNavigation p_user_navigation,\n");
	fprintf (script, "		user_response::UserResponseType p_the_user_response,\n");
	fprintf (script, "		std::vector<int> * data_ptr);\n");
	fprintf (script, " \n");
	fprintf (script, "static int serve_question(struct Session *session,\n");
	fprintf (script, "		 struct MHD_Connection *connection\n");
	fprintf (script, "		)\n");
	fprintf (script, "{\n");
	fprintf (script, "	cout << \"ENTER: \" << __PRETTY_FUNCTION__ << endl;\n");
	fprintf (script, "	UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;\n");
	fprintf (script, "	/*\n");
	fprintf (script, "	if (session->last_question_served == 0) {\n");
	fprintf (script, "		// this is the 1st question we are going to serve\n");
	fprintf (script, "		AbstractQuestion * q =\n");
	fprintf (script, "				session->questionnaire->eval2(last_question_answered, last_question_visited,\n");
	fprintf (script, "								qnre_navigation_mode);\n");
	fprintf (script, "		session->last_question_served = q;\n");
	fprintf (script, "	} else \n");
	fprintf (script, "	*/\n");
	fprintf (script, "	// first check that the response to the previous question is valid\n");
	fprintf (script, "\n");
	fprintf (script, "	string err_mesg, re_arranged_buffer;\n");
	fprintf (script, "	int32_t pos_1st_invalid_data;\n");
	fprintf (script, "	string last_question_visited_str = session->last_question_visited;\n");
	fprintf (script, "	string current_question_response = session->question_response;\n");
	fprintf (script, "	if (session->last_question_served) {\n");
	fprintf (script, "		if (last_question_visited_str != \"\" && current_question_response != \"\") {\n");
	fprintf (script, "			UserNavigation user_nav=NOT_SET;\n");
	fprintf (script, "			user_response::UserResponseType user_resp=user_response::NotSet;\n");
	fprintf (script, "			vector<int32_t> data;\n");
	fprintf (script, "			bool parse_success = verify_web_data (current_question_response, user_nav, user_resp, &data);\n");
	fprintf (script, "			//if (parse_success) {\n");
	fprintf (script, "			//	cout << \"successfully parsed data = \";\n");
	fprintf (script, "			//	for (int i=0; i<data.size(); ++i) {\n");
	fprintf (script, "			//		cout << data[i] << \", \";\n");
	fprintf (script, "			//	}\n");
	fprintf (script, "			//	cout << endl;\n");
	fprintf (script, "			//}\n");
	fprintf (script, "			AbstractQuestion * last_question_served = session->last_question_served;\n");
	fprintf (script, "			// the call below will be required at some later stage\n");
	fprintf (script, "			//bool valid_input = AbstractQuestion::VerifyResponse(user_resp);\n");
	fprintf (script, "			// right now we go along with the happy path\n");
	fprintf (script, "			bool invalid_code = last_question_served->VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data,\n");
	fprintf (script, "					&data);\n");
	fprintf (script, "			if (invalid_code == false) {\n");
	fprintf (script, "				//last_question_served->input_data.erase\n");
	fprintf (script, "				//	(last_question_served->input_data.begin(), \n");
	fprintf (script, "				//	 last_question_served->input_data.end());\n");
	fprintf (script, "				last_question_served->input_data.clear();\n");
	fprintf (script, "				for(uint32_t i = 0; i < data.size(); ++i){\n");
	fprintf (script, "					last_question_served->input_data.insert(data[i]);\n");
	fprintf (script, "					//cout << \"storing: \" << data[i]\n");
	fprintf (script, "					//	<< \" into input_data\" << endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "				last_question_served->isAnswered_ = true;\n");
	fprintf (script, "				data.clear();\n");
	fprintf (script, "			}\n");
	fprintf (script, "		}\n");
	fprintf (script, "	}\n");
	fprintf (script, "	AbstractQuestion * q =\n");
	fprintf (script, "			session->questionnaire->eval2(/*session->ptr_last_question_answered, session->ptr_last_question_visited,*/\n");
	fprintf (script, "							qnre_navigation_mode);\n");
	fprintf (script, "	session->last_question_served = q;\n");
	fprintf (script, "label_ask_again:\n");
	fprintf (script, "	stringstream question_form;\n");
	fprintf (script, "\n");
	fprintf (script, "	cout << \"last_question_visited == \" << last_question_visited_str << endl;\n");
	fprintf (script, "	cout << \"current_question_response == \" << current_question_response << endl;\n");
	fprintf (script, "\n");
	fprintf (script, "	\n");
	fprintf (script, "\n");
	fprintf (script, "	question_form << \"<html><head><title>\"\n");
	fprintf (script, "		<< \"Questionnaire: \" << session->questionnaire->jno\n");
	fprintf (script, "		<< \"</title>\\n\";\n");
	fprintf (script, "	//question_form << \"<script type=\\\"text/javascript\\\" src=\\\"event_util.js\\\" ></script>\\n\";\n");
	fprintf (script, "	fstream event_js_file(\"event_util.js\", ios_base::in);\n");
	fprintf (script, "	string event_js_file_contents;\n");
	fprintf (script, "	stringstream event_js_file_contents_str;\n");
	fprintf (script, "	cout << \"reading file: event_js_file\" << endl;\n");
	fprintf (script, "	while (getline (event_js_file, event_js_file_contents) ) {\n");
	fprintf (script, "		// cout << \"contents: \" << event_js_file_contents << endl;\n");
	fprintf (script, "		event_js_file_contents_str << event_js_file_contents << endl;\n");
	fprintf (script, "	}\n");
	fprintf (script, "\n");
	fprintf (script, "	question_form << \"<script type=\\\"text/javascript\\\" >\\n\";\n");
	fprintf (script, "	question_form << event_js_file_contents_str.str().c_str() << endl;\n");
	fprintf (script, "	question_form << \"</script>\\n\";\n");
	fprintf (script, "\n");
	fprintf (script, "	question_form << \"</head>\\n<body>\\n\";\n");
	fprintf (script, "	question_form << \"\\t<form action=\\\"\" << q->questionName_ \n");
	fprintf (script, "		<< \"\\\" method=\\\"post\\\">\\n\" \n");
	fprintf (script, "		<< q->questionName_ << \".\";\n");
	fprintf (script, "	for(int32_t i = 0; i< q->loop_index_values.size(); ++i){\n");
	fprintf (script, "		question_form << \".\" << q->loop_index_values[i];\n");
	fprintf (script, "	}\n");
	fprintf (script, "\n");
	fprintf (script, "	question_form << q->textExprVec_[0]->text_\n");
	fprintf (script, "		<< endl;\n");
	fprintf (script, "	question_form\n");
	fprintf (script, "		<< \"\\t\\t<input type=\\\"text\\\" name=\\\"question_response\\\"\" \n");
	fprintf (script, "		<< \"value=\\\"\"\n");
	fprintf (script, "		// put the value here later\n");
	fprintf (script, "		<< \"\\\" />\\n\";\n");
	fprintf (script, "\n");
	fprintf (script, "	question_form << \"<p>\";\n");
	fprintf (script, "\n");
	fprintf (script, "\n");
	fprintf (script, "	question_form\n");
	fprintf (script, "		// << \"\\t\\t<input type=\\\"hidden\\\" name=\\\"last_question_answered\\\" \";\n");
	fprintf (script, "		<< \"\\t\\t last_question_answered: <input type=\\\"text\\\" name=\\\"last_question_answered\\\" \";\n");
	fprintf (script, "	/*\n");
	fprintf (script, "	if (session->last_question_answered) {\n");
	fprintf (script, "		question_form\n");
	fprintf (script, "			<< \" value=\\\"\"\n");
	fprintf (script, "			<< last_question_answered->questionName_ \n");
	fprintf (script, "			<< \"\\\"\";\n");
	fprintf (script, "	} else {\n");
	fprintf (script, "		question_form\n");
	fprintf (script, "			<< \" value=\\\"\"\n");
	fprintf (script, "			<< \"\\\"\";\n");
	fprintf (script, "	}\n");
	fprintf (script, "	*/\n");
	fprintf (script, "	question_form << \"value =\\\"\" << session->last_question_answered \n");
	fprintf (script, "			<< \"\\\"\"\n");
	fprintf (script, "			<< \" />\\n\";\n");
	fprintf (script, "\n");
	fprintf (script, "	question_form\n");
	fprintf (script, "		<< \"\\t\\t last_question_visited: <input type=\\\"text\\\" name=\\\"last_question_visited\\\" \";\n");
	fprintf (script, "	/*\n");
	fprintf (script, "	if (session->last_question_visited) {\n");
	fprintf (script, "		question_form\n");
	fprintf (script, "			<< \" value=\\\"\"\n");
	fprintf (script, "			<< last_question_visited->questionName_ \n");
	fprintf (script, "			<< \"\\\"\";\n");
	fprintf (script, "	} else {\n");
	fprintf (script, "		question_form\n");
	fprintf (script, "			<< \" value=\\\"\"\n");
	fprintf (script, "			<< \"\\\"\";\n");
	fprintf (script, "	}\n");
	fprintf (script, "	*/\n");
	fprintf (script, "	question_form << \"value =\\\"\" << session->last_question_visited \n");
	fprintf (script, "			<< \"\\\"\"\n");
	fprintf (script, "			<< \" />\\n\";\n");
	fprintf (script, "\n");
	fprintf (script, "	question_form\n");
	fprintf (script, "		<< \"\\t\\t current_question: <input type=\\\"text\\\" name=\\\"current_question\\\" \";\n");
	fprintf (script, "	question_form << \"value =\\\"\" << q->questionName_;\n");
	fprintf (script, "\n");
	fprintf (script, "	for (int i=0; i<q->loop_index_values.size(); ++i) {\n");
	fprintf (script, "		question_form << \"$\" << q->loop_index_values[i];\n");
	fprintf (script, "	}\n");
	fprintf (script, "	question_form\n");
	fprintf (script, "		<< \"\\\"\"\n");
	fprintf (script, "		<< \" />\\n\";\n");
	fprintf (script, "\n");
	fprintf (script, "	question_form << \"		user_navigation: <input type=\\\"text\\\" name=\\\"user_navigation\\\" value =\\\"\\\" /> \" << endl;\n");
	fprintf (script, "	question_form << \"		<input type=\\\"button\\\" value=\\\"Previous\\\" name=\\\"prev_button\\\" id=\\\"prev_button\\\" /> \" << endl;\n");
	fprintf (script, "	question_form << \"		<input type=\\\"button\\\" value=\\\"Next\\\" name=\\\"next_button\\\" id=\\\"next_button\\\" /> \" << endl;\n");
	fprintf (script, "	question_form << \"		<input type=\\\"button\\\" id=\\\"form_button\\\" value=\\\"button\\\" />\" << endl;\n");
	fprintf (script, "\n");
	fprintf (script, "	question_form << \"	<script type=\\\"text/javascript\\\">\\n\";\n");
	fprintf (script, "	question_form << \"	var form = document.forms[0];\\n\";\n");
	fprintf (script, "	question_form << \"	var form_button = form.elements[\\\"form_button\\\"];\\n\";\n");
	fprintf (script, "	question_form << \"	//var form_button = document.getElementById(\\\"form_button\\\");\\n\";\n");
	fprintf (script, "	question_form << \"	//alert ('form_button' +  form_button);\\n\";\n");
	fprintf (script, "	question_form << \"	var handler = function () {\\n\";\n");
	fprintf (script, "	question_form << \"		//alert(\\\"handler executed on click\\\");\\n\";\n");
	fprintf (script, "	question_form << \"		var user_navigation = form.elements[\\\"user_navigation\\\"];\\n\";\n");
	fprintf (script, "	question_form << \"		user_navigation.value = \\\"previous\\\";\\n\";\n");
	fprintf (script, "	question_form << \"	}\\n\";\n");
	fprintf (script, "	question_form << \"	EventUtil.addHandler(form_button, \\\"click\\\", handler);\\n\";\n");
	fprintf (script, "	question_form << \"	//alert(\\\"added handler to button\\\");\\n\";\n");
	fprintf (script, "	question_form << \"	// the real stuff I want to do goes here\\n\";\n");
	fprintf (script, "	question_form << \"	// 1. when user clicks button previous \\n\";\n");
	fprintf (script, "	question_form << \"	//    set user_navigation to previous\\n\";\n");
	fprintf (script, "	question_form << \"	//    and submit the form\\n\";\n");
	fprintf (script, "	question_form << \"	var prev_button = form.elements[\\\"prev_button\\\"]\\n\";\n");
	fprintf (script, "	question_form << \"	var handle_prev = function() {\\n\";\n");
	fprintf (script, "	question_form << \"		var user_navigation = form.elements[\\\"user_navigation\\\"];\\n\";\n");
	fprintf (script, "	question_form << \"		user_navigation.value = \\\"previous\\\";\\n\";\n");
	fprintf (script, "	question_form << \"		prev_button.disabled = true;\\n\";\n");
	fprintf (script, "	question_form << \"		next_button.disabled = true;\\n\";\n");
	fprintf (script, "	question_form << \"		form.submit();\\n\";\n");
	fprintf (script, "	question_form << \"	}\\n\";\n");
	fprintf (script, "	question_form << \"	EventUtil.addHandler(prev_button, \\\"click\\\", handle_prev);\\n\";\n");
	fprintf (script, "	question_form << \"\\n\";\n");
	fprintf (script, "	question_form << \"	// 2. when user clicks button next\\n\";\n");
	fprintf (script, "	question_form << \"	//    set user_navigation to next\\n\";\n");
	fprintf (script, "	question_form << \"	//    and submit the form\\n\";\n");
	fprintf (script, "	question_form << \"	var next_button = form.elements[\\\"next_button\\\"]\\n\";\n");
	fprintf (script, "	question_form << \"	var handle_next = function(event) {\\n\";\n");
	fprintf (script, "	question_form << \"		var user_navigation = form.elements[\\\"user_navigation\\\"];\\n\";\n");
	fprintf (script, "	question_form << \"		user_navigation.value = \\\"next\\\";\\n\";\n");
	fprintf (script, "	question_form << \"		prev_button.disabled = true;\\n\";\n");
	fprintf (script, "	question_form << \"		next_button.disabled = true;\\n\";\n");
	fprintf (script, "	question_form << \"		//event = EventUtil.getEvent(event);\\n\";\n");
	fprintf (script, "	question_form << \"		//EventUtil.preventDefault(event);\\n\";\n");
	fprintf (script, "	question_form << \"		form.submit();\\n\";\n");
	fprintf (script, "	question_form << \"	}\\n\";\n");
	fprintf (script, "	question_form << \"	EventUtil.addHandler(next_button, \\\"click\\\", handle_next);\\n\";\n");
	fprintf (script, "	question_form << \"	</script>\\n\";\n");
	fprintf (script, "	question_form << \"\\n\";\n");
	fprintf (script, "\n");
	fprintf (script, "	question_form << \"\\n</body></html>\\n\";\n");
	fprintf (script, "	struct MHD_Response * response  = MHD_create_response_from_buffer(question_form.str().length(),\n");
	fprintf (script, "									(void *) question_form.str().c_str(),\n");
	fprintf (script, "									MHD_RESPMEM_MUST_COPY);\n");
	fprintf (script, "	add_session_cookie (session, response);\n");
	fprintf (script, "	const char * mime = \"text/html\";\n");
	fprintf (script, "	MHD_add_response_header (response,\n");
	fprintf (script, "				 MHD_HTTP_HEADER_CONTENT_ENCODING,\n");
	fprintf (script, "				 mime);\n");
	fprintf (script, "	int ret = MHD_queue_response (connection, MHD_HTTP_OK, response);\n");
	fprintf (script, "	MHD_destroy_response (response);\n");
	fprintf (script, "\n");
	fprintf (script, "	cout << \"EXIT: \" << __PRETTY_FUNCTION__ << endl;\n");
	fprintf (script, "	return ret;\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");
}

void print_microhttpd_include_files (FILE * script)
{
	fprintf (script, "#define _GNU_SOURCE\n");
	fprintf (script, "#include <stdlib.h>\n");
	fprintf (script, "#include <string.h>\n");
	fprintf (script, "#include <stdio.h>\n");
	fprintf (script, "#include <errno.h>\n");
	fprintf (script, "#include <time.h>\n");
	fprintf (script, "#include <microhttpd.h>\n");
}

void print_microhttpd_web_support_structs (FILE * script)
{
	fprintf (script, "/**\n");
	fprintf (script, " * Invalid method page.\n");
	fprintf (script, " */\n");
	fprintf (script, "#define METHOD_ERROR \"<html><head><title>Illegal request</title></head><body>Go away.</body></html>\"\n");
	fprintf (script, "\n");
	fprintf (script, "/**\n");
	fprintf (script, " * Invalid URL page.\n");
	fprintf (script, " */\n");
	fprintf (script, "#define NOT_FOUND_ERROR \"<html><head><title>Not found</title></head><body>Go away.</body></html>\"\n");
	fprintf (script, "\n");
	fprintf (script, "/**\n");
	fprintf (script, " * Last page.\n");
	fprintf (script, " */\n");
	fprintf (script, "#define LAST_PAGE \"<html><head><title>Thank you</title></head><body>Thank you.</body></html>\"\n");
	fprintf (script, "\n");
	fprintf (script, "#define COOKIE_NAME \"session\"\n");
	fprintf (script, "\n");
	fprintf (script, "struct Request\n");
	fprintf (script, "{\n");
	fprintf (script, "  /**\n");
	fprintf (script, "   * Associated session.\n");
	fprintf (script, "   */\n");
	fprintf (script, "  struct Session *session;\n");
	fprintf (script, "  /**\n");
	fprintf (script, "   * Post processor handling form data (IF this is\n");
	fprintf (script, "   * a POST request).\n");
	fprintf (script, "   */\n");
	fprintf (script, "  struct MHD_PostProcessor *pp;\n");
	fprintf (script, "  /**\n");
	fprintf (script, "   * URL to serve in response to this POST (if this request \n");
	fprintf (script, "   * was a 'POST')\n");
	fprintf (script, "   */\n");
	fprintf (script, "  const char *post_url;\n");
	fprintf (script, "};\n");
	fprintf (script, "\n");
	fprintf (script, "\n");
	fprintf (script, "\n");
}

void print_web_support_structs (FILE * script)
{

	fprintf (script, "struct Session\n");
	fprintf (script, "{\n");
	fprintf (script, "	/**\n");
	fprintf (script, "	* We keep all sessions in a linked list.\n");
	fprintf (script, "	*/\n");
	fprintf (script, "	struct Session *next;\n");
	fprintf (script, "	/**\n");
	fprintf (script, "	* Unique ID for this session. \n");
	fprintf (script, "	*/\n");
	fprintf (script, "	char sid[33];\n");
	fprintf (script, "	/**\n");
	fprintf (script, "	* Reference counter giving the number of connections\n");
	fprintf (script, "	* currently using this session.\n");
	fprintf (script, "	*/\n");
	fprintf (script, "	unsigned int rc;\n");
	fprintf (script, "	/**\n");
	fprintf (script, "	* Time when this session was last active.\n");
	fprintf (script, "	*/\n");
	fprintf (script, "	time_t start;\n");
	fprintf (script, "\n");
	fprintf (script, "	struct TheQuestionnaire * questionnaire;\n");
	fprintf (script, "	char last_question_answered[200];\n");
	fprintf (script, "	char last_question_visited[200];\n");
	fprintf (script, "	char question_response[200];\n");
	fprintf (script, "	char user_navigation[200];\n");
	fprintf (script, "	AbstractQuestion * last_question_served;\n");
	fprintf (script, "	AbstractQuestion * ptr_last_question_answered;\n");
	fprintf (script, "	AbstractQuestion * ptr_last_question_visited;\n");
	fprintf (script, "	Session()\n");
	fprintf (script, "		: start(time(NULL)),\n");
	fprintf (script, "		  questionnaire(new TheQuestionnaire(\"dummy\")),\n");
	fprintf (script, "		  rc(1), last_question_served(0),\n");
	fprintf (script, "		  ptr_last_question_answered(0),\n");
	fprintf (script, "		  ptr_last_question_visited(0)\n");
	fprintf (script, "	{ \n");
	fprintf (script, "		snprintf (sid,\n");
	fprintf (script, "		    sizeof (sid),\n");
	fprintf (script, "		    \"%%X%%X%%X%%X\",\n");
	fprintf (script, "		    (unsigned int) random (),\n");
	fprintf (script, "		    (unsigned int) random (),\n");
	fprintf (script, "		    (unsigned int) random (),\n");
	fprintf (script, "		    (unsigned int) random ());\n");
	fprintf (script, "		memset(last_question_answered, 0, sizeof(last_question_answered));\n");
	fprintf (script, "		memset(last_question_visited, 0, sizeof(last_question_visited));\n");
	fprintf (script, "	}\n");
	fprintf(script, "	~Session()\n");
	fprintf(script, "	{\n");
	fprintf(script, "		delete questionnaire;\n");
	fprintf(script, "		questionnaire = 0;\n");
	fprintf(script, "	}\n");
	fprintf (script, "};\n");
	fprintf (script, "\n");
	fprintf (script, "static struct Session *sessions;\n");
	fprintf (script, "vector <Session*> wt_sessions;\n");
}

void print_web_func_prototypes (FILE * script)
{
	fprintf(script, "\n");
	fprintf(script, "static int\n");
	fprintf(script, "post_iterator (void *cls,\n");
	fprintf(script, "	       enum MHD_ValueKind kind,\n");
	fprintf(script, "	       const char *key,\n");
	fprintf(script, "	       const char *filename,\n");
	fprintf(script, "	       const char *content_type,\n");
	fprintf(script, "	       const char *transfer_encoding,\n");
	fprintf(script, "	       const char *data, uint64_t off, size_t size);\n");
	fprintf(script, "\n");
	fprintf(script, "int setup_and_run_MHD_daemon();\n");
	fprintf(script, "\n");
	fprintf(script, "static struct Session *\n");
	fprintf(script, "get_session (struct MHD_Connection *connection);\n");
	fprintf(script, "static void\n");
	fprintf(script, "request_completed_callback (void *cls,\n");
	fprintf(script, "			    struct MHD_Connection *connection,\n");
	fprintf(script, "			    void **con_cls,\n");
	fprintf(script, "			    enum MHD_RequestTerminationCode toe);\n");
	fprintf(script, "\n");
	fprintf(script, "static int\n");
	fprintf(script, "create_response (void *cls,\n");
	fprintf(script, "		 struct MHD_Connection *connection,\n");
	fprintf(script, "		 const char *url,\n");
	fprintf(script, "		 const char *method,\n");
	fprintf(script, "		 const char *version,\n");
	fprintf(script, "		 const char *upload_data, \n");
	fprintf(script, "		 size_t *upload_data_size,\n");
	fprintf(script, "		 void **ptr);\n");
	fprintf(script, "\n");
	fprintf(script, "typedef int (*PageHandler)(const void *cls,\n");
	fprintf(script, "			   const char *mime,\n");
	fprintf(script, "			   struct Session *session,\n");
	fprintf(script, "			   struct MHD_Connection *connection);\n");
	fprintf(script, "struct Page\n");
	fprintf(script, "{\n");
	fprintf(script, "  /**\n");
	fprintf(script, "   * Acceptable URL for this page.\n");
	fprintf(script, "   */\n");
	fprintf(script, "  const char *url;\n");
	fprintf(script, "\n");
	fprintf(script, "  /**\n");
	fprintf(script, "   * Mime type to set for the page.\n");
	fprintf(script, "   */\n");
	fprintf(script, "  const char *mime;\n");
	fprintf(script, "\n");
	fprintf(script, "  /**\n");
	fprintf(script, "   * Handler to call to generate response.\n");
	fprintf(script, "   */\n");
	fprintf(script, "  PageHandler handler;\n");
	fprintf(script, "\n");
	fprintf(script, "  /**\n");
	fprintf(script, "   * Extra argument to handler.\n");
	fprintf(script, "   */ \n");
	fprintf(script, "  const void *handler_cls;\n");
	fprintf(script, "};\n");
	fprintf(script, "static void\n");
	fprintf(script, "add_session_cookie (struct Session *session,\n");
	fprintf(script, "		    struct MHD_Response *response);\n");
	fprintf(script, "\n");
	fprintf(script, "static int\n");
	fprintf(script, "not_found_page (const void *cls,\n");
	fprintf(script, "		const char *mime,\n");
	fprintf(script, "		struct Session *session,\n");
	fprintf(script, "		struct MHD_Connection *connection);\n");
	fprintf(script, "\n");
	fprintf(script, "static int serve_question(struct Session *session,\n");
	fprintf(script, "		 struct MHD_Connection *connection\n");
	fprintf(script, "		);\n");
	fprintf(script, "\n");
}

void print_Wt_support_code(FILE * script)
{
	// 2-jul-2013
	// Dont need all this - except for Validateserialno
#if 0
	fprintf(script, "using namespace Wt;\n");
	fprintf(script, "\n");
	fprintf(script, "class QuestionnaireApplication: public WApplication\n");
	fprintf(script, "{\n");
	fprintf(script, "public: \n");
	fprintf(script, "	QuestionnaireApplication(const WEnvironment &env);\n");
	fprintf(script, "private:\n");
	fprintf(script, "	WText * wt_debug_;\n");
	fprintf(script, "	WText * wt_questionText_;\n");
	fprintf(script, "	WLineEdit * le_data_;\n");
	fprintf(script, "	WText * wt_lastQuestionVisited_;\n");
	fprintf (script, "	WGroupBox * wt_cb_rb_container_;\n");
	fprintf (script, "	WButtonGroup * wt_rb_container_;\n");
	fprintf (script, "	vector<WRadioButton*> vec_rb;\n");
	fprintf (script, "	vector<WCheckBox*> vec_cb;\n");
	fprintf (script, "	std::map<int, int> map_cb_code_index;\n");
	fprintf (script, "	std::vector<WText *> languageSelects_;\n");


	fprintf(script, "\n");
	fprintf(script, "	WContainerWidget viewPort_;\n");
	fprintf(script, "	//WWidget * currentForm_;\n");
	fprintf(script, "		WContainerWidget * currentForm_;\n");
	fprintf(script, "	WContainerWidget * formContainer_;\n");
	fprintf(script, "	int ser_no;\n");
	fprintf(script, "		WContainerWidget * serialPage_;\n");
	fprintf(script, "		bool flagSerialPageRemoved_;\n");
	fprintf(script, "		Session * this_users_session;\n");
	fprintf(script, "		string sess_id ;\n");
	fprintf(script, "\n");
	fprintf(script, "	void display();\n");
	fprintf(script, "	void DoQuestionnaire() ;\n");
	fprintf(script, "	//void setCentralWidget(WWidget * new_question_form);\n");
	fprintf(script, "	void setCentralWidget(WContainerWidget * new_question_form);\n");
	fprintf(script, "	void changeLanguage();\n");
	fprintf(script, "	void setLanguage(const std::string lang);\n");
	fprintf(script, "	void ConstructQuestionForm(\n");
	fprintf(script, "		AbstractQuestion *q, Session * this_users_session);\n");
	fprintf(script, "	void ValidateSerialNo();\n");
	fprintf(script, " 	void ConstructThankYouPage();\n");
	fprintf(script, " 	const char * software_info();\n");
	fprintf(script, "		virtual ~QuestionnaireApplication();\n");
	fprintf(script, "};\n");

	fprintf(script, "\n");
	fprintf(script, "QuestionnaireApplication::~QuestionnaireApplication()\n");
	fprintf(script, "{\n");
	fprintf(script, "	delete this_users_session; 	this_users_session=0;\n");
	fprintf(script, "	delete serialPage_; 		serialPage_ = 0;\n");
	fprintf(script, "	if (currentForm_) {\n");
	fprintf(script, "		delete currentForm_; 	currentForm_ = 0;\n");
	fprintf(script, "	}\n");
	fprintf(script, "	cout << __PRETTY_FUNCTION__ << endl;\n");
	fprintf(script, "}\n");
	fprintf(script, "\n");
#endif /* 0 */
	fprintf(script, "void QuestionnaireApplication::ValidateSerialNo()\n");
	fprintf(script, "{\n");
	fprintf(script, "	int l_ser_no = -1;\n");
	fprintf(script, "	if (le_SerialNo_ ) {\n");
	fprintf(script, "		Wt::WString serno_text = le_SerialNo_->text();\n");
	fprintf(script, "		string narrow_text = serno_text.narrow();\n");
	fprintf(script, "		if (narrow_text.length() == 0 || narrow_text.length()>7) {\n");
	fprintf(script, "			le_SerialNo_->setText(\"You have entered a very long serial number\");\n");
	fprintf(script, "		} else {\n");
	fprintf(script, "			l_ser_no = strtol (narrow_text.c_str(), 0, 10);\n");
	fprintf(script, "			if (l_ser_no > 0) {\n");
	fprintf(script, "				ser_no = l_ser_no;\n");
	fprintf(script, "				//this_users_session->questionnaire->ser_no = l_ser_no;\n");
	fprintf(script, "				int exists = check_if_reg_file_exists(jno, ser_no);\n");
	fprintf(script, "				cout << \"checking if serial no : \" << ser_no \n");
	fprintf(script, "					<< \", jno: \" << jno << \" exists: \" << exists << endl;\n");
	fprintf(script, "\n");
	fprintf(script, "				if(exists == 1){\n");
	fprintf(script, " 					map <string, question_disk_data*>  qdd_map;\n");
	fprintf(script, "					load_data(jno, ser_no, &qdd_map);\n");
	fprintf(script, "					//merge_disk_data_into_questions(qscript_stdout, last_question_answered, last_question_visited);\n");
	fprintf(script, "					merge_disk_data_into_questions2(qscript_stdout,\n");
	fprintf(script, "							this_users_session->theQuestionnaire_->last_question_answered,\n");
	fprintf(script, "							this_users_session->theQuestionnaire_->last_question_visited,\n");
	fprintf(script, "							this_users_session->theQuestionnaire_->question_list,\n");
	fprintf(script, "							&qdd_map);\n");
	fprintf(script, "					for (map<string, question_disk_data*>:: iterator it \n");
	fprintf(script, "							= qdd_map.begin();\n");
	fprintf(script, "							it != qdd_map.end();\n");
	fprintf(script, "							++it) {\n");
	fprintf(script, "						delete it->second;\n");
	fprintf(script, "					}\n");
	fprintf(script, "				}\n");
	fprintf(script, "				//DoQuestionnaire();\n");
	fprintf(script, "				callback_get_ser_no_from_ui (l_ser_no, this_users_session->theQuestionnaire_ , 1);\n");
	fprintf(script, "			} else {\n");
	fprintf(script, "				le_SerialNo_->setText(\"You have entered a  negative number\");\n");
	fprintf(script, "			}\n");
	fprintf(script, "		}\n");
	fprintf(script, "	}\n");
	fprintf(script, "}\n");
	fprintf(script, "\n");

#if 0
	fprintf(script, "bool verify_web_data (std::string p_question_data, \n");
	fprintf(script, "		UserNavigation p_user_navigation,\n");
	fprintf(script, "		user_response::UserResponseType p_the_user_response,\n");
	fprintf(script, "		std::vector<int> * data_ptr);\n");
	fprintf(script, "\n");
	fprintf(script, "\n");
	fprintf(script, "void QuestionnaireApplication::DoQuestionnaire()\n");
	fprintf(script, "{\n");
	fprintf(script, "	//if (!wt_questionText_) {\n");
	fprintf(script, "	//	wt_questionText_ = new WText(root());\n");
	fprintf(script, "	//}\n");
	fprintf(script, "	cout << \"Data for ser_no: \" << ser_no;\n");
	fprintf(script, "	for(int32_t i = 0; i < this_users_session->questionnaire->question_list.size(); ++i)\n");
	fprintf(script, "	{\n");
	fprintf(script, "		cout << this_users_session->questionnaire->question_list[i]->questionName_;\n");
	fprintf(script, "		for( set<int32_t>::iterator iter = this_users_session->questionnaire->question_list[i]->input_data.begin();\n");
	fprintf(script, "				iter != this_users_session->questionnaire->question_list[i]->input_data.end(); ++iter){\n");
	fprintf(script, "			cout << \" \" << *iter;\n");
	fprintf(script, "		}\n");
	fprintf(script, "		cout << \"\\n\";\n");
	fprintf(script, "	}\n");

	fprintf(script, "	static int counter = 0;\n");
	fprintf(script, "	stringstream s;\n");
	fprintf(script, "	s << \"reached DoQuestionnaire: \" << counter++;\n");
	fprintf(script, "	wt_debug_->setText(s.str());\n");
	fprintf(script, "	UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;\n");
	//fprintf(script, "	string sess_id = sessionId();\n");
	fprintf(script, "	string display_text = string(\"Session Id:\") + sess_id;\n");
	fprintf(script, "	wt_questionText_->setText(display_text);\n");
	/*
	fprintf(script, "	int found_index = -1;\n");
	fprintf(script, "	for (int i=0; i<wt_sessions.size(); ++i) {\n");
	fprintf(script, "		// boy is the below inefficient and should be fixed\n");
	fprintf(script, "		if (sess_id == string(wt_sessions[i]->sid) ) {\n");
	fprintf(script, "			found_index = i;\n");
	fprintf(script, "			break;\n");
	fprintf(script, "		}\n");
	fprintf(script, "	}\n");
	fprintf(script, "	Session * this_users_session = 0;\n");
	fprintf(script, "	if (found_index != -1) {\n");
	fprintf(script, "		s << \"found session at index: \" << found_index;\n");
	fprintf(script, "		this_users_session = wt_sessions[found_index];\n");
	fprintf(script, "	} else {\n");
	fprintf(script, "		this_users_session = new Session();\n");
	fprintf(script, " 		this_users_session->questionnaire->ser_no = ser_no;\n");
	fprintf(script, "		strcpy(this_users_session->sid, sess_id.c_str());\n");
	fprintf(script, "		wt_sessions.push_back(this_users_session);\n");
	fprintf(script, "	}\n");
	*/
	fprintf(script, "	// put this code later\n");
	fprintf(script, "	string err_mesg, re_arranged_buffer;\n");
	fprintf(script, "	int32_t pos_1st_invalid_data;\n");
	fprintf(script, "	s << \"last_question_served: \" << this_users_session->last_question_served;\n");
	fprintf(script, "	wt_debug_->setText(s.str());\n");

	// fprintf(script, "	if (this_users_session->last_question_served)\n");
	// fprintf(script, "	{\n");
	// fprintf(script, "		if (last_question_visited_str != \"\" && current_question_response != \"\")\n");
	// fprintf(script, "		{\n");
	// fprintf(script, "			UserNavigation user_nav=NOT_SET;\n");
	// fprintf(script, "			user_response::UserResponseType user_resp=user_response::NotSet;\n");
	// fprintf(script, "			vector<int32_t> data;\n");
	// fprintf(script, "			bool parse_success = verify_web_data (current_question_response, user_nav, user_resp, &data);\n");
	// fprintf(script, "			if (parse_success)\n");
	// fprintf(script, "			{\n");
	// fprintf(script, "				cout << \"successfully parsed data = \";\n");
	// fprintf(script, "				for (int i=0; i<data.size(); ++i)\n");
	// fprintf(script, "				{\n");
	// fprintf(script, "					cout << data[i] << \", \";\n");
	// fprintf(script, "				}\n");
	// fprintf(script, "				cout << endl;\n");
	// fprintf(script, "			}\n");
	// fprintf(script, "			AbstractQuestion * last_question_served = this_users_session->last_question_served;\n");
	// fprintf(script, "			// the call below will be required at some later stage\n");
	// fprintf(script, "			//bool valid_input = AbstractQuestion::VerifyResponse(user_resp);\n");
	// fprintf(script, "			// right now we go along with the happy path\n");
	// fprintf(script, "			bool invalid_code = last_question_served->VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data,\n");
	// fprintf(script, "				&data);\n");
	// fprintf(script, "			if (invalid_code == false)\n");
	// fprintf(script, "			{\n");
	// fprintf(script, "				last_question_served->input_data.erase\n");
	// fprintf(script, "					(last_question_served->input_data.begin(),\n");
	// fprintf(script, "					last_question_served->input_data.end());\n");
	// fprintf(script, "				for(uint32_t i = 0; i < data.size(); ++i)\n");
	// fprintf(script, "				{\n");
	// fprintf(script, "					last_question_served->input_data.insert(data[i]);\n");
	// fprintf(script, "					//cout << \"storing: \" << data[i]\n");
	// fprintf(script, "					//	<< \" into input_data\" << endl;\n");
	// fprintf(script, "				}\n");
	// fprintf(script, "				last_question_served->isAnswered_ = true;\n");
	// fprintf(script, "				data.clear();\n");
	// fprintf(script, "			}\n");
	// fprintf(script, "		}\n");
	// fprintf(script, "	}\n");

	fprintf(script, "	if (this_users_session->last_question_served)\n");
	fprintf (script, "	{\n");
	fprintf (script, "		if (NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion *>(this_users_session->last_question_served)) {\n");
	fprintf (script, "			AbstractQuestion * last_question_served = this_users_session->last_question_served;\n");
	fprintf (script, "			vector<int32_t> data;\n");
	fprintf (script, "			bool isAnswered = false;\n");
	fprintf (script, " 			cout << \"returned back data from question: \" << nq->questionName_ << endl;\n");
	fprintf (script, "			if (last_question_served->no_mpn == 1) {\n");
	fprintf (script, "				if ( wt_rb_container_->selectedButtonIndex() != -1) {\n");
	fprintf (script, "					isAnswered = true;\n");
	fprintf (script, "					int code = wt_rb_container_->checkedId();\n");
	fprintf (script, "					cout << \"no_mpn == 1, code: \" << code << endl;\n");
	fprintf (script, "					data.push_back(code);\n");
	fprintf (script, "				} else {\n");
	fprintf (script, "					isAnswered = false;\n");
	fprintf (script, "				}\n");
	fprintf (script, "			} else {\n");
	fprintf (script, " 				cout << \" vec_cb.size(): \" << vec_cb.size() << \"no_mpn > 1\" << endl;\n");
	fprintf (script, "				for (int i = 0; i < vec_cb.size(); ++i) {\n");
	fprintf (script, "					if (vec_cb[i]->checkState() == Wt::Checked) {\n");
	fprintf (script, "						int code = map_cb_code_index[i];\n");
	fprintf (script, "						data.push_back(code);\n");
	fprintf (script, "						cout << \"vec_cb[\" << i << \"] is checked,   code: \" << code << endl;\n");
	fprintf (script, "						isAnswered = true;\n");
	fprintf (script, "					}\n");
	fprintf (script, "				}\n");
	fprintf (script, "			}\n");
	fprintf (script, "			if (isAnswered) {\n");
	fprintf (script, "				bool invalid_code = last_question_served->VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data,\n");
	fprintf (script, "					&data);\n");
	fprintf (script, "				if (invalid_code == false)\n");
	fprintf (script, "				{\n");
	fprintf (script, "					//last_question_served->input_data.erase\n");
	fprintf (script, "					//	(last_question_served->input_data.begin(),\n");
	fprintf (script, "					//	last_question_served->input_data.end());\n");
	fprintf (script, "				last_question_served->input_data.clear();\n");
	fprintf (script, "					for(uint32_t i = 0; i < data.size(); ++i)\n");
	fprintf (script, "					{\n");
	fprintf (script, "						last_question_served->input_data.insert(data[i]);\n");
	fprintf (script, "						cout << \"storing: \" << data[i]\n");
	fprintf (script, "							<< \" into input_data\" << endl;\n");
	fprintf (script, "					}\n");
	fprintf (script, "					last_question_served->isAnswered_ = true;\n");
	fprintf (script, "					data.clear();\n");
	fprintf (script, "				}\n");
	fprintf (script, "			}\n");
	fprintf (script, "			// do something with isAnswered_ == false here and resend the\n");
	fprintf (script, "			// qnre to the respondent\n");
	fprintf (script, "		} else {\n");
	fprintf (script, "\n");
	fprintf (script, "			string last_question_visited_str = wt_lastQuestionVisited_->text().narrow();\n");
	fprintf (script, "			string current_question_response = le_data_->text().narrow();\n");
	fprintf (script, "			AbstractQuestion * last_question_served = this_users_session->last_question_served;\n");
	fprintf (script, "			if (last_question_visited_str != \"\" && current_question_response != \"\" && last_question_served->no_mpn==1)\n");
	fprintf (script, "			{\n");
	fprintf (script, "				UserNavigation user_nav=NOT_SET;\n");
	fprintf (script, "				user_response::UserResponseType user_resp=user_response::NotSet;\n");
	fprintf (script, "				vector<int32_t> data;\n");
	fprintf (script, "				bool parse_success = verify_web_data (current_question_response, user_nav, user_resp, &data);\n");
	fprintf (script, "				if (parse_success)\n");
	fprintf (script, "				{\n");
	fprintf (script, "					cout << \"successfully parsed data = \";\n");
	fprintf (script, "					for (int i=0; i<data.size(); ++i)\n");
	fprintf (script, "					{\n");
	fprintf (script, "						cout << data[i] << \", \";\n");
	fprintf (script, "					}\n");
	fprintf (script, "					cout << endl;\n");
	fprintf (script, "				}\n");
	fprintf (script, "				// the call below will be required at some later stage\n");
	fprintf (script, "				//bool valid_input = AbstractQuestion::VerifyResponse(user_resp);\n");
	fprintf (script, "				// right now we go along with the happy path\n");
	fprintf (script, "				bool invalid_code = last_question_served->VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data,\n");
	fprintf (script, "					&data);\n");
	fprintf (script, "				if (invalid_code == false)\n");
	fprintf (script, "				{\n");
	fprintf (script, "					last_question_served->input_data.erase\n");
	fprintf (script, "						(last_question_served->input_data.begin(),\n");
	fprintf (script, "						last_question_served->input_data.end());\n");
	fprintf (script, "					for(uint32_t i = 0; i < data.size(); ++i)\n");
	fprintf (script, "					{\n");
	fprintf (script, "						last_question_served->input_data.insert(data[i]);\n");
	fprintf (script, "						//cout << \"storing: \" << data[i]\n");
	fprintf (script, "						//	<< \" into input_data\" << endl;\n");
	fprintf (script, "					}\n");
	fprintf (script, "					last_question_served->isAnswered_ = true;\n");
	fprintf (script, "					data.clear();\n");
	fprintf (script, "				}\n");
	fprintf (script, "				else {\n");
	fprintf (script, "					ConstructQuestionForm(last_question_served, this_users_session);\n");
	fprintf (script, "					return;\n");
	fprintf (script, "				}\n");
	fprintf (script, "			}\n");
	fprintf (script, "			else if (last_question_visited_str != \"\" && current_question_response != \"\" && last_question_served->no_mpn > 1)\n");
	fprintf (script, "			{\n");
	fprintf (script, "				string utf8_response = le_data_->text().toUTF8();\n");
	fprintf (script, "				if (utf8_response != \"\") \n");
	fprintf (script, "				{\n");
	fprintf (script, "					stringstream file_name_str;\n");
	fprintf (script, "					file_name_str << last_question_served->questionName_ << \".\" \n");
	fprintf (script, "						<< jno << \"_\" << ser_no << \".dat\";\n");
	fprintf (script, "					\n");
	fprintf (script, "					fstream open_end_resp(file_name_str.str().c_str(), ios_base::out|ios_base::ate);\n");
	fprintf (script, "					open_end_resp << utf8_response << endl;\n");
	fprintf (script, "					last_question_served->input_data.insert(96);\n");
	fprintf (script, "					last_question_served->isAnswered_ = true;\n");
	fprintf (script, "				}\n");
	fprintf (script, "				else\n");
	fprintf (script, "				{\n");
	fprintf (script, "					ConstructQuestionForm(last_question_served, this_users_session);\n");
	fprintf (script, "					return;\n");
	fprintf (script, "				}\n");
	fprintf (script, "			}\n");
	fprintf (script, "		}\n");
	fprintf (script, "	}\n");
	fprintf (script, "	{\n");
	fprintf(script, " 		TheQuestionnaire * qnre = this_users_session->questionnaire;\n");
	fprintf(script, "		qnre->write_data_to_disk(qnre->question_list, qnre->jno, qnre->ser_no);\n");
	fprintf (script, "	}\n");

	fprintf(script, "	AbstractQuestion * q =\n");
	fprintf(script, "		this_users_session->questionnaire->eval2(\n");
	fprintf(script, "		qnre_navigation_mode, this_users_session->last_question_served, 0 /*jump to index dummy*/);\n");
	fprintf(script, "	this_users_session->last_question_served = q;\n");
	fprintf(script, "if (q) {\n");
	fprintf(script, "	ConstructQuestionForm(q, this_users_session);\n");
	fprintf(script, "} else {\n");
	fprintf(script, " 	TheQuestionnaire * qnre = this_users_session->questionnaire;\n");
	fprintf(script, "	qnre->write_data_to_disk(qnre->question_list, qnre->jno, qnre->ser_no);\n");
	fprintf(script, " 	ConstructThankYouPage();\n");
	fprintf(script, "}\n");

	fprintf(script, "}\n");
	fprintf(script, "\n");

	fprintf(script, "void QuestionnaireApplication::ConstructThankYouPage()\n");
	fprintf(script, "{\n");
	fprintf(script, "	WContainerWidget * new_form = new WContainerWidget();\n");
	fprintf(script, "	WText * txt = new WText(WString::tr(\"thank_you\"), new_form);\n");
	fprintf(script, " 	WText * survey_code = new WText(WString::tr(\"vege_source_code\"), new_form);\n");
	fprintf(script, "	setCentralWidget(new_form);\n");
	fprintf(script, "	cout << \"ConstructThankYouPage\\n\";\n");
	fprintf(script, "}\n");



	fprintf(script, "\n");
	fprintf(script, "void QuestionnaireApplication::ConstructQuestionForm(\n");
	fprintf(script, "	AbstractQuestion *q, Session * this_users_session)\n");
	fprintf(script, "{\n");
	fprintf(script, "\n");
	fprintf(script, "	WContainerWidget * new_form = new WContainerWidget();\n");
	fprintf(script, "	vec_rb.clear();			 // memory leak introduced here? no it seems\n");
	fprintf(script, "	vec_cb.clear();			 // memory leak introduced here? no it seems\n");
	fprintf(script, "	map_cb_code_index.clear();\n");
	fprintf(script, "\n");
	fprintf(script, "	wt_questionText_ = new WText();\n");
	fprintf(script, "	//wt_questionText_->setText(q->textExprVec_[0]->text_);\n");
	fprintf(script, "	//stringstream question_text;\n");
	fprintf(script, "	stringstream part_mesg_id;\n");
	fprintf(script, "	WString question_text;\n");
	fprintf(script, "	part_mesg_id << q->questionName_;\n");
	fprintf(script, "	for (int i=0; i<q->loop_index_values.size(); ++i)\n");
	fprintf(script, "	{\n");
	fprintf(script, "		part_mesg_id << \"_\" << q->loop_index_values[i];\n");
	fprintf(script, "	}\n");
	fprintf(script, "	WText * wt_questionNo_ = new WText(part_mesg_id.str().c_str(), new_form);\n");
	fprintf(script, "	for (int i=0; i<q->textExprVec_.size(); ++i)\n");
	fprintf(script, "	{\n");
	fprintf(script, "		question_text += \"<p>\";\n");
	fprintf(script, "		if (q->textExprVec_[i]->teType_ == TextExpression::simple_text_type)\n");
	fprintf(script, "		{\n");
	fprintf(script, "			stringstream mesg_id;\n");
	fprintf(script, "			mesg_id << part_mesg_id.str() << \"_\" << i;\n");
	fprintf(script, "			question_text += WString::tr(mesg_id.str().c_str());\n");
	fprintf(script, "		}\n");
	fprintf(script, "		else if (q->textExprVec_[i]->teType_ == TextExpression::named_attribute_type)\n");
	fprintf(script, "		{\n");
	fprintf(script, "			stringstream named_attribute_key;\n");
	fprintf(script, "			named_attribute_key << q->textExprVec_[i]->naPtr_->name;\n");
	fprintf(script, "			named_attribute_key << \"_\" << q->textExprVec_[i]->naIndex_;\n");
	fprintf(script, "			question_text += WString::tr(named_attribute_key.str().c_str());\n");
	fprintf(script, "		}\n");
	fprintf(script, "		else if (q->textExprVec_[i]->teType_ == TextExpression::question_type)\n");
	fprintf(script, "		{\n");
	fprintf(script, "			if (q->textExprVec_[i]->codeIndex_ != -1) {\n");
	fprintf(script, "				question_text += q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(q->textExprVec_[i]->codeIndex_);\n");
	fprintf(script, "			} else {\n");
	fprintf(script, "				question_text += q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers();\n");
	fprintf(script, "			}\n");
	fprintf(script, "		}\n");
	fprintf(script, "		question_text += \"</p>\";\n");
	fprintf(script, "	}\n");
	fprintf(script, "	wt_questionText_->setText(question_text);\n");
	fprintf(script, "\n");
	fprintf(script, "	new_form->addWidget(wt_questionText_);\n");
	fprintf(script, "	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q))\n");
	fprintf(script, "	{\n");
	fprintf(script, "		new_form->addWidget(wt_cb_rb_container_ = new WGroupBox());\n");
	fprintf(script, "		if (q->no_mpn==1)\n");
	fprintf(script, "		{\n");
	fprintf(script, "			wt_rb_container_ = new WButtonGroup(wt_cb_rb_container_);\n");
	fprintf(script, "		}\n");
	fprintf(script, "		vector<stub_pair> & vec= (nq->nr_ptr->stubs);\n");
	fprintf(script, "		for (int i=0; i<vec.size(); ++i)\n");
	fprintf(script, "		{\n");
	fprintf(script, "			stringstream named_range_key;\n");
	fprintf(script, "			named_range_key << nq->nr_ptr->name << \"_\" << i;\n");
	fprintf(script, "			if (q->no_mpn==1 && vec[i].mask)\n");
	fprintf(script, "			{\n");
	fprintf(script, "				//WRadioButton * wt_rb = new WRadioButton( vec[i].stub_text, wt_cb_rb_container_);\n");
	fprintf(script, "				WRadioButton * wt_rb = new WRadioButton(WString::tr(named_range_key.str().c_str()), wt_cb_rb_container_);\n");
	fprintf(script, "				wt_rb_container_->addButton(wt_rb, vec[i].code);\n");
	fprintf(script, "				new WBreak(wt_cb_rb_container_);\n");
	fprintf(script, "				vec_rb.push_back(wt_rb);\n");
	fprintf(script, "			}\n");
	fprintf(script, "			else if (q->no_mpn>1 && vec[i].mask)\n");
	fprintf(script, "			{\n");
	fprintf(script, "				//WCheckBox * wt_cb = new WCheckBox ( vec[i].stub_text, wt_cb_rb_container_);\n");
	fprintf(script, "				WCheckBox * wt_cb = new WCheckBox (WString::tr(named_range_key.str().c_str()), wt_cb_rb_container_);\n");
	fprintf(script, "				vec_cb.push_back(wt_cb);\n");
	fprintf(script, "				cout << \" adding code: \" << vec[i].code << \" to map_cb_code_index\" ;\n");
	fprintf(script, "				map_cb_code_index[vec_cb.size()-1] = vec[i].code;\n");
	fprintf(script, "			}\n");
	fprintf(script, "		}\n");
	fprintf(script, "		new_form->addWidget(wt_cb_rb_container_);\n");
	fprintf(script, "	}\n");
	fprintf(script, "	else\n");
	fprintf(script, "	{\n");
	fprintf(script, "		le_data_ = new WLineEdit();\n");
	fprintf(script, "		new_form->addWidget(le_data_);\n");
	fprintf(script, "	}\n");
	fprintf(script, "\n");
	fprintf(script, "	wt_lastQuestionVisited_ = new WText();\n");
	fprintf(script, "	if (this_users_session->last_question_answered)\n");
	fprintf(script, "		wt_lastQuestionVisited_->setText(q->questionName_);\n");
	fprintf(script, "	new_form->addWidget(wt_lastQuestionVisited_);\n");
	fprintf(script, "\n");
	fprintf(script, "							 // create a button\n");
	fprintf(script, "	WPushButton *b = new WPushButton(\"Next\");\n");
	fprintf(script, "	b->clicked().connect(this, &QuestionnaireApplication::DoQuestionnaire);\n");
	fprintf(script, "	new_form->addWidget(b);\n");
	fprintf(script, "\n");
	fprintf(script, "	setCentralWidget(new_form);\n");
	fprintf(script, "}\n");
	fprintf(script, "\n");

	fprintf(script, "\n");
	fprintf(script, "void QuestionnaireApplication::setCentralWidget(WContainerWidget * new_question_form)\n");
	fprintf(script, "{\n");
	fprintf(script, "	if (!flagSerialPageRemoved_) {\n");
	fprintf(script, "		formContainer_->removeWidget(serialPage_);\n");
	fprintf(script, "		flagSerialPageRemoved_ = true;\n");
	fprintf(script, "	}\n");
	fprintf(script, "	if (currentForm_)\n");
	fprintf(script, "		delete currentForm_;\n");
	fprintf(script, "	currentForm_ = new_question_form;\n");
	fprintf(script, "	formContainer_->addWidget(currentForm_);\n");
	fprintf(script, "}\n");
	fprintf(script, "\n");


	fprintf (script, "void QuestionnaireApplication::changeLanguage()\n");
	fprintf (script, "{\n");
	fprintf (script, "	WText *t = (WText *)sender();\n");
	fprintf (script, "	setLanguage(narrow(t->text().value()));\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");
	fprintf (script, "void QuestionnaireApplication::setLanguage(const std::string lang)\n");
	fprintf (script, "{\n");
	fprintf (script, "	bool haveLang = false;\n");
	fprintf (script, "\n");
	fprintf (script, "	for (unsigned i = 0; i < languageSelects_.size(); ++i) {\n");
	fprintf (script, "		WText *t = languageSelects_[i];\n");
	fprintf (script, "\n");
	fprintf (script, "		// prefix match, e.g. en matches en-us.\n");
	fprintf (script, "		bool isLang = lang.find(narrow(t->text().value())) == 0;\n");
	fprintf (script, "		t->setStyleClass(isLang ? L\"langcurrent\" : L\"lang\");\n");
	fprintf (script, "\n");
	fprintf (script, "		haveLang = haveLang || isLang;\n");
	fprintf (script, "	}\n");
	fprintf (script, "\n");
	fprintf (script, "	if (!haveLang) {\n");
	fprintf (script, "		languageSelects_[0]->setStyleClass(L\"langcurrent\");\n");
	fprintf (script, "		WApplication::instance()\n");
	fprintf (script, "			->setLocale(narrow(languageSelects_[0]->text().value()));\n");
	fprintf (script, "	} else\n");
	fprintf (script, "		WApplication::instance()->setLocale(lang);\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");


	fprintf(script, "\n");
	fprintf(script, "\n");
	fprintf(script, "QuestionnaireApplication::QuestionnaireApplication(const WEnvironment &env)\n");
	fprintf(script, "	: WApplication(env), wt_questionText_(0), currentForm_(0), flagSerialPageRemoved_(false)\n");
	fprintf(script, "{\n");
	fprintf(script, "	messageResourceBundle().use(WApplication::appRoot() + jno);\n");

	fprintf(script, "	serialPage_ = new WContainerWidget(0);\n");
	fprintf(script, "	setTitle(\"QuestionnaireApplication\");\n");
	fprintf(script, "	/*\n");
	fprintf(script, "	WPushButton *b = new WPushButton(\"Click to start survey\", root()); // create a button\n");
	fprintf(script, "	b->setMargin(5, Left);                                 // add 5 pixels margin\n");
	fprintf(script, "\n");
	fprintf(script, "	root()->addWidget(new WBreak());                       // insert a line break\n");
	fprintf(script, "\n");
	fprintf(script, "	wt_questionText_ = new WText(root());                         // empty text\n");
	fprintf(script, "\n");
	fprintf(script, "	b->clicked().connect(this, &QuestionnaireApplication::DoQuestionnaire);\n");
	fprintf(script, "	*/\n");

	fprintf (script, "\n");
	fprintf (script, "	WCssDecorationStyle langStyle;\n");
	fprintf (script, "	langStyle.font().setSize(WFont::Smaller);\n");
	fprintf (script, "	langStyle.setCursor(PointingHandCursor);\n");
	fprintf (script, "	langStyle.setForegroundColor(blue);\n");
	fprintf (script, "	langStyle.setTextDecoration(WCssDecorationStyle::Underline);\n");
	fprintf (script, "	this->styleSheet().addRule(\".lang\", langStyle);\n");
	fprintf (script, "\n");
	fprintf (script, "	langStyle.setCursor(ArrowCursor);\n");
	fprintf (script, "	langStyle.font().setWeight(WFont::Bold);\n");
	fprintf (script, "	this->styleSheet().addRule(\".langcurrent\", langStyle);\n");

	fprintf (script, "\n");
	//langStyle.setForegroundColor(green);
	fprintf (script, "	langStyle.setForegroundColor(WColor(100, 0, 200, 100));\n");
	fprintf (script, "	langStyle.setCursor(IBeamCursor);\n");
	fprintf (script, "	langStyle.font().setWeight(WFont::Bold);\n");
	fprintf (script, "	langStyle.font().setSize(WFont::XLarge);\n");
	fprintf (script, "	this->styleSheet().addRule(\".langtitle\", langStyle);\n");

	fprintf (script, "\n");
	fprintf (script, "	// warning the statement below modifies the global variable\n");
	fprintf (script, "	//load_languages_available(vec_language);\n");
	fprintf (script, "	WContainerWidget *langLayout = new WContainerWidget();\n");
	fprintf (script, "	langLayout->setContentAlignment(AlignRight);\n");
	fprintf (script, "\n");
	fprintf (script, "	WText * lang_title = new WText(WString::tr(\"language\"), langLayout);\n");
	fprintf (script, "	lang_title->setStyleClass(L\"langtitle\");\n");
	fprintf (script, "\n");
	fprintf (script, "\n");
	fprintf (script, "	for (int i = 0; i < vec_language.size(); ++i) {\n");
	fprintf (script, "		WText *t = new WText(widen(vec_language[i]), langLayout);\n");
	//fprintf (script, "		WText *t = new WText(WString::tr(vec_language[i]), langLayout);\n");
	fprintf (script, "		t->setMargin(5);\n");
	fprintf (script, "		t->clicked().connect(this, &QuestionnaireApplication::changeLanguage);\n");
	fprintf (script, "		languageSelects_.push_back(t);\n");
	fprintf (script, "	}\n");
	fprintf (script, "\n");
	fprintf (script, "	/*\n");
	fprintf (script, "	* Start with the reported locale, if available\n");
	fprintf (script, "	*/\n");
	fprintf (script, "	//setLanguage(wApp->locale());\n");
	fprintf (script, "	setLanguage(\"hn\");\n");
	fprintf (script, "\n");

	//fprintf(script, "	WText * txt_software_info = new WText(software_info(), serialPage_);\n");
	fprintf(script, "	WText * txt_software_info = new WText(WString::tr(\"qscript_info\"), serialPage_);\n");

	fprintf(script, "	WPushButton *b = new WPushButton(\"Click to start survey\", serialPage_); // create a button\n");
	fprintf(script, "	b->setMargin(5, Left);                                 // add 5 pixels margin\n");
	fprintf(script, "	serialPage_->addWidget(new WBreak());                       // insert a line break\n");
	fprintf(script, "	//b->clicked().connect(this, &QuestionnaireApplication::DoQuestionnaire);\n");
	fprintf(script, "	b->clicked().connect(this, &QuestionnaireApplication::ValidateSerialNo);\n");
	fprintf(script, "	wt_questionText_ = new WText(serialPage_);\n");
	fprintf(script, "	wt_questionText_->setText(\"Serial No: \");\n");
	fprintf(script, "	wt_lastQuestionVisited_ = new WText(serialPage_);\n");
	fprintf(script, "	le_data_ = new WLineEdit(serialPage_);\n");
	fprintf(script, "\n");
	fprintf(script, "	wt_debug_ = new WText(serialPage_);\n");
	fprintf(script, "	formContainer_ = new WContainerWidget(root());\n");
	fprintf(script, "	formContainer_->addWidget(serialPage_);\n");
	fprintf(script, "	formContainer_->addWidget(langLayout);\n");
	fprintf(script, "	string sess_id = sessionId();\n");
	fprintf(script, "	this_users_session = new Session();\n");
	fprintf(script, "	strcpy(this_users_session->sid, sess_id.c_str());\n");
	fprintf(script, "	wt_sessions.push_back(this_users_session);\n");
	fprintf(script, "}\n");
	fprintf(script, "\n");
	fprintf(script, "Wt::WServer server;\n");
	fprintf(script, "WApplication * createApplication(const WEnvironment &env)\n");
	fprintf(script, "{\n");
	fprintf(script, "	//return new QuestionnaireApplication (env);\n");
	fprintf(script, "	WApplication * ptr =  new QuestionnaireApplication (env);\n");
	fprintf(script, "	//cout << \"Sizeof (WApplication): \" << sizeof (*ptr) << endl;\n");
	fprintf(script, "	return ptr;\n");
	fprintf(script, "}\n");
	fprintf(script, "\n");
	fprintf(script, "int main(int argc, char ** argv)\n");
	fprintf(script, "{\n");
	fprintf(script, "	//process_options(argc, argv);\n");
	fprintf(script, "       for (int i=0; i<argc; ++i) { if (string(argv[i]) == \"-m\") { write_messages_flag = 1; break;} }\n");
	fprintf(script, "	if (write_messages_flag) {\n");
	fprintf(script, "	\tTheQuestionnaire theQuestionnaire(\"dummy\");\n");
	fprintf(script, "	\texit(0);\n");
	fprintf(script, "	}\n");
	fprintf(script, "	if (write_data_file_flag||write_qtm_data_file_flag)\n");
	fprintf(script, "	{\n");
	fprintf(script, "		qtm_data_file_ns::init_exceptions();\n");
	fprintf(script, "		directory_ptr = opendir(\".\");\n");
	fprintf(script, "		if (! directory_ptr)\n");
	fprintf(script, "		{\n");
	fprintf(script, "			cout << \" unable to open . (current directory) for reading\\n\";\n");
	fprintf(script, "			exit(1);\n");
	fprintf(script, "		}\n");
	fprintf(script, "	}\n");
	fprintf (script, "	load_languages_available(vec_language);\n");
	fprintf(script, "	bool using_ncurses = true;\n");
	fprintf(script, "	qscript_stdout = fopen(qscript_stdout_fname.c_str(), \"w\");\n");
	fprintf(script, "	SetupSignalHandler();\n");
	fprintf(script, "\n");
	fprintf(script, "	//return WRun (argc, argv, &createApplication);\n");

	fprintf (script, "{\n");
	fprintf (script, "  try {\n");
	fprintf (script, "    // use argv[0] as the application name to match a suitable entry\n");
	fprintf (script, "    // in the Wt configuration file, and use the default configuration\n");
	fprintf (script, "    // file (which defaults to /etc/wt/wt_config.xml unless the environment\n");
	fprintf (script, "    // variable WT_CONFIG_XML is set)\n");
	fprintf (script, "    // WServer server(argv[0]);\n");
	fprintf (script, "\n");
	fprintf (script, "    // WTHTTP_CONFIGURATION is e.g. \"/etc/wt/wthttpd\"\n");
	fprintf (script, "    server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);\n");
	fprintf (script, "\n");
	fprintf (script, "    // add a single entry point, at the default location (as determined\n");
	fprintf (script, "    // by the server configuration's deploy-path)\n");
	fprintf (script, "    server.addEntryPoint(Wt::Application, createApplication);\n");
	fprintf (script, "    if (server.start()) {\n");
	fprintf (script, "\tstd::string port_number_fname = jno + string(\"_port_number\");\n");
	fprintf (script, "\tstd::fstream port_number(port_number_fname.c_str(), ios_base::out);\n");
	fprintf (script, "\t port_number << server.httpPort();\n");
	// process id
	fprintf (script, "port_number << ' ' << getpid() << std::endl; ");

	fprintf (script, "\t std::cout << server.httpPort() << std::endl;\n");
	fprintf (script, "\t port_number.flush();\n");
	fprintf (script, "      int sig = WServer::waitForShutdown(argv[0]);\n");
	fprintf (script, "\n");
	fprintf (script, "      std::cerr << \"Shutdown (signal = \" << sig << \")\" << std::endl;\n");
	fprintf (script, "      server.stop();\n");
	fprintf (script, "\n");
	fprintf (script, "      if (sig == SIGHUP)\n");
	fprintf (script, "        WServer::restart(argc, argv, environ);\n");
	fprintf (script, "    }\n");
	fprintf (script, "  } catch (WServer::Exception& e) {\n");
	fprintf (script, "    std::cerr << e.what() << std::endl;\n");
	fprintf (script, "    return 1;\n");
	fprintf (script, "  } catch (std::exception& e) {\n");
	fprintf (script, "    std::cerr << \"exception: \" << e.what() << std::endl;\n");
	fprintf (script, "    return 1;\n");
	fprintf (script, "  }\n");
	fprintf (script, "}\n");


	fprintf(script, "}\n");
	fprintf(script, "\n");

	fprintf(script, "const char * QuestionnaireApplication::software_info()\n{\n");
	fprintf(script, "	const char * info = ");
	fprintf(script, "\"Welcome to the qscript demo survey page. This survey is not a demo of qscript web capabilities, but rather a demo of the pen and paper module. For web capable qscript we need to implement the following features <ul><li>Piping of answers</li><li>Unicode capture of other responses</li><li>Randomization of stub lists - groups, subgroups, holding an attribute, holding a group, etc</li><li>Randomization of attributes</li><li>question numbers are displayed at the top like this \\\"q1\\\". Looped question numbers will be displayed like this \\\"q1_0\\\". Note that the 1st iteration starts at 0.</li><li>The qscript project page is <a href=\\\"http://qscript.in\\\">http://qscript.in</a></li><li>The Download page is <a href=\\\"http://sourceforge.net/projects/xtcc\\\">http://sourceforge.net/projects/xtcc</a></li><li>Enter a serial number below. It can be upto 7 digits long. You can finish the survey later, by entering the same serial number. It will start exactly where you left off. We have no control over what serial numbers people enter. To make up a number somewhat unique - try using your mobile number, mixed with your date of birth, mixed with your spouse's date of birth.</li></ul>\";\n");
	fprintf(script, " 	return info;\n}\n");

	fprintf (script, "\n");
	fprintf (script, "// warning modifies the input variable\n");
	fprintf (script, "void load_languages_available(vector<string> & vec_language)\n");
	fprintf (script, "{\n");
	fprintf (script, "	DIR * directory_ptr = opendir(\".\");\n");
	fprintf (script, "	vec_language.push_back(\"en\");\n");
	fprintf (script, "	struct dirent *directory_entry = readdir(directory_ptr);\n");
	fprintf (script, "	while (directory_entry) {\n");
	fprintf (script, "		string dir_entry_name(directory_entry->d_name);\n");
	fprintf (script, "		int len_entry = dir_entry_name.length();\n");
	fprintf (script, "		if (len_entry > 4 &&\n");
	fprintf (script, "				dir_entry_name[len_entry - 1] == 'l' &&\n");
	fprintf (script, "				dir_entry_name[len_entry - 2] == 'm' &&\n");
	fprintf (script, "				dir_entry_name[len_entry - 3] == 'x' &&\n");
	fprintf (script, "				dir_entry_name[len_entry - 4] == '.' ) {\n");
	fprintf (script, "			// the names we are looking for are of the form\n");
	fprintf (script, "			// jno + \"[a-z][a-z].xml\"\n");
	fprintf (script, "			bool is_our_file = true;\n");
	fprintf (script, "			if (len_entry != jno.length() + 7) {\n");
	fprintf (script, "				is_our_file = false;\n");
	fprintf (script, "				// the above doesnt matter actually, \n");
	fprintf (script, "				// continue takes us back to the top\n");
	fprintf (script, "				goto read_another_entry;\n");
	fprintf (script, "			} else {\n");
	fprintf (script, "				// possibly what we are looking for\n");
	fprintf (script, "				//\n");
	fprintf (script, "				for (int i = 0; i < jno.length(); ++i) {\n");
	fprintf (script, "					if (!(jno[i] == dir_entry_name[i])) {\n");
	fprintf (script, "						// cannot be our data file\n");
	fprintf (script, "						is_our_file = false;\n");
	fprintf (script, "						goto read_another_entry;\n");
	fprintf (script, "					}\n");
	fprintf (script, "				}\n");
	fprintf (script, "				char first_letter = dir_entry_name[jno.length() + 1];\n");
	fprintf (script, "				if (! isalpha (first_letter)) {\n");
	fprintf (script, "					is_our_file = false;\n");
	fprintf (script, "					goto read_another_entry;\n");
	fprintf (script, "				}\n");
	fprintf (script, "				char second_letter = dir_entry_name[jno.length() + 2];\n");
	fprintf (script, "				if (! isalpha (second_letter)) {\n");
	fprintf (script, "					is_our_file = false;\n");
	fprintf (script, "					goto read_another_entry;\n");
	fprintf (script, "				}\n");
	fprintf (script, "				string a_language;\n");
	fprintf (script, "				a_language.push_back(first_letter);\n");
	fprintf (script, "				a_language.push_back(second_letter);\n");
	fprintf (script, "				vec_language.push_back(a_language);\n");
	fprintf (script, "				//cout << \"found an language traslation file: \" \n");
	fprintf (script, "				//	<< dir_entry_name << endl;\n");
	fprintf (script, "			}\n");
	fprintf (script, "		}\n");
	fprintf (script, "read_another_entry:\n");
	fprintf (script, "		directory_entry = readdir(directory_ptr);\n");
	fprintf (script, "	}\n");
	fprintf (script, "	closedir(directory_ptr);\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");
#endif /* 0 */

}


named_range * named_stub_exists (string p_name)
{
	using qscript_parser::named_stubs_list;
	for (int i=0; i < named_stubs_list.size(); ++i) {
		if (named_stubs_list[i]->name == p_name) {
			return named_stubs_list[i];
		}
	}
	return 0;
}

int question_exists (string p_name)
{
	int index = -1;
	for (int32_t i = 0; i < question_list.size(); ++i) {
		if (question_list[i]->questionName_  ==  p_name) {
			index = i;
			break;
		}
	}
	return index;
}


#if 0
bool verify_stubs_list (struct named_range * nr_ptr)
{
	bool success = true;
	// We need to check 2 things
	// 1. Does the stub list end with [0-9]r
	// 	=> reversed scale
	// 2. Does the stub list end with [0-9]
	// 	=> normal scale
	// if either of these conditions is true
	//  then do our checks otherwise immediately
	//  return success
	string stub_list_name = nr_ptr->name;
	struct RatingScaleInfo rat_scale_inf = extract_rating_scale (stub_list_name);

	if (rat_scale_inf.isRatingScale_) {
		if (rat_scale_inf.isReversed_ == true) {
			cerr << "Scale is reversed - run checks" << endl;
			if (!check_reversed_rating_scale(rat_scale_inf, nr_ptr) ) {
				stringstream err_mesg;
				err_mesg << "stub list :" << nr_ptr->name
					<< "failed rating scale checks"
					<< endl;
				print_err (compiler_sem_err, err_mesg.str(), line_no, __LINE__, __FILE__);
			}
		} else if (rat_scale_inf.isReversed_ == false) {
			cerr << "Normal Scale - run checks" << endl;
			if (!check_standard_rating_scale(rat_scale_inf, nr_ptr) ) {
				stringstream err_mesg;
				err_mesg << "stub list :" << nr_ptr->name
					<< "failed rating scale checks"
					<< endl;
				print_err (compiler_sem_err, err_mesg.str(), line_no, __LINE__, __FILE__);
			}
		} else {
			stringstream err_mesg;
			err_mesg << " This should never happen. Unhandled case RatingScaleInfo";
			print_err (compiler_internal_error, err_mesg.str(), line_no, __LINE__, __FILE__);
		}
	} else {
		// nothing
	}
	return success;

}
#endif /*  0 */


void print_new_logic_support_functions(FILE * script)
{
	string support_fname =  program_options_ns::QSCRIPT_HOME +  string("/runtime/cpp/common/new_logic_support_frag_stdout.cpp");
	std::ifstream new_logic_support_frag(support_fname.c_str(),
			std::ios::in | std::ios::binary);

	if (new_logic_support_frag) {
		std::string new_logic_support_frag_contents;
		new_logic_support_frag.seekg(0, std::ios::end);
		new_logic_support_frag_contents.resize(new_logic_support_frag.tellg());
		new_logic_support_frag.seekg(0, std::ios::beg);
		new_logic_support_frag.read(&new_logic_support_frag_contents[0], new_logic_support_frag_contents.size());
		new_logic_support_frag.close();
		fprintf (script, "%s", new_logic_support_frag_contents.c_str());
	} else {
		cerr << "Unable to open file " << support_fname << endl
			<< "... exiting" << endl;
		exit(1);
	}

#if 0
	fprintf (script, "/* ============= new_logic_support_frag stdout =========*/\n");
	fprintf (script, "void question_eval_loop2 (\n");
	fprintf (script, "	UserInput p_user_input,\n");
	fprintf (script, "	AbstractRuntimeQuestion * last_question_visited,\n");
	fprintf (script, "	AbstractRuntimeQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire, int nest_level);\n");
	fprintf (script, "\n");
	fprintf (script, "int callback_get_ser_no_from_ui (int p_ser_no, int nest_level)\n");
	fprintf (script, "{\n");
	fprintf (script, "	// now its not :-) // nxd: this is a global variable - has to be eliminated at some point\n");
	fprintf (script, "	TheQuestionnaire * theQuestionnaire = new TheQuestionnaire (jno);\n");
	fprintf (script, "	cout << \"received serial no : \" << p_ser_no << \"from ui\";\n");
	fprintf (script, "\n");
	fprintf (script, "	theQuestionnaire->ser_no = p_ser_no;\n");
	fprintf (script, "	theQuestionnaire->base_text_vec.push_back(BaseText(\"All Respondents\"));\n");

	if (program_options_ns::data_export_flag) {
		fprintf (script, "	theQuestionnaire->compute_flat_file_map_and_init();\n");
	} else {
		fprintf (script, "	//theQuestionnaire->compute_flat_file_map_and_init();\n");
	}
	fprintf (script, "	UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;\n");
	fprintf (script, "\n");
	fprintf (script, "	AbstractRuntimeQuestion * last_question_visited = 0;\n");
	fprintf (script, "	AbstractRuntimeQuestion * jump_to_question = 0;\n");
	fprintf (script, "	EvalMode qnre_mode = NORMAL_FLOW;\n");
	fprintf (script, "	//question_eval_loop (qnre_mode,\n");
	fprintf (script, "	//			qnre_navigation_mode, last_question_visited,\n");
	fprintf (script, "	//			jump_to_question, theQuestionnaire);\n");
	fprintf (script, "	UserInput l_user_input;\n");
	fprintf (script, "	question_eval_loop2 (\n");
	fprintf (script, "				l_user_input, /* last_question_visited */ 0,\n");
	fprintf (script, "				/* jump_to_question */ 0, theQuestionnaire, nest_level+1);\n");
	fprintf (script, "	cout << \"finished qnre: exiting ...\" << endl;\n");
	fprintf (script, "	prompt_user_for_serial_no (callback_get_ser_no_from_ui, nest_level + 1);\n");
	fprintf (script, "	return 0;\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");
	fprintf (script, "\n");
	fprintf (script, "void parse_input_data(vector<int> * data_ptr, int & success);\n");
	fprintf (script, "void callback_ui_input (UserInput p_user_input, AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire, int nest_level);\n");
	fprintf (script, "void eval_single_question_logic_with_input (UserInput p_user_input, const vector<AbstractRuntimeQuestion *> & q_vec, struct TheQuestionnaire * theQuestionnaire, int nest_level);\n");
	fprintf (script, "\n");
	fprintf (script, "\n");
	fprintf (script, "void callback_ui_input (UserInput p_user_input, AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire, int nest_level)\n");
	fprintf (script, "{\n");
	fprintf (script, "	cout << __PRETTY_FUNCTION__ << endl;\n");
	fprintf (script, "	// this will be called by the UI - it is the UI's responsibility to\n");
	fprintf (script, "	// get valid data for us\n");
	fprintf (script, "	//bool valid_input = q->VerifyResponse (p_user_input.theUserResponse_, p_user_input.userNavigation_);\n");
	fprintf (script, "	if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {\n");
	fprintf (script, "		question_eval_loop2 (\n");
	fprintf (script, "				p_user_input,\n");
	fprintf (script, "				/* last_question_visited */ q,\n");
	fprintf (script, "				/*  jump_to_question */ 0, theQuestionnaire, nest_level+1);\n");
	fprintf (script, "	} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {\n");
	fprintf (script, "		eval_single_question_logic_with_input (p_user_input, q, theQuestionnaire, nest_level + 1);\n");
	fprintf (script, "	} else if (p_user_input.theUserResponse_ == user_response::UserSavedData) {\n");
	fprintf (script, "		cout << \"under stdout either the user can enter data or navigation\" << endl\n");
	fprintf (script, "			<< \"but under ncurses or other guis - it's possible to enter data\" << endl\n");
	fprintf (script, "			<< \" AND ask to save by pressing f4, in which case we should save the data \"\n");
	fprintf (script, "			<< \" and then try to validate the user input - just like we would in a normal case\"\n");
	fprintf (script, "			<< endl;\n");
	fprintf (script, "		// nxd: this function needs to be cleaned up\n");
	fprintf (script, "		//      we can easily downcast to an AbstractQuestionnaire and then there is no need for this\n");
	fprintf (script, "		//      function to be present here\n");
	fprintf (script, "		theQuestionnaire->write_data_to_disk (theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);\n");
	fprintf (script, "	} else {\n");
	fprintf (script, "		cerr << __PRETTY_FUNCTION__ << \" unhandled case theUserResponse_\" << endl;\n");
	fprintf (script, "	}\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");
	fprintf (script, "void question_eval_loop2 (\n");
	fprintf (script, "	UserInput p_user_input,\n");
	fprintf (script, "	AbstractRuntimeQuestion * last_question_visited,\n");
	fprintf (script, "	AbstractRuntimeQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire, int nest_level)\n");
	fprintf (script, "{\n");

	fprintf (script, "	cout << endl << \"Enter: \" << __PRETTY_FUNCTION__ << endl;\n");
	fprintf (script, "	cout << \"arg values: \" << endl;\n");
	fprintf (script, "	if (p_user_input.userNavigation_ == NAVIGATE_NEXT) {\n");
	fprintf (script, "		cout << \"p_user_input.userNavigation_ == NAVIGATE_NEXT\" << endl;\n");
	fprintf (script, "	} else if (p_user_input.userNavigation_ == NAVIGATE_PREVIOUS) {\n");
	fprintf (script, "		cout << \"p_user_input.userNavigation_ == NAVIGATE_PREVIOUS\" << endl;\n");
	fprintf (script, "	} else {\n");
	fprintf (script, "		cout << \"FIXME: p_user_input.userNavigation_ == Unhandled value \" << endl;\n");
	fprintf (script, "	}\n");
	fprintf (script, "	if 	  (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {\n");
	fprintf (script, "		cout << \"p_user_input.theUserResponse_ == UserEnteredNavigation\" << endl;\n");
	fprintf (script, "	} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {\n");
	fprintf (script, "		cout << \"p_user_input.theUserResponse_ == UserEnteredData\" << endl;\n");
	fprintf (script, "	} else if (p_user_input.theUserResponse_ == user_response::UserClearedData) {\n");
	fprintf (script, "		cout << \"p_user_input.theUserResponse_ == UserClearedData\" << endl;\n");
	fprintf (script, "	} else if (p_user_input.theUserResponse_ == user_response::UserSavedData) {\n");
	fprintf (script, "		cout << \"p_user_input.theUserResponse_ == UserSavedData\" << endl;\n");
	fprintf (script, "	} else if (p_user_input.theUserResponse_ == user_response::NotSet) {\n");
	fprintf (script, "		cout << \"p_user_input.theUserResponse_ == NotSet\" << endl;\n");
	fprintf (script, "	} else {\n");
	fprintf (script, "		cout << \"FIXME: p_user_input.theUserResponse_ == Unhandled value \" << endl;\n");
	fprintf (script, "	}\n");
	fprintf (script, "\n");

	fprintf (script, "\n");
	fprintf (script, "	cout \n");
	fprintf (script, "		<< \"p_user_input.questionResponseData_:\" \n");
	fprintf (script, "		<< p_user_input.questionResponseData_ << endl;\n");
	fprintf (script, "\n");
	fprintf (script, "	if (last_question_visited) {\n");
	fprintf (script, "		cout << \"last_question_visited->questionName_:\" \n");
	fprintf (script, "			<<  last_question_visited->questionName_\n");
	fprintf (script, "			<< endl;\n");
	fprintf (script, "	} else {\n");
	fprintf (script, "		cout << \"last_question_visited->questionName_: is NULL\"  << endl;\n");
	fprintf (script, "	}\n");
	fprintf (script, "\n");

	fprintf (script, "	if (last_question_visited) {\n");
	fprintf (script, "		if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {\n");
	fprintf (script, "			if (p_user_input.userNavigation_ == NAVIGATE_PREVIOUS) {\n");
	fprintf (script, "				fprintf(qscript_stdout,\n");
	fprintf (script, "					\"user_navigation == NAVIGATE_PREVIOUS\\n\");\n");
	fprintf (script, "				cout << \"Previous Button in MULITPLE QUESTIONS PER PAGE UNHANDLED\"\n");
	fprintf (script, "					<< endl;\n");
	fprintf (script, "#if 0\n");
	fprintf (script, "				AbstractRuntimeQuestion *target_question =\n");
	fprintf (script, "					theQuestionnaire->ComputePreviousQuestion(last_question_visited);\n");
	fprintf (script, "				if (target_question == 0) { \n");
	fprintf (script, "					stdout_eval (last_question_visited, theQuestionnaire, callback_ui_input, nest_level+1);\n");
	fprintf (script, "				} else {\n");
	fprintf (script, "					stdout_eval (target_question, theQuestionnaire, callback_ui_input, nest_level+1);\n");
	fprintf (script, "				}\n");
	fprintf (script, "#endif /*0*/\n");
	fprintf (script, "			} else if (p_user_input.userNavigation_ == NAVIGATE_NEXT) {\n");
	fprintf (script, "				// do nothing \n");
	fprintf (script, "				// once we exit this major block == last_question_visited\n");
	fprintf (script, "				// the bottom of this function will handle it\n");
	fprintf (script, "			} else {\n");
	fprintf (script, "				cout << \"Unhandled case userNavigation_ ... exiting\" << endl\n");
	fprintf (script, "					<< __FILE__ << \",\" \n");
	fprintf (script, "					<< __LINE__ << \",\" \n");
	fprintf (script, "					<< __PRETTY_FUNCTION__ << \",\" \n");
	fprintf (script, "					<< endl;\n");
	fprintf (script, "				exit(1);\n");
	fprintf (script, "			}\n");
	fprintf (script, "		} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {\n");
	fprintf (script, "			// the management of correctly accepting data is handled \n");
	fprintf (script, "			// by : callback_ui_input\n");
	fprintf (script, "			// if we have reached back again here - it means it's\n");
	fprintf (script, "			// time to get the next question\n");
#if 0
	fprintf (script, "			AbstractQuestion * q =\n");
	fprintf (script, "				theQuestionnaire->eval2 (\n");
	fprintf (script, "				NAVIGATE_NEXT, last_question_visited, jump_to_question);\n");

	fprintf (script, "			if (!q) {\n");
	fprintf (script, "				cout << \"End of qnre();\" << endl << \">\";\n");
	fprintf (script, "				//int ch = getchar();\n");
	fprintf (script, "			} else {\n");

	fprintf (script, "			cout << __PRETTY_FUNCTION__ << \",\" << __LINE__ <<  \", eval2 return q = \"\n");
	fprintf (script, "				<< q->questionName_ << endl;\n");


	fprintf (script, "				stdout_eval (q, theQuestionnaire, callback_ui_input);\n");
	fprintf (script, "			}\n");
#endif /* 0 */
	fprintf (script, "\n");
	fprintf (script, "		} else {\n");
	fprintf (script, "			cout << \"Unhandled case userNavigation_ ... exiting\" << endl;\n");
	fprintf (script, "			exit(1);\n");
	fprintf (script, "		}\n");
	fprintf (script, "	} // else {\n");
	fprintf (script, "	// should reach here - end of :\n");
	fprintf (script, "		vector<AbstractRuntimeQuestion *> q_vec =\n");
	fprintf (script, "			theQuestionnaire->eval2 (\n");
	fprintf (script, "			NAVIGATE_NEXT, last_question_visited, jump_to_question);\n");
	fprintf (script, "		if (q_vec.size() == 0) {\n");
	fprintf (script, "			cout << \"End of qnre();\" << endl << \">\";\n");
	fprintf (script, "		} else {\n");
	fprintf (script, "			cout << __PRETTY_FUNCTION__ << \",\" << __LINE__ <<  \", eval2 return first q in vec = \"\n");
	fprintf (script, "				<< q_vec[0]->questionName_ << endl;\n");
	fprintf (script, "			stdout_eval (q_vec, theQuestionnaire, callback_ui_input, nest_level+1);\n");
	fprintf (script, "		}\n");
	fprintf (script, "	//}\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");

	fprintf (script, "/* ============= END new_logic_support_frag stdout =========*/\n");

#endif /* 0 */
}

void print_emscripten_support_functions(FILE * script)
{
	string support_fname =  program_options_ns::QSCRIPT_HOME +  string("/runtime/cpp/common/emscripten_support_frag.cpp");
	std::ifstream new_logic_support_frag(support_fname.c_str(),
			std::ios::in | std::ios::binary);

	if (new_logic_support_frag) {
		std::string new_logic_support_frag_contents;
		new_logic_support_frag.seekg(0, std::ios::end);
		new_logic_support_frag_contents.resize(new_logic_support_frag.tellg());
		new_logic_support_frag.seekg(0, std::ios::beg);
		new_logic_support_frag.read(&new_logic_support_frag_contents[0], new_logic_support_frag_contents.size());
		new_logic_support_frag.close();
		fprintf (script, "%s", new_logic_support_frag_contents.c_str());
	} else {
		cerr << "Unable to open file " << support_fname << endl
			<< "... exiting" << endl;
		exit(1);
	}

}

void print_new_logic_support_functions_2(FILE * script)
{
	// http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
	string support_fname =  program_options_ns::QSCRIPT_HOME +  string("/runtime/cpp/common/new_logic_support_frag.cpp");
	std::ifstream new_logic_support_frag(support_fname.c_str(),
			std::ios::in | std::ios::binary);
	// somewhere in the c++ prog lang - stroustrup has an example
	// of this. unfortunately im in gurgaon and the book is in bombay
	//stringstream new_logic_support_frag_contents;
	//new_logic_support_frag.get (new_logic_support_frag_contents);

	if (new_logic_support_frag) {
		std::string new_logic_support_frag_contents;
		new_logic_support_frag.seekg(0, std::ios::end);
		new_logic_support_frag_contents.resize(new_logic_support_frag.tellg());
		new_logic_support_frag.seekg(0, std::ios::beg);
		new_logic_support_frag.read(&new_logic_support_frag_contents[0], new_logic_support_frag_contents.size());
		new_logic_support_frag.close();
		fprintf (script, "%s", new_logic_support_frag_contents.c_str());
	} else {
		cerr << "Unable to open file " << support_fname << endl
			<< "... exiting" << endl;
		exit(1);
	}

#if 0
	fprintf (script, "void question_eval_loop2 (\n");
	fprintf (script, "	UserInput p_user_input,\n");
	fprintf (script, "	AbstractRuntimeQuestion * last_question_visited,\n");
	fprintf (script, "	AbstractRuntimeQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire, int nest_level);\n");
	fprintf (script, "\n");
	fprintf (script, "// nxd: this is a global variable - has to be eliminated at some point\n");
	fprintf (script, "//TheQuestionnaire * theQuestionnaire = new TheQuestionnaire (jno);\n");
	fprintf (script, "int callback_get_ser_no_from_ui (int p_ser_no, struct TheQuestionnaire * theQuestionnaire, int nest_level )\n");
	fprintf (script, "{\n");
	fprintf (script, "	cout << \"received serial no : \" << p_ser_no << \"from ui\";\n");
	fprintf (script, "\n");
	fprintf (script, "	theQuestionnaire->ser_no = p_ser_no;\n");
	fprintf (script, "	theQuestionnaire->base_text_vec.push_back(BaseText(\"All Respondents\"));\n");

	if (program_options_ns::data_export_flag) {
		fprintf (script, "	theQuestionnaire->compute_flat_file_map_and_init();\n");
	} else {
		fprintf (script, "	//theQuestionnaire->compute_flat_file_map_and_init();\n");
	}
	fprintf (script, "	UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;\n");
	fprintf (script, "\n");
	fprintf (script, "	AbstractRuntimeQuestion * last_question_visited = 0;\n");
	fprintf (script, "	AbstractRuntimeQuestion * jump_to_question = 0;\n");
	fprintf (script, "	EvalMode qnre_mode = NORMAL_FLOW;\n");
	fprintf (script, "	//question_eval_loop (qnre_mode,\n");
	fprintf (script, "	//			qnre_navigation_mode, last_question_visited,\n");
	fprintf (script, "	//			jump_to_question, theQuestionnaire);\n");
	fprintf (script, "	UserInput l_user_input;\n");
	fprintf (script, "	question_eval_loop2 (\n");
	fprintf (script, "				l_user_input, /* last_question_visited */ 0,\n");
	fprintf (script, "				/* jump_to_question */ 0, theQuestionnaire, nest_level + 1);\n");
	fprintf (script, "	//cout << \"finished qnre: exiting ...\" << endl;\n");
	fprintf (script, "	//prompt_user_for_serial_no (callback_get_ser_no_from_ui);\n");
	fprintf (script, "	return 0;\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");
	fprintf (script, "\n");
	fprintf (script, "void parse_input_data(vector<int> * data_ptr, int & success);\n");
	fprintf (script, "void callback_ui_input (UserInput p_user_input, AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire, int nest_level);\n");
	fprintf (script, "void eval_single_question_logic_with_input (UserInput p_user_input, AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire, int nest_level);\n");
	fprintf (script, "\n");
	fprintf (script, "\n");
	fprintf (script, "void callback_ui_input (UserInput p_user_input, AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire, int nest_level)\n");
	fprintf (script, "{\n");
	fprintf (script, "	cout << __PRETTY_FUNCTION__ << endl;\n");
	fprintf (script, "	// this will be called by the UI - it is the UI's responsibility to\n");
	fprintf (script, "	// get valid data for us\n");
	fprintf (script, "	//bool valid_input = q->VerifyResponse (p_user_input.theUserResponse_, p_user_input.userNavigation_);\n");
	fprintf (script, "	if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {\n");
	fprintf (script, "		question_eval_loop2 (\n");
	fprintf (script, "				p_user_input,\n");
	fprintf (script, "				/* last_question_visited */ q,\n");
	fprintf (script, "				/*  jump_to_question */ 0, theQuestionnaire, nest_level + 1);\n");
	fprintf (script, "	} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {\n");
	fprintf (script, "		eval_single_question_logic_with_input (p_user_input, q, theQuestionnaire, nest_level + 1);\n");
	fprintf (script, "	} else if (p_user_input.theUserResponse_ == user_response::UserSavedData) {\n");
	fprintf (script, "		cout << \"under stdout either the user can enter data or navigation\" << endl\n");
	fprintf (script, "			<< \"but under ncurses or other guis - it's possible to enter data\" << endl\n");
	fprintf (script, "			<< \" AND ask to save by pressing f4, in which case we should save the data \"\n");
	fprintf (script, "			<< \" and then try to validate the user input - just like we would in a normal case\"\n");
	fprintf (script, "			<< endl;\n");
	fprintf (script, "		// nxd: this function needs to be cleaned up\n");
	fprintf (script, "		//      we can easily downcast to an AbstractQuestionnaire and then there is no need for this\n");
	fprintf (script, "		//      function to be present here\n");
	fprintf (script, "		theQuestionnaire->write_data_to_disk (theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);\n");
	fprintf (script, "	} else {\n");
	fprintf (script, "		cerr << __PRETTY_FUNCTION__ << \" unhandled case theUserResponse_\" << endl;\n");
	fprintf (script, "	}\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");
	fprintf (script, "void question_eval_loop2 (\n");
	fprintf (script, "	UserInput p_user_input,\n");
	fprintf (script, "	AbstractRuntimeQuestion * last_question_visited,\n");
	fprintf (script, "	AbstractRuntimeQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire, int nest_level)\n");
	fprintf (script, "{\n");

	fprintf (script, "	cout << endl << \"Enter: \" << __PRETTY_FUNCTION__ << endl;\n");
	fprintf (script, "	cout << \"arg values: \" << endl;\n");
	fprintf (script, "	if (p_user_input.userNavigation_ == NAVIGATE_NEXT) {\n");
	fprintf (script, "		cout << \"p_user_input.userNavigation_ == NAVIGATE_NEXT\" << endl;\n");
	fprintf (script, "	} else if (p_user_input.userNavigation_ == NAVIGATE_PREVIOUS) {\n");
	fprintf (script, "		cout << \"p_user_input.userNavigation_ == NAVIGATE_PREVIOUS\" << endl;\n");
	fprintf (script, "	} else {\n");
	fprintf (script, "		cout << \"FIXME: p_user_input.userNavigation_ == Unhandled value \" << endl;\n");
	fprintf (script, "	}\n");
	fprintf (script, "	if 	  (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {\n");
	fprintf (script, "		cout << \"p_user_input.theUserResponse_ == UserEnteredNavigation\" << endl;\n");
	fprintf (script, "	} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {\n");
	fprintf (script, "		cout << \"p_user_input.theUserResponse_ == UserEnteredData\" << endl;\n");
	fprintf (script, "	} else if (p_user_input.theUserResponse_ == user_response::UserClearedData) {\n");
	fprintf (script, "		cout << \"p_user_input.theUserResponse_ == UserClearedData\" << endl;\n");
	fprintf (script, "	} else if (p_user_input.theUserResponse_ == user_response::UserSavedData) {\n");
	fprintf (script, "		cout << \"p_user_input.theUserResponse_ == UserSavedData\" << endl;\n");
	fprintf (script, "	} else if (p_user_input.theUserResponse_ == user_response::NotSet) {\n");
	fprintf (script, "		cout << \"p_user_input.theUserResponse_ == NotSet\" << endl;\n");
	fprintf (script, "	} else {\n");
	fprintf (script, "		cout << \"FIXME: p_user_input.theUserResponse_ == Unhandled value \" << endl;\n");
	fprintf (script, "	}\n");
	fprintf (script, "\n");

	fprintf (script, "\n");
	fprintf (script, "	cout \n");
	fprintf (script, "		<< \"p_user_input.questionResponseData_:\" \n");
	fprintf (script, "		<< p_user_input.questionResponseData_ << endl;\n");
	fprintf (script, "\n");
	fprintf (script, "	if (last_question_visited) {\n");
	fprintf (script, "		cout << \"last_question_visited->questionName_:\" \n");
	fprintf (script, "			<<  last_question_visited->questionName_\n");
	fprintf (script, "			<< endl;\n");
	fprintf (script, "	} else {\n");
	fprintf (script, "		cout << \"last_question_visited->questionName_: is NULL\"  << endl;\n");
	fprintf (script, "	}\n");
	fprintf (script, "\n");

	fprintf (script, "	if (last_question_visited) {\n");
	fprintf (script, "		if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {\n");
	fprintf (script, "			if (p_user_input.userNavigation_ == NAVIGATE_PREVIOUS) {\n");
	fprintf (script, "				fprintf(qscript_stdout,\n");
	fprintf (script, "					\"user_navigation == NAVIGATE_PREVIOUS\\n\");\n");
	fprintf (script, "				AbstractRuntimeQuestion *target_question =\n");
	fprintf (script, "					theQuestionnaire->ComputePreviousQuestion(last_question_visited);\n");
	fprintf (script, "				if (target_question == 0) { \n");
	fprintf (script, "					stdout_eval (last_question_visited, theQuestionnaire, callback_ui_input, nest_level+ 1);\n");
	fprintf (script, "				} else {\n");
	fprintf (script, "					stdout_eval (target_question, theQuestionnaire, callback_ui_input, nest_level+ 1);\n");
	fprintf (script, "				}\n");
	fprintf (script, "				return;\n");
	fprintf (script, "			} else if (p_user_input.userNavigation_ == NAVIGATE_NEXT) {\n");
	fprintf (script, "				// do nothing \n");
	fprintf (script, "				// once we exit this major block == last_question_visited\n");
	fprintf (script, "				// the bottom of this function will handle it\n");

	fprintf (script, "			} else {\n");
	fprintf (script, "				cout << \"Unhandled case userNavigation_ ... exiting\" << endl\n");
	fprintf (script, "					<< __FILE__ << \",\" \n");
	fprintf (script, "					<< __LINE__ << \",\" \n");
	fprintf (script, "					<< __PRETTY_FUNCTION__ << \",\" \n");
	fprintf (script, "					<< endl;\n");
	fprintf (script, "				exit(1);\n");
	fprintf (script, "			}\n");
	fprintf (script, "		} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {\n");
	fprintf (script, "			// the management of correctly accepting data is handled \n");
	fprintf (script, "			// by : callback_ui_input\n");
	fprintf (script, "			// if we have reached back again here - it means it's\n");
	fprintf (script, "			// time to get the next question\n");
#if 0
	fprintf (script, "			AbstractQuestion * q =\n");
	fprintf (script, "				theQuestionnaire->eval2 (\n");
	fprintf (script, "				NAVIGATE_NEXT, last_question_visited, jump_to_question);\n");

	fprintf (script, "			if (!q) {\n");
	fprintf (script, "				cout << \"End of qnre();\" << endl << \">\";\n");
	fprintf (script, "				//int ch = getchar();\n");
	fprintf (script, "			} else {\n");

	fprintf (script, "			cout << __PRETTY_FUNCTION__ << \",\" << __LINE__ <<  \", eval2 return q = \"\n");
	fprintf (script, "				<< q->questionName_ << endl;\n");


	fprintf (script, "				stdout_eval (q, theQuestionnaire, callback_ui_input);\n");
	fprintf (script, "			}\n");
#endif /* 0 */
	fprintf (script, "\n");
	fprintf (script, "		} else if (p_user_input.theUserResponse_ == user_response::UserSavedData) {\n");
	fprintf (script, "			theQuestionnaire->write_data_to_disk(theQuestionnaire->question_list,\n");
	fprintf (script, "				theQuestionnaire->jno, theQuestionnaire->ser_no);\n");
	fprintf (script, "		} else {\n");
	fprintf (script, "			cout << \"Unhandled case userNavigation_ ... exiting\" << endl;\n");
	fprintf (script, "			exit(1);\n");
	fprintf (script, "		}\n");
	fprintf (script, "	} // else {\n");
	fprintf (script, "	// should reach here - end of :\n");
	fprintf (script, "		AbstractRuntimeQuestion * q =\n");
	fprintf (script, "			theQuestionnaire->eval2 (\n");
	fprintf (script, "			NAVIGATE_NEXT, last_question_visited, jump_to_question);\n");
	fprintf (script, "		if (!q) {\n");
	fprintf (script, "			cout << \"End of qnre();\" << endl << \">\";\n");
	fprintf (script, "		} else {\n");
	fprintf (script, "			cout << __PRETTY_FUNCTION__ << \",\" << __LINE__ <<  \", eval2 return q = \"\n");
	fprintf (script, "				<< q->questionName_ << endl;\n");
	fprintf (script, "			stdout_eval (q, theQuestionnaire, callback_ui_input, nest_level + 1);\n");
	fprintf (script, "		}\n");
	fprintf (script, "	//}\n");
	fprintf (script, "}\n");
	fprintf (script, "\n");

#endif /* 0 */
}



/* end of namespace */
}
