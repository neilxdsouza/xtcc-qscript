#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <cctype>
#include <unistd.h>
#include "AbstractQuestionnaire.h"
#include "question_stdout_runtime.h"
#include "stub_pair.h"
//#include "AbstractStatement.h"
#include "named_range.h"
#include "xtcc_set.h"
#include "datatype.h"
#include "qscript_lib.h"
#include "question_disk_data.h"
#include "question.h"
#include "user_navigation.h"
//#include "qtm_data_file.h"
//#include "qtm_datafile_conf_parser.h"
#include "ArrayQuestion.h"
//#include "AsciiFlatFileQuestionDiskMap.h"
//#include "XtccDataFile.h"
#include "base_text.h"
#include "named_attributes.h"
#include "QuestionAttributes.h"
#include "UserResponse.h"
#include "dom_manip_funcs.h"
#include "EvalReturnValue.h"
using namespace std;
//string qscript_stdout_fname("qscript_stdout.log");
//FILE * qscript_stdout = 0;
#include "debug_mem.h"


//fstream debug_log_file("qscript_debug.log", ios_base::out|ios_base::trunc);
extern fstream flat_file;
extern fstream xtcc_datafile;
extern fstream qtm_disk_file;
extern set<string> qtm_include_files;
using namespace std;
//extern vector<int32_t> data;
namespace program_options_ns { bool flag_nice_map = true; }
extern UserNavigation user_navigation;
vector<mem_addr_tab>  mem_addr;
//extern vector<question_disk_data*>  qdd_list;
bool write_messages_flag;

bool write_data_file_flag;
bool write_qtm_data_file_flag;
bool write_xtcc_data_file_flag;
bool card_start_flag;
bool card_end_flag;
int card_start;
int card_end;
int32_t check_if_reg_file_exists(string jno, int32_t ser_no);
void print_map_header(fstream & map_file);
map<string, vector<string> > map_of_active_vars_for_questions;
map<string, map<int, int> > freq_count;
void write_data_to_disk(const vector<AbstractRuntimeQuestion*>& q_vec, string jno, int32_t ser_no);
void SetupSignalHandler();
static void sig_usr(int32_t signo);
string output_data_file_name;
string output_qtm_data_file_name;
string output_xtcc_data_file_name;
void GetUserResponse(string& qno, int32_t &qindex);
string jno = "img_capt_in_for_loop";
char * flat_file_output_buffer = 0;
char * xtcc_datafile_output_buffer = 0;
int32_t len_flat_file_output_buffer  = 0;
int32_t len_xtcc_datafile_output_buffer  = 0;
//vector <AsciiFlatFileQuestionDiskMap*> ascii_flatfile_question_disk_map;
//vector <XtccDataFileDiskMap*> xtcc_question_disk_map;
//vector <qtm_data_file_ns::QtmDataDiskMap*> qtm_datafile_question_disk_map;
//qtm_data_file_ns::QtmDataFile qtm_data_file;
void Compute_FlatFileQuestionDiskDataMap(vector<AbstractRuntimeQuestion*> p_question_list);
void load_languages_available(vector<string> & vec_language);

//int process_options(int argc, char * argv[]);
	DIR * directory_ptr = 0;
struct TheQuestionnaire: public AbstractQuestionnaire
{
//CompoundStatement::GenerateCode()
// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 3, flagIsAForBody_: 0, source lineNo_: 1
//  virtual void RangeQuestion::GenerateCodeSingleQuestion(StatementCompiledCode&, bool)
XtccSet xs_0;
RangeQuestion * q1;
//CompoundStatement::GenerateCode()
// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 2, flagIsAForBody_: 1, source lineNo_: 13
//CompoundStatement::GenerateCode()
// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 2, flagIsAForBody_: 1, source lineNo_: 15
vector<int32_t> list_q2_array_bounds;
ArrayQuestion q2_list;
DummyArrayQuestion* dum_q2;
vector<int32_t> list_q3_array_bounds;
ArrayQuestion q3_list;
DummyArrayQuestion* dum_q3;
//  virtual void RangeQuestion::GenerateCodeSingleQuestion(StatementCompiledCode&, bool)
XtccSet xs_1;
//CompoundStatement::GenerateCode()
// Generating array declarations: flagGeneratedQuestionDefinitions_: 0, qscript_parser::for_loop_max_counter_stack.size(): 0, counterContainsQuestions_: 0, flagIsAForBody_: 1, source lineNo_: 22

TheQuestionnaire (string p_jno): AbstractQuestionnaire(p_jno)
 /* length(): 48 */,list_q2_array_bounds(1),list_q3_array_bounds(1)
{
xs_0.range.push_back(pair<int32_t,int32_t>(1,5));
{
vector<TextExpression *> text_expr_vec;
/* Enter: std::string PrintQuestionTitleCode(std::vector<TextExpression*>&)*/
text_expr_vec.push_back(new TextExpression(string("How many room details would you like to capture")));
/* Exit: std::string PrintQuestionTitleCode(std::vector<TextExpression*>&)*/
q1 = new RangeQuestion(QUESTION_TYPE, 10,string( "q1"), text_expr_vec,spn,1,INT32_TYPE,xs_0, QuestionAttributes(false , false, string("")), true, string(""));
print_question_messages(q1);
}
list_q2_array_bounds[0] = 5;
q2_list.SetArrayBounds(list_q2_array_bounds);
dum_q2= new DummyArrayQuestion("q2",list_q2_array_bounds);
question_list.push_back( dum_q2);
list_q3_array_bounds[0] = 5;
q3_list.SetArrayBounds(list_q3_array_bounds);
dum_q3= new DummyArrayQuestion("q3",list_q3_array_bounds);
question_list.push_back( dum_q3);
xs_1.range.push_back(pair<int32_t,int32_t>(1,20));

	questions_start_from_here_index = question_list.size();
	int our_question_index_no = 100000;
question_list.push_back(q1); q1 -> setQuestionIndexNo(our_question_index_no);
print_question_messages(q1);
for (int32_t i2 = 0;i2<5; ++i2) {
vector<int32_t> stack_of_loop_indices; /*  $# */
stack_of_loop_indices.push_back(i2);
/* sending quest_decl to array_quest_init_area  */
{ /*  NxD */
vector<TextExpression *> text_expr_vec;
/* Enter: std::string PrintQuestionTitleCode(std::vector<TextExpression*>&)*/
text_expr_vec.push_back(new TextExpression(string("Q2. Please click a photo of the room")));
/* Exit: std::string PrintQuestionTitleCode(std::vector<TextExpression*>&)*/
/*  NxD  */VideoCaptureQuestion * q2 = new VideoCaptureQuestion(QUESTION_TYPE, 18, string( "q2"), text_expr_vec, image_capture, stack_of_loop_indices , dum_q2, QuestionAttributes(false , false, string("")), true, string(""));
question_list.push_back(q2); q2 -> setQuestionIndexNo(our_question_index_no);
print_question_messages(q2);
q2_list.questionList.push_back(q2);
q2->array_q_ptr_ = &q2_list;
q2->index_in_array_question = q2_list.questionList.size() - 1;

}
{
vector<TextExpression *> text_expr_vec;
/* Enter: std::string PrintQuestionTitleCode(std::vector<TextExpression*>&)*/
text_expr_vec.push_back(new TextExpression(string("Q3. How many people can this room accomodate")));
/* Exit: std::string PrintQuestionTitleCode(std::vector<TextExpression*>&)*/
RangeQuestion * q3 = new RangeQuestion(QUESTION_ARR_TYPE, 21,string( "q3"), text_expr_vec,spn,1,INT32_TYPE,xs_1, stack_of_loop_indices , dum_q3, QuestionAttributes(false , false, string("")), false, string(""));
question_list.push_back(q3);q3 -> setQuestionIndexNo(our_question_index_no);
print_question_messages(q3);
q3_list.questionList.push_back(q3);
q3->array_q_ptr_ = &q3_list;
q3->index_in_array_question = q3_list.questionList.size() - 1;

}
	stack_of_loop_indices.pop_back();
}

	//compute_flat_file_map_and_init();
}

#if 0
void compute_flat_file_map_and_init()
{
if (write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)
{
	int current_map_pos = 0;
	int current_xtcc_map_pos = 0;
	if (write_qtm_data_file_flag) {
		qtm_datafile_conf_parser_ns::load_config_file(jno);
		qtm_data_file.Initialize();
	}
	if (write_data_file_flag) {
		stringstream asc_datafile_conf_str;
		asc_datafile_conf_str << jno
			<< ".asc_data.conf";
		fstream asc_datafile_conf(asc_datafile_conf_str.str().c_str(), ios_base::in);
		if (!asc_datafile_conf) {
			cerr << " could not open : " << asc_datafile_conf_str.str()
				<< " for reading" << endl;
			exit(1);
		}
		string ser_no_token; string equal_token; ser_no_pos=-1; string semi_colon_token;
		asc_datafile_conf >> ser_no_token;
		if ( ser_no_token != string("SER_NO_COLS")) {
			cerr << "expected token SER_NO_COLS" << endl;
			exit(1);
		}
		asc_datafile_conf >> equal_token;
		if (equal_token != string("=") ) {
			cerr << "expected token =" << endl;
			exit(1);
		}
		asc_datafile_conf >> ser_no_pos;
		if (ser_no_pos == -1) {
			cerr << "invalid no of positions reserved for serial no: ";
			exit(1);
		}
		current_map_pos += (ser_no_pos-1);
	}
	if (write_xtcc_data_file_flag) {
		current_xtcc_map_pos += 4; // serial no is 4 bytes fixed
	}
{
	AsciiFlatFileQuestionDiskMap * qscript_temp_1 = new AsciiFlatFileQuestionDiskMap(q1, current_map_pos);
	current_map_pos += qscript_temp_1->GetTotalLength();
	ascii_flatfile_question_disk_map.push_back(qscript_temp_1);
	if (write_xtcc_data_file_flag) {
	 XtccDataFileDiskMap * qscript_temp_2 = new XtccDataFileDiskMap(q1, current_xtcc_map_pos);
	 current_xtcc_map_pos += qscript_temp_2->GetTotalLength();
	 xtcc_question_disk_map.push_back(qscript_temp_2);
	}
	if (write_qtm_data_file_flag) {
		qtm_data_file_ns::QtmDataDiskMap * qscript_temp_3 = new qtm_data_file_ns::QtmDataDiskMap(q1, qtm_data_file, base_text_vec.back());
	 qtm_datafile_question_disk_map.push_back(qscript_temp_3);
	}
for (int32_t i2 = 0;i2<5; ++i2) {
vector<int32_t> stack_of_loop_indices; /*  $# */
stack_of_loop_indices.push_back(i2);
{
int32_t consolidated_for_loop_index_1 = i2;
base_text_vec.push_back(BaseText("All respondents where internal variable i2 is true is Less Than All who have answered question q1"));
{
	AsciiFlatFileQuestionDiskMap * qscript_temp_4 = new AsciiFlatFileQuestionDiskMap(q2_list.questionList[i2], current_map_pos);
	current_map_pos += qscript_temp_4->GetTotalLength();
	ascii_flatfile_question_disk_map.push_back(qscript_temp_4);
	if (write_xtcc_data_file_flag) {
	 XtccDataFileDiskMap * qscript_temp_5 = new XtccDataFileDiskMap(q2_list.questionList[i2], current_xtcc_map_pos);
	 current_xtcc_map_pos += qscript_temp_5->GetTotalLength();
	 xtcc_question_disk_map.push_back(qscript_temp_5);
	}
	if (write_qtm_data_file_flag) {
	qtm_data_file_ns::QtmDataDiskMap * qscript_temp_6 = new qtm_data_file_ns::QtmDataDiskMap(q2_list.questionList[i2], qtm_data_file, base_text_vec.back());
	 qtm_datafile_question_disk_map.push_back(qscript_temp_6);
	}
	AsciiFlatFileQuestionDiskMap * qscript_temp_7 = new AsciiFlatFileQuestionDiskMap(q3_list.questionList[i2], current_map_pos);
	current_map_pos += qscript_temp_7->GetTotalLength();
	ascii_flatfile_question_disk_map.push_back(qscript_temp_7);
	if (write_xtcc_data_file_flag) {
	 XtccDataFileDiskMap * qscript_temp_8 = new XtccDataFileDiskMap(q3_list.questionList[i2], current_xtcc_map_pos);
	 current_xtcc_map_pos += qscript_temp_8->GetTotalLength();
	 xtcc_question_disk_map.push_back(qscript_temp_8);
	}
	if (write_qtm_data_file_flag) {
	qtm_data_file_ns::QtmDataDiskMap * qscript_temp_9 = new qtm_data_file_ns::QtmDataDiskMap(q3_list.questionList[i2], qtm_data_file, base_text_vec.back());
	 qtm_datafile_question_disk_map.push_back(qscript_temp_9);
	}
}
base_text_vec.pop_back();
base_text_vec.push_back(BaseText("Not All respondents where internal variable i2 is true is Less Than All who have answered question q1"));
{
}
base_text_vec.pop_back();
}
	stack_of_loop_indices.pop_back();
}
}
	string map_file_name(jno + string(".map"));
	fstream map_file(map_file_name.c_str(), ios_base::out|ios_base::ate);
	 print_map_header(map_file);
	for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {
		ascii_flatfile_question_disk_map[i]->print_map(map_file);
	}
	string spss_syn_file_name(jno + string("-flat-ascii.sps"));
	fstream spss_syn_file(spss_syn_file_name.c_str(), ios_base::out|ios_base::ate);
	 spss_syn_file << "DATA LIST FILE='" <<  jno << ".dat'\n"<< endl << "/RESPID			1-6\n";
	for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {
		ascii_flatfile_question_disk_map[i]->write_spss_pull_data(spss_syn_file);
	}
	 spss_syn_file << ".\n";

 spss_syn_file << "exe.\n";
	for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {
		ascii_flatfile_question_disk_map[i]->write_spss_variable_labels(spss_syn_file);
	}

 spss_syn_file << "exe.\n";
	for (int i=0; i<ascii_flatfile_question_disk_map.size(); ++i) {
		ascii_flatfile_question_disk_map[i]->write_spss_value_labels(spss_syn_file);
	}

 spss_syn_file << "exe.\n";

 spss_syn_file << "save outfile=\"" << jno << ".sav\"\n";
	string xtcc_map_file_name(jno + string(".xmap"));
	fstream xtcc_map_file(xtcc_map_file_name.c_str(), ios_base::out|ios_base::ate);
	print_map_header(xtcc_map_file);
	for (int i=0; i<xtcc_question_disk_map.size(); ++i) {
		xtcc_question_disk_map[i]->print_map(xtcc_map_file);
	}
	len_flat_file_output_buffer = current_map_pos+1;
	len_xtcc_datafile_output_buffer = current_xtcc_map_pos+1;
	flat_file_output_buffer = new char[len_flat_file_output_buffer];
	xtcc_datafile_output_buffer = new char[len_xtcc_datafile_output_buffer];
	memset(flat_file_output_buffer, ' ', len_flat_file_output_buffer-1);
	memset(xtcc_datafile_output_buffer, '\0', len_xtcc_datafile_output_buffer-1);
	flat_file_output_buffer[len_flat_file_output_buffer-1] = 0;
	xtcc_datafile_output_buffer[len_xtcc_datafile_output_buffer-1] = 0;
	string flat_file_name(jno + string(".dat"));
	flat_file.open(flat_file_name.c_str(), ios_base::out | ios_base::trunc);
	string xtcc_datafile_name(jno + string(".xdat"));
	xtcc_datafile.open(xtcc_datafile_name.c_str(), ios_base::out | ios_base::trunc);
		{struct stat dir_exists; stringstream s1;
			s1 << "setup-" << jno;
			if (stat(s1.str().c_str(), &dir_exists) <0) {
				if (errno == ENOENT)
					if (mkdir(s1.str().c_str()) <0) {
						perror("unable to create directory for setup files");
					} else
						perror("stating directory failed");
			}
}
	if (write_qtm_data_file_flag) {
		string qtm_map_file_name(string("setup-") + jno + string("/") + jno + string(".qmap"));
		fstream qtm_map_file(qtm_map_file_name.c_str(), ios_base::out|ios_base::ate);
		print_map_header(qtm_map_file);
		for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {
			qtm_datafile_question_disk_map[i]->print_map(qtm_map_file);
		}
		string qtm_qax_file_name( string("setup-")+jno+string("/") + jno + string(".qax"));
		fstream qtm_qax_file(qtm_qax_file_name.c_str(), ios_base::out|ios_base::ate);
		map <string, vector<qtm_data_file_ns::QtmDataDiskMap*> > summary_tables;
		for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {
			qtm_datafile_question_disk_map[i]->print_qax(qtm_qax_file, string("setup-")+jno);
			string questionName = qtm_datafile_question_disk_map[i]->q->questionName_;
			if (qtm_datafile_question_disk_map[i]->q->loop_index_values.size() > 0) {
				summary_tables[questionName].push_back(qtm_datafile_question_disk_map[i]);
			}
		}
		for ( map <string, vector<qtm_data_file_ns::QtmDataDiskMap*> >::iterator it= summary_tables.begin();
				it != summary_tables.end(); ++it) {
			print_summary_axis(it->second, qtm_qax_file);
		}
		qtm_datafile_question_disk_map[0]->print_run(jno);
		string tab_file_name(string("setup-")+ jno + string("/") + jno + string(".tab"));
		fstream tab_file(tab_file_name.c_str(), ios_base::out|ios_base::ate);
		for (int i=0; i<qtm_datafile_question_disk_map.size(); ++i) {
			string questionName = qtm_datafile_question_disk_map[i]->q->questionName_;
			AbstractRuntimeQuestion * q = qtm_datafile_question_disk_map[i]->q;
			tab_file << "tab " << q->questionName_;
			for(int j=0; j<q->loop_index_values.size(); ++j) {
				tab_file << "_" << q->loop_index_values[j];
			}
			tab_file << " &ban" << endl;
		}
		qtm_datafile_question_disk_map[0]->qtmDataFile_.AllocateCards();
		qtm_datafile_question_disk_map[0]->qtmDataFile_.Reset();
		string qtm_disk_file_name(jno + string(".qdat"));
		qtm_disk_file.open(qtm_disk_file_name.c_str(), ios_base::out | ios_base::trunc);
	}
	if (write_xtcc_data_file_flag) {
		string xtcc_ax_file_name(string("setup-")+jno+string("/") + jno + string(".xtcc"));
		fstream xtcc_ax_file(xtcc_ax_file_name.c_str(), ios_base::out | ios_base::ate);
		xtcc_ax_file << "data_struct;rec_len=" << len_xtcc_datafile_output_buffer << ";\n";
		xtcc_ax_file << "ed_start\n";
		 xtcc_ax_file << "	int32_t edit_data();\n";
		 xtcc_ax_file << "	int32_t all;\n";
		 xtcc_ax_file << "	int32_t ser_no;\n";
		for (int i=0; i<xtcc_question_disk_map.size(); ++i) {
			xtcc_question_disk_map[i]->print_edit_var_defns(xtcc_ax_file, string("setup-")+jno+string("/"));
		}
		 xtcc_ax_file << "	int32_t edit_data()\n{\n";
		 xtcc_ax_file << "	all = 1;\n";
		 xtcc_ax_file << "	ser_no = c[0,3];\n";
		for (int i=0; i<xtcc_question_disk_map.size(); ++i) {
			xtcc_question_disk_map[i]->print_xtcc_edit_load(xtcc_ax_file, string("setup-")+jno+string("/"));
		}
		 xtcc_ax_file << "	}\n";
		xtcc_ax_file << "ed_end\n";
		xtcc_ax_file << "tabstart {\n";
		for (int i=0; i<xtcc_question_disk_map.size(); ++i) {
			xtcc_question_disk_map[i]->print_xtcc_tab(xtcc_ax_file, string("setup-")+jno+string("/"));
		}
		xtcc_ax_file << "}\n";
		xtcc_ax_file << "axstart {\n";
		xtcc_ax_file << "ax tot_ax;\n";
		xtcc_ax_file << "ttl; \"Total\";\n";
		xtcc_ax_file << "cnt; \"All\"; c= all==1;\n";
		for (int i=0; i<xtcc_question_disk_map.size(); ++i) {
			xtcc_question_disk_map[i]->print_xtcc_ax(xtcc_ax_file, string("setup-")+jno+string("/"));
		}
		xtcc_ax_file << "}\n";
	}
}
}
#endif /* 0 */

/* vector<AbstractRuntimeQuestion *> */ EvalReturnValue eval2 ( /*AbstractRuntimeQuestion * p_last_question_answered,
		 AbstractRuntimeQuestion * p_last_question_visited,*/
		 UserNavigation p_navigation_mode, const vector<AbstractRuntimeQuestion *> & p_last_question_visited, AbstractRuntimeQuestion * p_jump_to_index, const string & p_jump_to_group_name)
{
//if (last_question_visited)
	//fprintf (qscript_stdout, "entered eval2: last_question_visited: %s, stopAtNextQuestion: %d\n", last_question_visited->questionName_.c_str(), stopAtNextQuestion);
	/*
	if (write_data_file_flag||write_qtm_data_file_flag||write_xtcc_data_file_flag) {
		ser_no = read_a_serial_no();
		if (ser_no == 0) {
			exit(1);
		}
	} else {
		int exists = check_if_reg_file_exists(jno, ser_no);
		if (exists == 1) {
			map <string, question_disk_data*>  qdd_map;
			load_data (jno, ser_no, &qdd_map);
			//merge_disk_data_into_questions(qscript_stdout, last_question_answered, last_question_visited);
			//merge_disk_data_into_questions2 (qscript_stdout, last_question_answered, last_question_visited, this->question_list, &qdd_map);
		}
	}

	*/
	vector<string> error_messages_vec;
	error_messages_vec.clear();
	start_of_questions:
	if(back_jump == true){
	//fprintf(qscript_stdout, "have reached start_of_questions with back_jump: jumpToQuestion: %s, jumpToIndex: %d\n", jumpToQuestion.c_str(), jumpToIndex);
	}
{
/* compound statement on line no: 1 questionsInBlock_, size:3 q1, q2, q3,  */
/* ENTER: AbstractRuntimeQuestion::PrintSetupBackJump() : for_bounds_stack.size():0 */
lab_q1:
if( back_jump == true  && q1->isAnswered_ == true ) {
if( jumpToQuestion == "q1")
{ back_jump = false;
}
}
/* EXIT: AbstractRuntimeQuestion::PrintSetupBackJump()  */
/*  void AbstractQuestion::PrintEvalAndNavigateCode(std::ostringstream&)*/

if ( /* nxd */(q1->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
(q1->isAnswered_ && !q1->VerifyQuestionIntegrity())||
( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited.size() == 0) || (p_navigation_mode == NAVIGATE_NEXT && q1->questionNoIndex_ >  last_question_visited[last_question_visited.size()-1]-> questionNoIndex_ )) ||
(  (p_jump_to_group_name.length() == 0 && p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractRuntimeQuestion*>(q1    ) == p_jump_to_index)) ||  (p_jump_to_group_name.length()  > 0 && p_navigation_mode == NAVIGATE_PREVIOUS && q1 -> pageName_      == p_jump_to_group_name) )
 ||
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag)   && !(q1->question_attributes.isAllowBlank()) && q1->isAnswered_ == false )) {
label_eval_q1:
		if (q1->question_attributes.hidden_==false) {
	// q1->eval(question_window, stub_list_window, data_entry_window);

	//fprintf(qscript_stdout, "last_question_visited: q1\n");
/* page_nest_lev == 00 | NOT INSIDE A PAGE */
	 vector<AbstractRuntimeQuestion*> ret_vec;
	 ret_vec.push_back(q1);
	 last_question_visited.clear();
	 last_question_visited.push_back(q1);
	 EvalReturnValue ev_ret_val; 
	 ev_ret_val.qVec_ = ret_vec; 
	 ev_ret_val.errMessageVec_ = error_messages_vec; 
	 //return ret_vec;
	 return ev_ret_val;
	}
}
int32_t i2 = 0;
for (i2 = 0;i2<5;i2 = i2+1){
int32_t consolidated_for_loop_index_1 = i2;
/* compound statement on line no: 13 questionsInBlock_, size:2 q2, q3,  */
/* if_nest_level: 1 */
/*if (!q1->isAnswered_) {
cerr << "runtime error using unanswered question in expression: " << "q1" << endl;
}*/
int32_t qscript_temp_10 = q1->isAnswered_ ? *q1->input_data.begin() : INT_MAX;
if (i2<qscript_temp_10) {// ifStatementStack.size(): 0
// question_list_else_body :
{
/* compound statement on line no: 15 questionsInBlock_, size:2 q2, q3,  */
/* START ======== VideoQuestion::GenerateCode code goes here */
/* ENTER: AbstractRuntimeQuestion::PrintSetupBackJump() : for_bounds_stack.size():1 */
lab_q2:
if( back_jump == true  && q2_list.questionList[consolidated_for_loop_index_1]->isAnswered_ == true ) {
}
/* EXIT: AbstractRuntimeQuestion::PrintSetupBackJump()  */
/* START ======== VideoCaptureQuestion::GenerateCodeSingleQuestion code goes here array_mode :1 */
// if (data_entry_window == 0) {
	//cout << "jumpToQuestion = " << jumpToQuestion << endl;//	cout << "jumpToIndex = " << jumpToIndex << endl;//}

if (
(q2_list.questionList[i2]->isAnswered_ == false  && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
 stopAtNextQuestion ||
( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited.size() == 0) || 
  (p_navigation_mode == NAVIGATE_NEXT && 
  q2_list.questionList[i2]->questionNoIndex_ > last_question_visited[last_question_visited.size()-1]->questionNoIndex_)) ||

( 
(p_jump_to_group_name.length() == 0 && p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractRuntimeQuestion*>(q2_list.questionList[i2]  ) == p_jump_to_index) ) ||
(p_jump_to_group_name.length() >  0 && p_navigation_mode == NAVIGATE_PREVIOUS && q2_list.questionList[i2] -> pageName_    == p_jump_to_group_name)
 ) 
 ||
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag) 
  && !(q2_list.questionList[i2]->question_attributes.isAllowBlank()) && q2_list.questionList[i2]->isAnswered_ == false )) {
cout << "reached here because: " << 
"q2_list.questionList[i2]->isAnswered_ == false  && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) :" 
<< (q2_list.questionList[i2]->isAnswered_ == false  && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag))  << endl << q2_list.questionList[i2]->isAnswered_ << endl;
label_eval_q2:
if( jumpToQuestion == "q2" && jumpToIndex == consolidated_for_loop_index_1){
back_jump = false;
jumpToIndex = -1;
}
if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited[last_question_visited.size()-1] == q2_list.questionList[i2] &&  q2_list.questionList[i2]->isAnswered_ == true) {
 stopAtNextQuestion = true;
//fprintf (qscript_stdout, " at question:  q2 arming stopAtNextQuestion = true \n");
} else if ( q2_list.questionList[i2] ->question_attributes.hidden_==false) {
	 vector<AbstractRuntimeQuestion*> ret_vec;
ret_vec.push_back (q2_list.questionList[i2]);
		last_question_visited = ret_vec;
		stopAtNextQuestion = false;
	 last_question_visited.clear();
	 last_question_visited.push_back(q2_list.questionList[i2]);
	 EvalReturnValue ev_ret_val; 
	 ev_ret_val.qVec_ = ret_vec; 
	 ev_ret_val.errMessageVec_ = error_messages_vec; 
	 return ev_ret_val;

	}
}
/* END ======== VideoCaptureQuestion::GenerateCodeSingleQuestion code goes here */
/* END ======== VideoQuestion::GenerateCode code goes here */
/* ENTER: AbstractRuntimeQuestion::PrintSetupBackJump() : for_bounds_stack.size():1 */
lab_q3:
if( back_jump == true  && q3_list.questionList[consolidated_for_loop_index_1]->isAnswered_ == true ) {
}
/* EXIT: AbstractRuntimeQuestion::PrintSetupBackJump()  */
// if (data_entry_window == 0) {
	//cout << "jumpToQuestion = " << jumpToQuestion << endl;//	cout << "jumpToIndex = " << jumpToIndex << endl;//}

if (
(q3_list.questionList[i2]->isAnswered_ == false  && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||
 stopAtNextQuestion ||
( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited.size() == 0) || 
  (p_navigation_mode == NAVIGATE_NEXT && 
  q3_list.questionList[i2]->questionNoIndex_ > last_question_visited[last_question_visited.size()-1]->questionNoIndex_)) ||

( 
(p_jump_to_group_name.length() == 0 && p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractRuntimeQuestion*>(q3_list.questionList[i2]  ) == p_jump_to_index) ) ||
(p_jump_to_group_name.length() >  0 && p_navigation_mode == NAVIGATE_PREVIOUS && q3_list.questionList[i2] -> pageName_    == p_jump_to_group_name)
 ) 
 ||
((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag) 
  && !(q3_list.questionList[i2]->question_attributes.isAllowBlank()) && q3_list.questionList[i2]->isAnswered_ == false )) {
cout << "reached here because: " << 
"q3_list.questionList[i2]->isAnswered_ == false  && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) :" 
<< (q3_list.questionList[i2]->isAnswered_ == false  && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag))  << endl << q3_list.questionList[i2]->isAnswered_ << endl;
label_eval_q3:
if( jumpToQuestion == "q3" && jumpToIndex == consolidated_for_loop_index_1){
back_jump = false;
jumpToIndex = -1;
}
if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited[last_question_visited.size()-1] == q3_list.questionList[i2] &&  q3_list.questionList[i2]->isAnswered_ == true) {
 stopAtNextQuestion = true;
//fprintf (qscript_stdout, " at question:  q3 arming stopAtNextQuestion = true \n");
} else if ( q3_list.questionList[i2] ->question_attributes.hidden_==false) {
	 vector<AbstractRuntimeQuestion*> ret_vec;
ret_vec.push_back (q3_list.questionList[i2]);
		last_question_visited = ret_vec;
		stopAtNextQuestion = false;
	 last_question_visited.clear();
	 last_question_visited.push_back(q3_list.questionList[i2]);
	 EvalReturnValue ev_ret_val; 
	 ev_ret_val.qVec_ = ret_vec; 
	 ev_ret_val.errMessageVec_ = error_messages_vec; 
	 return ev_ret_val;

	}
}
}
 }
 else {
// end of ifBody_->GetQuestionNames 
 // elseIfStatement DOES NOT exists 
/* question_list_if_body.size(): 1 */ 
// nestedCompoundStatementStack_.size(): 3
// cmpd_stmt->flagIsAForBody_: 1
// question_name type is QUESTION_ARR_TYPE: 
// IfStatement nestLevel_: 3
// IfStatement forNestLevel_: 1
// q3: , nestLevel_: // q3: , forNestLevel_: 1
// enclosingCompoundStatement_ is CompoundStatement 
// and enclosingCompoundStatement_ is part of a for loop 
q3_list.questionList[i2]->isAnswered_ = false;
// **************** 
{
/* compound statement on line no: 22 questionsInBlock_, size:0  */
/* ENTER ExpressionStatement::GenerateCode */
1;
}
}
}
}

	{ EvalReturnValue ev_ret_val; return ev_ret_val;}
} /* close eval */
};
#include "question_logic.h"
//#include "json.h"
/* ============= new_logic_support_frag event driven - emscripten =========*/
struct TheQuestionnaire * make_questionnaire ()
{
	TheQuestionnaire * theQuestionnaire = new TheQuestionnaire (jno);
	theQuestionnaire->base_text_vec.push_back(BaseText("All Respondents"));
	return theQuestionnaire;
}
//void question_eval_loop2 (
//	UserInput p_user_input,
//	AbstractRuntimeQuestion * last_question_visited,
//	AbstractRuntimeQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire, int nest_level);

int callback_get_ser_no_from_ui (int p_ser_no, int nest_level, char * survey_data)
{
	//my_log_from_cpp ("Entered: callback_get_ser_no_from_ui");
	// now its not :-) // nxd: this is a global variable - has to be eliminated at some point
	TheQuestionnaire * theQuestionnaire = new TheQuestionnaire (jno);
	//cout << "received serial no : " << p_ser_no << "from ui";
	printf ("received serial no : %d from ui\n", p_ser_no );

	theQuestionnaire->ser_no = p_ser_no;
	theQuestionnaire->base_text_vec.push_back(BaseText("All Respondents"));
	//theQuestionnaire->compute_flat_file_map_and_init();
	UserNavigation qnre_navigation_mode = NAVIGATE_NEXT;

	AbstractRuntimeQuestion * last_question_visited = 0;
	AbstractRuntimeQuestion * jump_to_question = 0;

	string str_survey_data(survey_data);
	if (str_survey_data.length() > 0) {
		map <string, question_disk_data*>  qdd_map;
		map <string, vector<int> >  randomization_order;
		//my_log_from_cpp ("going to parse survey_data");
		int r_val =  load_data_from_string (str_survey_data.c_str(), &qdd_map, &randomization_order);
		//my_log_from_cpp ("finished parsing survey_data ");
		//stringstream rnd_order_str;
		//for (map<string, vector<int> >::iterator it = randomization_order.begin();
		//		it != randomization_order.end(); ++it) {
		//	rnd_order_str << it->first << ":";
		//	for (int i = 0; i < it->second.size(); ++i) {
		//		rnd_order_str << " " << it->second[i];
		//	}
		//	rnd_order_str << endl;
		//}
		//my_log_from_cpp (rnd_order_str.str().c_str());
		printf ("after load_data_from_string r_val: %d\n", r_val);
		merge_disk_data_into_questions2 (/*qscript_stdout*/ 0,
			theQuestionnaire->last_question_answered,
			theQuestionnaire->last_question_visited,
			theQuestionnaire->question_list, &qdd_map,
			theQuestionnaire->named_attribute_list_vec, randomization_order);
		my_log_from_cpp ("finished merging answers");
	}
	EvalMode qnre_mode = NORMAL_FLOW;
	//question_eval_loop (qnre_mode,
	//			qnre_navigation_mode, last_question_visited,
	//			jump_to_question, theQuestionnaire);
	UserInput l_user_input;
	vector <AbstractRuntimeQuestion*> empty_vec;
	question_eval_loop2 (
				l_user_input, /* last_question_visited */ empty_vec,
				/* jump_to_question */ 0, theQuestionnaire, nest_level + 1);
	//cout << "finished qnre: exiting ..." << endl;
	//cout << "commented out prompt_user_for_serial_no" << endl;
	//prompt_user_for_serial_no (callback_get_ser_no_from_ui, nest_level + 1);
	return 0;
}


void parse_input_data(vector<int> * data_ptr, int & success);
//void callback_ui_input (UserInput p_user_input, AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire, int nest_level);
//void eval_single_question_logic_with_input (UserInput p_user_input, AbstractRuntimeQuestion * q, struct TheQuestionnaire * theQuestionnaire, int nest_level);


void callback_ui_input (UserInput p_user_input,
		const vector<AbstractRuntimeQuestion *> & q_vec,
		struct TheQuestionnaire * theQuestionnaire, int nest_level,
		vector <string> & err_mesg_vec)
{
	my_log_from_cpp ("callback_ui_input in emscripten_support_frag.cpp: ");
	//cout << __PRETTY_FUNCTION__ << endl;
	//printf ("%s\n", __PRETTY_FUNCTION__);
	//my_log_from_cpp ("Enter callback_ui_input");
	// this will be called by the UI - it is the UI's responsibility to
	// get valid data for us
	//bool valid_input = q->VerifyResponse (p_user_input.theUserResponse_, p_user_input.userNavigation_);
	if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {
		question_eval_loop2 (
				p_user_input,
				/* last_question_visited */ q_vec,
				/*  jump_to_question */ 0, theQuestionnaire, nest_level + 1);
	} else if (p_user_input.theUserResponse_ == user_response::UserViewedVideo) {
		vector <string> err_mesg_vec;
		eval_single_question_logic_with_input (p_user_input, q_vec, theQuestionnaire, nest_level + 1, err_mesg_vec);
		question_eval_loop2 (p_user_input, q_vec, 0, theQuestionnaire, nest_level + 1);
	} else if (p_user_input.theUserResponse_ == user_response::UserViewedImage) {
		//my_log_from_cpp ("callback_ui_input: UserViewedImage");
		vector <string> err_mesg_vec;
		eval_single_question_logic_with_input (p_user_input, q_vec, theQuestionnaire, nest_level + 1, err_mesg_vec);
		question_eval_loop2 (p_user_input, q_vec, 0, theQuestionnaire, nest_level + 1);
	} else if (p_user_input.theUserResponse_ == user_response::UserListenedToAudio) {
		vector <string> err_mesg_vec;
		eval_single_question_logic_with_input (p_user_input, q_vec, theQuestionnaire, nest_level + 1, err_mesg_vec);
		question_eval_loop2 (p_user_input, q_vec, 0, theQuestionnaire, nest_level + 1);
	} else if (p_user_input.theUserResponse_ == user_response::UserCapturedTime) {
		vector <string> err_mesg_vec;
		eval_single_question_logic_with_input (p_user_input, q_vec, theQuestionnaire, nest_level + 1, err_mesg_vec);
		question_eval_loop2 (p_user_input, q_vec, 0, theQuestionnaire, nest_level + 1);
	} else if (p_user_input.theUserResponse_ == user_response::UserGeocodedLocation) {
		vector <string> err_mesg_vec;
		eval_single_question_logic_with_input (p_user_input, q_vec, theQuestionnaire, nest_level + 1, err_mesg_vec);
		question_eval_loop2 (p_user_input, q_vec, 0, theQuestionnaire, nest_level + 1);
	} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {
		vector <string> err_mesg_vec;
		bool all_questions_success =
			eval_single_question_logic_with_input (p_user_input,
					q_vec, theQuestionnaire,
					nest_level + 1, err_mesg_vec);
		if (all_questions_success) {
			question_eval_loop2 (p_user_input, q_vec, 0, theQuestionnaire, nest_level + 1);
		} else {
			// in the event driven loop - just return
			// we need to pass the error messages back
			// so should make that a parameter to this
			// function

			stringstream err_json_string;
			err_json_string << "[" << endl;
			for (int i=0; i < err_mesg_vec.size(); ++i ) {
				if (i > 0 ) {
					err_json_string << "," ;
				}
				err_json_string << "\"" << err_mesg_vec[i] << "\"";
			}
			err_json_string << "]" << endl;
			current_question_errors (err_json_string.str().c_str());
			return;
		}
	} else if (p_user_input.theUserResponse_ == user_response::UserSavedData) {
		//cout << "under stdout either the user can enter data or navigation" << endl
		//	<< "but under ncurses or other guis - it's possible to enter data" << endl
		//	<< " AND ask to save by pressing f4, in which case we should save the data "
		//	<< " and then try to validate the user input - just like we would in a normal case"
		//	<< endl;
		// nxd: this function needs to be cleaned up
		//      we can easily downcast to an AbstractQuestionnaire and then there is no need for this
		//      function to be present here
		theQuestionnaire->write_data_to_disk (theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);
	} else {
		//cerr << __PRETTY_FUNCTION__ << " unhandled case theUserResponse_" << endl;
	}
	printf("EXIT: %s\n", __PRETTY_FUNCTION__);
}

void question_eval_loop2 (
	UserInput p_user_input,
	const vector<AbstractRuntimeQuestion *> & last_question_visited,
	AbstractRuntimeQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire, int nest_level)
{
	//my_log_from_cpp ("question_eval_loop2");
	//printf ("Enter: %s\n", __PRETTY_FUNCTION__);
	//cout << endl << "Enter: " << __PRETTY_FUNCTION__ << endl;
	//cout << "arg values: " << endl;
	if (p_user_input.userNavigation_ == NAVIGATE_NEXT) {
		//cout << "p_user_input.userNavigation_ == NAVIGATE_NEXT" << endl;
		//printf ("p_user_input.userNavigation_ == NAVIGATE_NEXT\n");
	} else if (p_user_input.userNavigation_ == NAVIGATE_PREVIOUS) {
		//printf ("p_user_input.userNavigation_ == NAVIGATE_PREVIOUS\n");
	} else {
		printf ("FIXME: p_user_input.userNavigation_ == Unhandled value\n");
	}
	if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {
		printf ("p_user_input.theUserResponse_ == UserEnteredNavigation");
	} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {
		//cout << "p_user_input.theUserResponse_ == UserEnteredData" << endl;
	} else if (p_user_input.theUserResponse_ == user_response::UserClearedData) {
		//cout << "p_user_input.theUserResponse_ == UserClearedData" << endl;
	} else if (p_user_input.theUserResponse_ == user_response::UserSavedData) {
		//cout << "p_user_input.theUserResponse_ == UserSavedData" << endl;
	} else if (p_user_input.theUserResponse_ == user_response::NotSet) {
		//cout << "p_user_input.theUserResponse_ == NotSet" << endl;
	} else {
		//cout << "FIXME: p_user_input.theUserResponse_ == Unhandled value " << endl;
	}


	//cout << "p_user_input.questionResponseData_:" << p_user_input.questionResponseData_ << endl;

	if (last_question_visited.size() > 0) {
		//cout << "last_question_visited->questionName_:"
		//	<<  last_question_visited->questionName_
		//	<< endl;
		//printf ("last_question_visited->questionName_:%s\n",
		//		last_question_visited[0]->questionName_.c_str());
	} else {
		//cout << "last_question_visited->questionName_: is NULL"  << endl;
		//printf ("last_question_visited->questionName_ is NULL\n");
	}

	if (last_question_visited.size() > 0) {
		//my_log_from_cpp ("last_question_visited.size() > 0");
		if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {
			if (p_user_input.userNavigation_ == NAVIGATE_PREVIOUS) {
				//fprintf(qscript_stdout, "user_navigation == NAVIGATE_PREVIOUS unhandled\n");
				//printf("%s, %s, %d, user_navigation == NAVIGATE_PREVIOUS unhandled\n",
				//		__PRETTY_FUNCTION__, __FILE__, __LINE__);
#if 1
				//AbstractRuntimeQuestion *target_question =
				struct ComputePreviousQuestionRetVal prev_question_ret_val = 
					theQuestionnaire->ComputePreviousQuestion(last_question_visited[0]);
				// this line seems unncessary - but it is necessary
				// - DO NOT DELETE AS REDUNDANT
				//vector<AbstractRuntimeQuestion *> q_vec =
				//string dummy_group_name;
				//EvalReturnValue eval_ret_val =
				//	theQuestionnaire->eval2 (
				//	NAVIGATE_PREVIOUS, last_question_visited, target_question,
				//	dummy_group_name);

				EvalReturnValue eval_ret_val =
					theQuestionnaire->eval2 (
					NAVIGATE_PREVIOUS, last_question_visited, prev_question_ret_val.singlePreviousQuestion_,
					prev_question_ret_val.questionGroupName_);
				vector <AbstractRuntimeQuestion*> & q_vec = eval_ret_val.qVec_;
				//if (target_question == 0) 
				if (prev_question_ret_val.singlePreviousQuestion_ == 0) {
					stdout_eval (last_question_visited, theQuestionnaire,
							callback_ui_input, nest_level + 1, eval_ret_val.errMessageVec_);
				} else {
					stdout_eval (q_vec, theQuestionnaire,
							callback_ui_input, nest_level + 1, eval_ret_val.errMessageVec_);
				}
#endif /* 0 */
				return;
			} else if (p_user_input.userNavigation_ == NAVIGATE_NEXT) {
				// do nothing
				// once we exit this major block == last_question_visited
				// the bottom of this function will handle it
			} else {
				//cout << "Unhandled case userNavigation_ ... exiting" << endl
				//	<< __FILE__ << ","
				//	<< __LINE__ << ","
				//	<< __PRETTY_FUNCTION__ << ","
				//	<< endl;
				exit(1);
			}
		} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {
			// the management of correctly accepting data is handled
			// by : callback_ui_input
			// if we have reached back again here - it means it's
			// time to get the next question




		} else if (p_user_input.theUserResponse_ == user_response::UserViewedVideo ||
				p_user_input.theUserResponse_ == user_response::UserViewedImage ||
				p_user_input.theUserResponse_ == user_response::UserListenedToAudio
				) {
				// do nothing
				// once we exit this major block == last_question_visited
				// the bottom of this function will handle it
		} else if (p_user_input.theUserResponse_ == user_response::UserCapturedTime) {
				// do nothing
		} else if (p_user_input.theUserResponse_ == user_response::UserGeocodedLocation) {
				// do nothing
				// once we exit this major block == last_question_visited
				// the bottom of this function will handle it
		} else {
			//cout << "Unhandled case userNavigation_ ... exiting" << endl;
			exit(1);
		}
	} // else {
	// should reach here - end of :
		//vector<AbstractRuntimeQuestion *> q_vec =
		//my_log_from_cpp ("Just before theQuestionnaire->eval2");
		string dummy_group_name2;
		EvalReturnValue eval_ret_val =
			theQuestionnaire->eval2 (
			NAVIGATE_NEXT, last_question_visited, jump_to_question,
			dummy_group_name2);
		//my_log_from_cpp ("Just after theQuestionnaire->eval2");
		vector <AbstractRuntimeQuestion*> & q_vec = eval_ret_val.qVec_;
		if (q_vec.size() == 0) {
			//printf(" eval2 has returned NULL => End of qnre();\n");
			//my_log_from_cpp(" eval2 has returned NULL => End of qnre();\n");
			show_end_of_qnre_page();
		} else {
			//stringstream eval2_retval_str;
			//eval2_retval_str << "q_vec.size(): " << q_vec.size() ;
			//for (int i=0; i < q_vec.size(); ++i) {
			//	eval2_retval_str << q_vec[i]->questionName_;
			//	for (int j=0; j < q_vec[i]->loop_index_values.size(); ++j) {
			//		eval2_retval_str << "$" << q_vec[i]->loop_index_values[j];
			//	}
			//	eval2_retval_str << endl;
			//}
			//my_log_from_cpp(eval2_retval_str.str().c_str());
			//printf(" eval2 has returned first q in vec: %s\n", q_vec[0]->questionName_.c_str());
			//cout << __PRETTY_FUNCTION__ << "," << __LINE__ <<  ", eval2 return q = "
			//	<< q->questionName_ << endl;
			//string qnre_data = theQuestionnaire->write_data_to_disk (theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);
			// *
			const int MAX_DATAFILE_SIZE = 50000;
			char buffer[MAX_DATAFILE_SIZE]; int n_left = MAX_DATAFILE_SIZE;
			char * buffer_start_ptr = buffer;
			//string qnre_data = theQuestionnaire->write_data_to_disk (theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);

			int n_written = theQuestionnaire->
				write_data_to_buffer
					(
						theQuestionnaire->question_list,
						theQuestionnaire->jno,
						theQuestionnaire->ser_no,
						buffer_start_ptr,
						n_left);
			if (n_written > 0) {
				save_qnre_data (buffer);
			}
			// * /
			stdout_eval (q_vec, theQuestionnaire, callback_ui_input, nest_level + 1, eval_ret_val.errMessageVec_);
		}
	//}
}

void set_last_visited (struct TheQuestionnaire * qnre, AbstractRuntimeQuestion * last_question_visited)
{
	qnre->last_question_visited[qnre->last_question_visited.size()-1] = last_question_visited;
}

#include "utils.h"

extern "C" {

void callback_return_serial (int serial_no, char * survey_data)
{
	//my_log_from_cpp ("Entered callback_return_serial:");
	//printf ("Got a serial no from the DOM: %d, survey_data: |%s|\n", serial_no, survey_data);
	printf ("Got a serial no from the DOM: %d\n", serial_no);
	//TheQuestionnaire * l_qnre_ptr = dynamic_cast<TheQuestionnaire*> (AbstractQuestionnaire::qnre_ptr);
	callback_get_ser_no_from_ui (serial_no, 1, survey_data);
}

void called_from_the_dom (char * data, char * other_specify_data)
{
	//current_question_errors (ptr);
	//emscripten_pause_main_loop();
	//emscripten_resume_main_loop();
	//printf ("data from the browser dom callback: %s\n", data);
	//char err_mesg_buffer[4000];
	//printf ("Enter: called_from_the_dom: data %s\n", data);
	my_log_from_cpp ("Entered called_from_the_dom");
	//my_log_from_cpp (data);
	string str_data (data);
	vector <string> question_data_vec = split_on_char (data, '|');
	//string str_other_specify_data(other_specify_data);
	//if (str_other_specify_data.length() > 0) {
	//	json_value * the_json_object = json_parse (str_other_specify_data.c_str(), str_other_specify_data.length());
	//	if ( AbstractQuestionnaire::qnre_ptr->last_question_visited.size() == 1) {
	//		NamedStubQuestion * nq = dynamic_cast <NamedStubQuestion*> (AbstractQuestionnaire::qnre_ptr->last_question_visited[0]);
	//		if (nq) {
	//			nq->nr_ptr->stubs[6].stub_text = "New Other Specify Brand 1";
	//			nq->nr_ptr->stubs[7].stub_text = "New Other Specify Brand 2";
	//		}
	//	}
	//}
#if 0
	//printf ("data: %s\n", data);
	AbstractRuntimeQuestion * q = AbstractQuestionnaire::qnre_ptr->last_question_visited[0];
	printf ("last_question_visited: %s\n", q->questionName_.c_str());
	// hard code the answers - Proof of concept testing
	// Can we really load the next question on the interface using this callback system?
	//q->isAnswered_ = true;
	//q->input_data.insert (2);
	//UserInput user_input;
	//user_input.theUserResponse_ = user_response::UserEnteredData;
	//user_input.questionResponseData_ = "1";
	UserInput user_input;
	user_input.theUserResponse_ = user_response::UserEnteredData;
	user_input.questionResponseDataVec_.push_back(data);
	string err_mesg;
	bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
	TheQuestionnaire * l_qnre_ptr = dynamic_cast<TheQuestionnaire*> (AbstractQuestionnaire::qnre_ptr);

	if (valid_input) {
		if (user_input.theUserResponse_ == user_response::UserSavedData) {
			cerr  << "NOT YET DONE"
				<< __FILE__ << "," << __LINE__ << "," << __PRETTY_FUNCTION__
				<< endl
				<< "invoking callback_ui_input with UserSavedData" << endl;
			// this call will return really fast
			//  (if you consider io fast)
			//  but what I mean is we wont add much to the call stack
			//callback_ui_input (user_input, q, theQuestionnaire_, 1);
			//GetUserInput (callback_ui_input, q, theQuestionnaire);
			//cout << "callback_ui_input has returned after UserSavedData" << endl;
		} else {
			cout << "reached here: "
				<< __PRETTY_FUNCTION__ << endl;
			callback_ui_input (user_input,
					AbstractQuestionnaire::qnre_ptr->last_question_visited,
					l_qnre_ptr, 1);
			cout << "callback_ui_input has returned"
				<< __PRETTY_FUNCTION__ << endl;
		}
		// move all this into callback_ui_input
		// case UserEnteredData
	}
	//void question_eval_loop2 (
	//	UserInput p_user_input,
	//	AbstractRuntimeQuestion * last_question_visited,
	//	AbstractRuntimeQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire, int nest_level );
	//question_eval_loop2 (user_input, q, 0, l_qnre_ptr, /*nest_level + */ 1);
#endif /*  0  */

	//vector <UIReturnValue> ui_question_status;
	stringstream not_answered_question_list;
	bool all_questions_answered = true;
	UserInput user_input;
	for (int32_t i = 0;
		i < AbstractQuestionnaire::qnre_ptr->last_question_visited.size();
		++i) {
		AbstractRuntimeQuestion * q =
				AbstractQuestionnaire::qnre_ptr->last_question_visited[i];
#if 0
		AbstractRuntimeQuestion * last_question_served =
				AbstractQuestionnaire::qnre_ptr->last_question_visited[i];
		if (NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion *>(last_question_served)) {
			//AbstractRuntimeQuestion * last_question_served = this_users_session -> ptr_last_question_visited ;
			vector<int32_t> data;
			bool isAnswered = false;
			cout << "returned back data from question: " << nq->questionName_ << endl;
			if (last_question_served->no_mpn == 1) {
				UIReturnValue ret_val ;
				ui_question_status.push_back(ret_val) ;
			} else {
				cout << "Reached NamedStubQuestion and currently doing nothing" << endl;
				UIReturnValue ret_val = handleCBDataInput(1, i);
				ui_question_status.push_back(ret_val) ;
			}
		} else {
			/*
			string current_question_response = le_data_->text().narrow();
			if (current_question_response !="") {
				handleRangeQuestionData(1);
			}
			*/
			cout << __PRETTY_FUNCTION__ << "Handle WLineEdit data not yet implemented" << endl;

		}
#endif /*  0  */
		if (q->q_type == video) {
			user_input.theUserResponse_ = user_response::UserViewedVideo;
			//my_log_from_cpp ("UserViewedVideo"); 
		} else if (q->q_type == image) {
			user_input.theUserResponse_ = user_response::UserViewedImage;
			//my_log_from_cpp ("UserViewedImage"); 
		} else if (q->q_type == audio) {
			user_input.theUserResponse_ = user_response::UserListenedToAudio;
		} else if (q->q_type == video_capture || q->q_type == audio_capture || q->q_type == image_capture) {
			user_input.theUserResponse_ = user_response::UserCapturedTime;
		} else if (q->q_type == geocode_gmapv3) {
			user_input.theUserResponse_ = user_response::UserGeocodedLocation;
			my_log_from_cpp ("geocode_gmapv3");
		} else {

			if (question_data_vec[i].length() > 0) {
				user_input.theUserResponse_ = user_response::UserEnteredData;
				user_input.questionResponseDataVec_.push_back(question_data_vec[i]);
			} else if (question_data_vec[i].length() == 0 && q->question_attributes.allowBlank_ == true) {
				//my_log_from_cpp ("response is empty but blanks are allowed");
				user_input.theUserResponse_ = user_response::UserEnteredData;
				user_input.questionResponseDataVec_.push_back(question_data_vec[i]);
			} else {
				all_questions_answered = false;
				not_answered_question_list << " " << q->questionName_;
				//my_log_from_cpp ("not_answered all questions");
			}
		}
	}
	if (all_questions_answered == false)  {
		//printf("Please answer all the questions on the page: %s\n",
		//		not_answered_question_list.str().c_str()
		//      );
		stringstream err_mesg;
		err_mesg << "Please answer all the questions on the page: "
			<< not_answered_question_list.str();
		current_question_errors (err_mesg.str().c_str());
		return;
	} else {
		// send question for back end verification
		AbstractQuestionnaire * abs_qnre_ptr = AbstractQuestionnaire::qnre_ptr;
		TheQuestionnaire * l_qnre_ptr = dynamic_cast<TheQuestionnaire*> (AbstractQuestionnaire::qnre_ptr);
		vector <string> err_mesg_vec;
		callback_ui_input (user_input,
			abs_qnre_ptr->last_question_visited,
			l_qnre_ptr, 1, err_mesg_vec);
	}


	printf ("EXIT: %s\n", __PRETTY_FUNCTION__);
}

void navigate_previous (char * data)
{
	//my_log_from_cpp ("Enter: navigate_previous");
	UserInput user_input;
	user_input.userNavigation_ = NAVIGATE_PREVIOUS;
	user_input.theUserResponse_ = user_response::UserEnteredNavigation;
	AbstractQuestionnaire * abs_qnre_ptr = AbstractQuestionnaire::qnre_ptr;
	TheQuestionnaire * l_qnre_ptr = dynamic_cast<TheQuestionnaire*> (AbstractQuestionnaire::qnre_ptr);
	vector <string> err_mesg_vec;
	callback_ui_input (user_input,
			abs_qnre_ptr->last_question_visited,
			l_qnre_ptr, 1, err_mesg_vec);
	//my_log_from_cpp ("Exit: navigate_previous");
}

}
