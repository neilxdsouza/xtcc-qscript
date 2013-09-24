/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/question.cpp
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009
 *  Neil Xavier D'Souza
 */
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <panel.h>

#include "expr.h"
#include "question.h"
#include "named_range.h"
#include "scope.h"
#include "qscript_parser.h"
#include "user_navigation.h"
#include "qscript_readline.h"
#include "utils.h"
#include "UserResponse.h"

int32_t scan_datalex();
int32_t scan_dataparse();
//extern vector<int32_t> data;
extern UserNavigation user_navigation;
// extern user_response::UserResponseType the_user_response;

namespace program_options_ns {
	extern bool ncurses_flag;
	extern bool static_binary_flag;
	extern bool web_server_flag;
	extern bool compile_to_cpp_only_flag;
	extern int32_t fname_flag;
	extern bool no_question_save_restore_optimization;
	extern bool emscripten_flag;
}

using program_options_ns::no_question_save_restore_optimization;

using std::cout;
using std::endl;
using std::cerr;
using namespace std;
//extern map<string, vector<string> > map_of_active_vars_for_questions;
//void read_data(const char * prompt);
//user_response::UserResponseType read_data( const char * prompt)
//void read_data_from_window(WINDOW * data_entry_window, char * prompt, );
string PrintConsolidatedForLoopIndex(vector<AbstractExpression*> for_bounds_stack);
extern vector<string> consolidated_for_loop_index_stack;
int32_t GetTempMapKeyNumber();
string GetRestoreVariableName(ActiveVariableInfo * av_info);
string GetRestoreVariableContainerName(ActiveVariableInfo * av_info
				       , string & questionName_);
string GetRestoreVariableContainerNameArray(
	ActiveVariableInfo * av_info, string & questionName_, string map_key);
extern vector<string> consolidated_for_loop_index_stack;

	//! this is only called in the compile time environment
AbstractQuestion::AbstractQuestion(
	DataType l_type, int32_t l_no, string l_name, vector<TextExpression*> text_expr_vec
	, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
	, vector<AbstractExpression*> & l_for_bounds_stack
	, CompoundStatement * l_enclosing_scope
	, vector<ActiveVariableInfo* > l_av_info, QuestionAttributes  l_question_attributes
	, const XtccSet & p_mutexCodeList
	)
	:
	AbstractStatement(l_type, l_no)
	, questionName_(l_name), textExprVec_(text_expr_vec)
	, questionDiskName_()
	,  q_type(l_q_type)
	, no_mpn(l_no_mpn), dt(l_dt), input_data()
	, for_bounds_stack(l_for_bounds_stack), loop_index_values(0)
	, isAnswered_(false), isModified_(false)
	, enclosingCompoundStatement_(l_enclosing_scope)
	, activeVarInfo_(l_av_info)
	, dummyArrayQuestion_(0), currentResponse_()
	, question_attributes(l_question_attributes)
	, mutexCodeList_(p_mutexCodeList), maxCode_(0)
	, isStartOfBlock_(false)
	  , questionNoIndex_(++AbstractQuestion::nQuestions_)
{
	if(enclosingCompoundStatement_ == 0){
		print_err(compiler_internal_error, " no enclosing CompoundStatement scope for question "
			, qscript_parser::line_no, __LINE__, __FILE__);
	}
}

#if 0
AbstractQuestion::AbstractQuestion(
	DataType l_type, int32_t l_no, string l_name, string l_text
	, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
	, QuestionAttributes  l_question_attributes
	)
	: AbstractStatement(l_type, l_no), questionName_(l_name)
	, questionText_(l_text), q_type(l_q_type)
	, no_mpn(l_no_mpn), dt(l_dt), input_data()
	, for_bounds_stack(0), loop_index_values(0)
	, isAnswered_(false), isModified_(false)
	, enclosingCompoundStatement_(0), activeVarInfo_(0)
	, dummyArrayQuestion_(0), currentResponse_()
	, question_attributes(l_question_attributes)
	  , maxCode_(0)
{
	//if(enclosingCompoundStatement_ == 0){
	//	print_err(compiler_internal_error, " no enclosing CompoundStatement scope for question "
	//		, qscript_parser::line_no, __LINE__, __FILE__  );
	//}
}
#endif /* 0 */


	//! this is only called in the compile time environment
AbstractQuestion::AbstractQuestion(
	DataType l_type, int32_t l_no
	, string l_name, vector<TextExpression*> text_expr_vec
	, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
	, CompoundStatement * l_enclosing_scope
	, vector<ActiveVariableInfo* > l_av_info
	, QuestionAttributes  l_question_attributes
	, const XtccSet & p_mutexCodeList
	)
	: AbstractStatement(l_type, l_no), questionName_(l_name)
	, textExprVec_(text_expr_vec)
	, questionDiskName_()
	, q_type(l_q_type)
	, no_mpn(l_no_mpn), dt(l_dt), input_data()
	, for_bounds_stack(0), loop_index_values(0)
	, isAnswered_(false), isModified_(false)
	, enclosingCompoundStatement_(l_enclosing_scope)
	, activeVarInfo_(l_av_info)
	, dummyArrayQuestion_(0), currentResponse_()
	, question_attributes(l_question_attributes)
	, mutexCodeList_(p_mutexCodeList)
	  , maxCode_(0)
	, isStartOfBlock_(false)
	  , questionNoIndex_(++AbstractQuestion::nQuestions_)
{
	if(enclosingCompoundStatement_ == 0){
		print_err(compiler_internal_error, " no enclosing CompoundStatement scope for question "
			, qscript_parser::line_no, __LINE__, __FILE__);
	}
}

#if 0
// this is only called from the runtime
AbstractQuestion::AbstractQuestion(
	DataType l_type, int32_t l_no, string l_name
	, string l_text
	, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
	, const vector<int32_t>& l_loop_index_values
	, DummyArrayQuestion * l_dummy_array
	, QuestionAttributes  l_question_attributes
	)
	: AbstractStatement(l_type, l_no), questionName_(l_name)
	, questionText_(l_text), q_type(l_q_type)
	, no_mpn(l_no_mpn), dt(l_dt), input_data()
	, for_bounds_stack(0)
	, loop_index_values(l_loop_index_values)
	, isAnswered_(false), isModified_(false)
	, enclosingCompoundStatement_(0) // this is only used in the compile time environment
	, activeVarInfo_(0)
	, dummyArrayQuestion_(l_dummy_array), currentResponse_()
	, question_attributes(l_question_attributes)
	  , maxCode_(0)
{
	//for(int32_t i = 0; i < l_loop_index_values.size(); ++i){
	//	cout << "l_loop_index_values " << i << ":" << l_loop_index_values[i] << endl;
	//}
}
#endif /* 0 */

#if 0
int32_t AbstractQuestion::GetMaxCode()
{
	if (maxCode_ == 0) {
		stringstream err_msg;
		err_msg << " maxCode_ == 0 should have been set: questionName_: "
			<< questionName_ << endl;
		print_err(compiler_internal_error, err_msg.str()
				, 0, __LINE__, __FILE__);
		exit(1);
	}
	return maxCode_;
}
#endif /* 0 */

#if 0
AbstractQuestion::~AbstractQuestion()
{
	for (int i=0; i<activeVarInfo_.size(); ++i) {
		delete activeVarInfo_[i];
		activeVarInfo_[i]=0;
	}
}
#endif /* 0 */

#if 0
void AbstractQuestion::GetQuestionsInBlock(
	vector<AbstractQuestion*> & question_list, AbstractStatement * stop_at)
{
	//std::cerr << "ENTER AbstractQuestion::GetQuestionsInBlock()" << std::endl;
	question_list.push_back(this);
	if(next_ && next_ != stop_at){
		next_->GetQuestionsInBlock(question_list, stop_at);
	}
	//std::cerr << "EXIT AbstractQuestion::GetQuestionsInBlock()" << std::endl;
}
#endif /* 0 */

#if 0
void AbstractQuestion::PrintUserNavigation(ostringstream & program_code)
{
	// hard coded for now
	program_code << "if(user_navigation == NAVIGATE_PREVIOUS){\n\
		AbstractQuestion * target_question = ComputePreviousQuestion("
		<< questionName_.c_str() << ");\n\
		if(target_question == 0)\n\
		goto label_eval_" << questionName_.c_str() << ";\n\
		else {\n\
		jumpToQuestion = target_question->questionName_;\n\
		if(target_question->type_ == QUESTION_ARR_TYPE){\n\
			jumpToIndex = ComputeJumpToIndex(target_question);\n\
		}\n\
		//if (data_entry_window==0) cout << \"target question: \" << jumpToQuestion;\n\
		//if (data_entry_window==0) cout << \"target question Index: \" << jumpToIndex;\n\
		back_jump = true;\n\
		user_navigation = NOT_SET;\n\
		goto start_of_questions;\n}\n}\n";
	program_code << "else if (user_navigation == NAVIGATE_NEXT){\n";
	program_code << "\tif (" << questionName_ << "->isAnswered_==false && " << questionName_ <<  "->question_attributes.isAllowBlank()==false ) {\n"
			<< "\t\tgoto label_eval_" << questionName_ << ";\n"
			<< "\t}\n";
	program_code << "	stopAtNextQuestion = true;\n\
		user_navigation = NOT_SET;\n\
		}\n";
	program_code << "else if (user_navigation == JUMP_TO_QUESTION){\n\
		DisplayActiveQuestions();\n\
		GetUserResponse(jumpToQuestion, jumpToIndex);\n\
		user_navigation = NOT_SET;\n\
		goto start_of_questions;\n\
		}\n";
	program_code << "else if (user_navigation == SAVE_DATA){\n";
	program_code <<	"\twrite_data_to_disk(question_list, jno, ser_no);\n";
	program_code << "\t\tif (data_entry_window) mvwprintw(data_entry_window,2,50, \"saved partial data\");\n else \tcout << \"saved partial data\\n\";\n";
	program_code << "\t\tif (" << questionName_ << "->isAnswered_==false) {\n"
			<< "\t\t\tgoto label_eval_" << questionName_ << ";\n"
			<< "\t\t}\n";
	program_code << "\t}";
	program_code << " else { " << endl
		<< "last_question_answered = " << questionName_ << ";\n"
		<< "}\n";
}
#endif /* 0 */

#if 0
void AbstractQuestion::PrintUserNavigationArrayQuestion(ostringstream & program_code)
{
	program_code << "if(user_navigation == NAVIGATE_PREVIOUS){\n\
		AbstractQuestion * target_question = ComputePreviousQuestion("
			<< questionName_.c_str()  << "_list.questionList["
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< "]"
			<< ");\n\
		if(target_question == 0)\n\
		goto label_eval_" << questionName_ << ";\n\
		else {\n\
		jumpToQuestion = target_question->questionName_;\n\
		if(target_question->type_ == QUESTION_ARR_TYPE){\n\
			jumpToIndex = ComputeJumpToIndex(target_question);\n\
		}\n\
		//if (data_entry_window==0) cout << \"target question: \" << jumpToQuestion;\n\
		//if (data_entry_window==0) cout << \"target question Index: \" << jumpToIndex;\n\
		back_jump = true;\n\
		user_navigation = NOT_SET;\n\
		goto start_of_questions;\n}\n}\n";
	program_code << "else if (user_navigation == NAVIGATE_NEXT){\n\
		stopAtNextQuestion = true;\n\
		user_navigation = NOT_SET;\n}\n";
	program_code << "else if (user_navigation == JUMP_TO_QUESTION){\n\
		DisplayActiveQuestions();\n\
		GetUserResponse(jumpToQuestion, jumpToIndex);\n\
		user_navigation = NOT_SET;\n\
		goto start_of_questions;\n\
		}\n";
	program_code << "else if (user_navigation == SAVE_DATA){\n";
	program_code << "\twrite_data_to_disk(question_list, jno, ser_no);\n";
	program_code << "\tcout << \"saved partial data\\n\";\n";
	program_code << "\t\tif (data_entry_window) mvwprintw(data_entry_window,2,50, \"saved partial data\");\n else \tcout << \"saved partial data\\n\";\n";
	program_code << "\t\tif (" << questionName_ << "_list.questionList["
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< "]->isAnswered_==false) {\n"
			<< "\t\tcout << \"question has not been answered ... jumping back\\n\";\n"
			<< "\t\t\tgoto label_eval_" << questionName_ << ";\n"
			<< "\t\t}\n";
	program_code << "}\n";
	program_code << " else { " << endl
		<< "last_question_answered = " << questionName_ << "_list.questionList["
		//<< consolidated_for_loop_index_stack[consolidated_for_loop_index_stack.size()-1]
		<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
		<< "]" << ";\n"
		<< "}\n";
}
#endif /* 0 */

void AbstractQuestion::PrintEvalAndNavigateCode(ostringstream & program_code)
{
	/*
	program_code << "if ( ("
		<< questionName_ << "->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||" << endl
		<< "(" << questionName_ << "->isAnswered_ && !" << questionName_
		<< "->VerifyQuestionIntegrity())"<< "||" << endl
		<< "stopAtNextQuestion ||" << endl
		<< "jumpToQuestion == \"" << questionName_.c_str() << "\" || " << endl
		<< "((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag) "
		<< "  && !(" << questionName_ << "->question_attributes.isAllowBlank()) && "
		<< questionName_ << "->isAnswered_ == false "
		<< ")"
	        << ") {" << endl;
	*/
	program_code << "/*  " <<  __PRETTY_FUNCTION__<< "*/\n" << endl;

	program_code << "if ( /* nxd */("
		<< questionName_ << "->isAnswered_ == false && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||" << endl
		<< "(" << questionName_ << "->isAnswered_ && !" << questionName_
		<< "->VerifyQuestionIntegrity())"<< "||" << endl
		//<< "stopAtNextQuestion ||" << endl
		//<< "jumpToQuestion == \"" << questionName_.c_str() << "\" || " << endl
		<< "( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited.size() == 0) || (p_navigation_mode == NAVIGATE_NEXT && " << questionName_ << "->questionNoIndex_ >  last_question_visited[last_question_visited.size()-1]-> questionNoIndex_ )) ||" << endl
		<<  "( p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractRuntimeQuestion*>(" << questionName_ << ") == p_jump_to_index)) ||"  << endl
		<< "((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag) "
		<< "  && !(" << questionName_ << "->question_attributes.isAllowBlank()) && "
		<< questionName_ << "->isAnswered_ == false "
		<< ")"
	        << ") {" << endl;
	//program_code << "if(stopAtNextQuestion && " << questionName_ << "->question_attributes.hidden_ == false"
	//	<< " ) {\n\tstopAtNextQuestion = false; "
	//	<< " fprintf (qscript_stdout, \" at question:  " << questionName_
	//	<< " disarming stopAtNextQuestion = false \\n\");\n"
	//	<< "\n}\n";
	//program_code << "if ("
	//	<< "jumpToQuestion == \"" << questionName_ << "\") { " << endl
	//	<< "jumpToQuestion = \"\";\n"
	//	<< "}\n";
	program_code << "label_eval_" << questionName_.c_str() << ":\n"
		<< "\t\t"
		//<< "if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == "
		//<< questionName_ << ") {\n"
		//<< " stopAtNextQuestion = true;\n"
		//<< " fprintf (qscript_stdout, \" at question:  " << questionName_
		//<< " arming stopAtNextQuestion = true \\n\");\n"
		//<< "}" << " else " << endl
		<< "if (" << questionName_ << "->question_attributes.hidden_==false) {\n"
		<< "\t// " << questionName_
		<< "->eval(question_window, stub_list_window, data_entry_window);\n"
		// moved down - near return statement
		//<< "\tlast_question_visited = " << questionName_ << ";"
		<< endl;
	if (program_options_ns::emscripten_flag) {
		program_code
			<< "\t//fprintf(qscript_stdout, \"last_question_visited: " << questionName_ << "\\n\");\n";
	} else {
		program_code
			<< "\tfprintf(qscript_stdout, \"last_question_visited: " << questionName_ << "\\n\");\n";
	}

	if (qscript_parser::page_nest_lev > 0) {
		program_code << "/* page_nest_lev == " << qscript_parser::page_nest_lev
			<< qscript_parser::page_nest_lev << " | INSIDE A PAGE */" << endl;
		program_code
			//<< "\treturn " << questionName_ << ";" << endl
			<< "vec_page_" << qscript_parser::globalActivePageName_ << "_ret_val.push_back("
			<< questionName_ << ");" << endl
			<< "\t}\n";
		if (qscript_parser::flag_first_question_in_page) {
			program_code << "last_question_visited.clear();" << std::endl;
			qscript_parser::flag_first_question_in_page = false;
		}
	} else {
		program_code << "/* page_nest_lev == " << qscript_parser::page_nest_lev
			<< qscript_parser::page_nest_lev << " | NOT INSIDE A PAGE */" << endl;
		program_code
			<< "\t vector<AbstractRuntimeQuestion*> ret_vec;" << endl
			<< "\t ret_vec.push_back(" << questionName_ << ");" << endl
			<< "\t last_question_visited.clear();" << endl
			<< "\t last_question_visited.push_back(" << questionName_ << ");" << endl
			<< "\t EvalReturnValue ev_ret_val; " << endl
			<< "\t ev_ret_val.qVec_ = ret_vec; " << endl 
			<< "\t ev_ret_val.errMessageVec_ = error_messages_vec; " << endl 
			<< "\t //return ret_vec;" << endl
			<< "\t return ev_ret_val;" << endl
			<< "\t}\n";
	}

	// NxD: 11-Aug-2013 original place of return statement
	//program_code
	//	<< "\treturn " << questionName_ << ";" << endl
	//	<< "\t}\n";
	// PrintUserNavigation(program_code);
	program_code <<  "}\n";
}

void AbstractQuestion::Generate_ComputeFlatFileMap(StatementCompiledCode & code)
{

	if (for_bounds_stack.size() == 0) {
		code.program_code << "\tAsciiFlatFileQuestionDiskMap * " << qscript_parser::temp_name_generator.GetNewName()
			<<  " = new AsciiFlatFileQuestionDiskMap(" << questionName_ << ", current_map_pos);\n";
	}  else {
		string consolidated_for_loop_index = PrintConsolidatedForLoopIndex(for_bounds_stack);
		code.program_code << "\tAsciiFlatFileQuestionDiskMap * " << qscript_parser::temp_name_generator.GetNewName()
			<<  " = new AsciiFlatFileQuestionDiskMap(" << questionName_
			<< "_list.questionList[" << consolidated_for_loop_index << "]"
			<< ", current_map_pos);\n";
	}
	code.program_code << "\tcurrent_map_pos += " << qscript_parser::temp_name_generator.GetCurrentName() << "->GetTotalLength();\n";
	code.program_code << "\tascii_flatfile_question_disk_map.push_back(" << qscript_parser::temp_name_generator.GetCurrentName() << ");\n";


	code.program_code << "\tif (write_xtcc_data_file_flag) {\n";
	if (for_bounds_stack.size() == 0) {
		code.program_code << "\t XtccDataFileDiskMap * " << qscript_parser::temp_name_generator.GetNewName()
			<<  " = new XtccDataFileDiskMap(" << questionName_ << ", current_xtcc_map_pos);\n";
	}  else {
		string consolidated_for_loop_index = PrintConsolidatedForLoopIndex(for_bounds_stack);
		code.program_code << "\t XtccDataFileDiskMap * " << qscript_parser::temp_name_generator.GetNewName()
			<<  " = new XtccDataFileDiskMap(" << questionName_
			<< "_list.questionList[" << consolidated_for_loop_index << "]"
			<< ", current_xtcc_map_pos);\n";
	}
	code.program_code << "\t current_xtcc_map_pos += " << qscript_parser::temp_name_generator.GetCurrentName() << "->GetTotalLength();\n";
	code.program_code << "\t xtcc_question_disk_map.push_back(" << qscript_parser::temp_name_generator.GetCurrentName() << ");\n";
	code.program_code << "\t}\n";


	code.program_code << "\tif (write_qtm_data_file_flag) {\n";
	if (for_bounds_stack.size() == 0) {

		code.program_code << "\t\tqtm_data_file_ns::QtmDataDiskMap * " << qscript_parser::temp_name_generator.GetNewName()
			<<  " = new qtm_data_file_ns::QtmDataDiskMap(" << questionName_ << ", qtm_data_file, base_text_vec.back()"
			<< ");\n";
	}  else {
		string consolidated_for_loop_index = PrintConsolidatedForLoopIndex(for_bounds_stack);
		code.program_code << "\tqtm_data_file_ns::QtmDataDiskMap * " << qscript_parser::temp_name_generator.GetNewName()
			<<  " = new qtm_data_file_ns::QtmDataDiskMap(" << questionName_
			<< "_list.questionList[" << consolidated_for_loop_index << "]"
			<< ", qtm_data_file, base_text_vec.back());\n";
	}
	code.program_code << "\t qtm_datafile_question_disk_map.push_back(" << qscript_parser::temp_name_generator.GetCurrentName() << ");\n";
	code.program_code << "\t}\n";

	if (next_) {
		next_->Generate_ComputeFlatFileMap(code);
	}
}

const char *  AbstractQuestion::CurrentResponseToCharString()
{
	stringstream s;
	for(set<int32_t>::iterator iter = input_data.begin();
		iter != input_data.end(); ++iter){
		s << *iter << ",";
	}
	currentResponse_ = s.str();
	return currentResponse_.c_str();
}

void AbstractQuestion::PrintQuestionArrayInitialisation(StatementCompiledCode & code)
{
	for(int32_t i = 0; i< for_bounds_stack.size(); ++i){
		code.quest_defns << "for(int32_t ";
		BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(for_bounds_stack[i]);
		if(bin_expr_ptr){
			//AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
			AbstractExpression * lhs = bin_expr_ptr->leftOperand_;
			ExpressionCompiledCode expr_code1;
			lhs->PrintExpressionCode(expr_code1);
			code.quest_defns << expr_code1.code_bef_expr.str() << expr_code1.code_expr.str();
			code.quest_defns << " = 0;";
			ExpressionCompiledCode expr_code2;
			for_bounds_stack[i]->PrintExpressionCode(expr_code2);
			code.quest_defns << expr_code2.code_bef_expr.str() << expr_code2.code_expr.str();
			code.quest_defns << "; ++";
			ExpressionCompiledCode expr_code3;
			lhs->PrintExpressionCode(expr_code3);
			code.quest_defns << expr_code3.code_bef_expr.str() << expr_code3.code_expr.str();
			code.quest_defns <<	"){" << endl;
			if(i == 0){
				code.quest_defns << "vector<int32_t> stack_of_loop_indices;\n";
					//<< "(" <<  for_bounds_stack.size() << ");\n";
			}
			code.quest_defns << "stack_of_loop_indices.push_back(";
			//lhs->PrintExpressionCode(quest_defns, quest_defns); // note this is already stored in expr_code3
			code.quest_defns << expr_code3.code_bef_expr.str() << expr_code3.code_expr.str();
			code.quest_defns << ");\n";
		} else {
			ExpressionCompiledCode expr_code;
			for_bounds_stack[i]->PrintExpressionCode(expr_code);
			code.quest_defns << expr_code.code_bef_expr.str() << expr_code.code_expr.str();
			print_err(compiler_sem_err
				, "for loop index condition is not a binary expression"
				, 0, __LINE__, __FILE__);
		}
	}
}

#if 0
// re_arranged_buffer will contain the data like this: valid_data invalid_data
bool AbstractQuestion::VerifyData(
	string & err_mesg, string & re_arranged_buffer
	, int32_t & pos_1st_invalid_data)
{
	bool invalid_code=false, has_invalid_data_flag = false;
	stringstream valid_data, invalid_data;
	for(uint32_t i = 0; i < data.size(); ++i){
		//cout << "Testing data exists: " << data[i] << endl;
		invalid_code = !IsValid(data[i]);
		if(invalid_code == true){
			if(!has_invalid_data_flag)
				has_invalid_data_flag = true;
			invalid_data << data[i] << " ";
		} else {
			valid_data << data[i] << " ";
		}
	}

	if (data.size() == 0 && question_attributes.isAllowBlank() == false) {
		err_mesg = " question cannot be blank";
		invalid_code = true;
		goto end;
	}

	if(has_invalid_data_flag) {
		err_mesg = "Input contained some invalid data.. " + invalid_data.str() +  " Re-enter Data\n";
		pos_1st_invalid_data = valid_data.str().length(); // it already has a space appended to it
		re_arranged_buffer = valid_data.str() + invalid_data.str();
		invalid_code = true;
		goto end;
	}
	if(q_type == spn && data.size()>1) {
		err_mesg = "Single coded Question - please enter only 1 code:";
		invalid_code = true;
		data.clear();
	} else if (q_type == mpn) {
		cout << "reached here: " << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
		if (data.size() > no_mpn){
			err_mesg = "Multi coded Question, no values exceed max allowed:  ";
			invalid_code = true;
			cerr << "should I clear this? - the DE operator has done hard work entering this data"
				<< __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
			data.clear();
		}
		int count_mutex_data = 0;
		for(int i=0; i<data.size(); ++i) {
			if (mutexCodeList_.exists(data[i])){
				cout << "mutexCodeList_ contains: " << data[i];
				++count_mutex_data;
			}
		}
		if (data.size()>1 && count_mutex_data >= 1) {
			err_mesg = "Mutex code entered with other codes";
			invalid_code = true;
			cerr << "should I clear this? - the DE operator has done hard work entering this data"
				<< __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
			data.clear();
		}
	} else {
		invalid_code = false;
	}
end:
	// cout << __PRETTY_FUNCTION__ << " returned invalid_code: |" << invalid_code
	// 	<< "|" << endl;
	return invalid_code;
}
#endif /* 0 */

#if 0
user_response::UserResponseType AbstractQuestion::GetDataFromUser(WINDOW * data_entry_window)
{
	// cout << __PRETTY_FUNCTION__ << ", " << __LINE__ << ", " << __FILE__ << endl;

	string err_mesg, re_arranged_buffer;
	int32_t pos_1st_invalid_data;
	if (data_entry_window == 0) {
		bool invalid_code = false;
		string prompt = "Enter Data:";
		do {
ask_again:
			user_response::UserResponseType user_resp = read_data(prompt.c_str());
			bool valid_response = AbstractQuestion::VerifyResponse(user_resp);
			if (!valid_response) {
				goto ask_again;
			}
			// NxD: 16-Feb-2011
			// handle User Data response here - blank as well as valid data
			if (user_resp == user_response::UserClearedData) {
				input_data.erase(input_data.begin(), input_data.end());
				isAnswered_ = false;
				goto ask_again;
			}
			invalid_code = VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data);
			prompt = err_mesg;

			if(invalid_code == false){
				input_data.erase(input_data.begin(), input_data.end());
				for(uint32_t i = 0; i < data.size(); ++i){
					input_data.insert(data[i]);
					//cout 	<< "storing: " << data[i]
					//	<< " into input_data" << endl;
				}
				isAnswered_ = true;
			}
		} while (invalid_code == true);
		stringstream mesg;
		mesg << "is it necessary to clear data here - we are doing it at top of read_data";
		LOG_MAINTAINER_MESSAGE(mesg.str());
		data.clear();
		return user_response::UserEnteredData;
	} else {
		bool invalid_code = false;
		stringstream current_data_str;
		for (set<int32_t>::iterator inp_data_iter = input_data.begin();
				inp_data_iter != input_data.end(); ++inp_data_iter) {
			current_data_str << *inp_data_iter << " ";
		}
		re_arranged_buffer = current_data_str.str();
		pos_1st_invalid_data = re_arranged_buffer.length() - 1;
		do {
label_ask_again:
			user_response::UserResponseType user_resp
				= read_data_from_window(
						data_entry_window, err_mesg.c_str()
					      //, (!invalid_code), re_arranged_buffer
					      , false, re_arranged_buffer
					      , pos_1st_invalid_data);
			// if (user_resp == user_response::UserEnteredNavigation) {
			// 	return user_resp;
			// }
			bool valid_input = AbstractQuestion::VerifyResponse(user_resp);
			if (isAnswered_ == false && user_navigation == NAVIGATE_PREVIOUS
					&& user_resp == user_response::UserEnteredNavigation) {
				// allow this behaviour - they can go back to the
				// previous question without answering anything -
				// no harm done
				return user_resp;
			} else if (isAnswered_ == false && user_navigation == NAVIGATE_NEXT
					&& user_resp == user_response::UserEnteredNavigation
					&& question_attributes.isAllowBlank() == false) {
				err_mesg = "cannot navigate to next question unless this is answered";
				mvwprintw(data_entry_window, 3, 1, err_mesg.c_str());
				goto label_ask_again;
			}
			if (!valid_input) {
				goto label_ask_again;
			}

			invalid_code = VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data);


			if (invalid_code == false) {
				input_data.erase(input_data.begin(), input_data.end());
				for(uint32_t i = 0; i < data.size(); ++i){
					input_data.insert(data[i]);
					//cout << "storing: " << data[i]
					//	<< " into input_data" << endl;
				}
				isAnswered_ = true;
			}
		} while (invalid_code == true);
		stringstream mesg;
		mesg << "is it necessary to clear data here - we are doing it at top of read_data";
		LOG_MAINTAINER_MESSAGE(mesg.str());
		data.clear();
		return user_response::UserEnteredData;
	}
}
#endif /* 0 */

//void AbstractQuestion::PrintArrayDeclarations(ostringstream & quest_defns)
void AbstractQuestion::PrintArrayDeclarations(StatementCompiledCode & code)
{
	string temp_array_bounds_name = "list_" + questionName_ + "_array_bounds";
	code.quest_defns << "vector<int32_t> " << temp_array_bounds_name
		<< ";" << endl;
#if 0
	static bool first_time = true;
	if (!first_time) {
		code.quest_defns_constructor << "," ;
	} else {
		code.quest_defns_constructor << ": ";
		first_time = false;
	}
#endif /* 0 */
	code.quest_defns_constructor << "," ;
	code.quest_defns_constructor << temp_array_bounds_name
		<< "(" << for_bounds_stack.size() << ")";
	for(int32_t i = 0; i< for_bounds_stack.size(); ++i){
		ostringstream array_bounds;
		BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(for_bounds_stack[i]);
		if (bin_expr_ptr) {
			AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
			ExpressionCompiledCode expr_code;
			rhs->PrintExpressionCode(expr_code);
			array_bounds << expr_code.code_bef_expr.str() << expr_code.code_expr.str();
			//int32_t bounds = atoi(array_bounds.str().c_str());
			//quest_defns << temp_array_bounds_name
			//	<< "[" << i << "] = " << array_bounds.str() << ";\n";
			code.quest_defns_init_code << temp_array_bounds_name
				<< "[" << i << "] = " << array_bounds.str() << ";\n";
			array_bounds.clear();
		} else {
			print_err(compiler_sem_err
				, "for loop index condition is not a binary expression"
				, 0, __LINE__, __FILE__);
		}
	}
	//----------------------------------------
	//code.quest_defns << "ArrayQuestion " << questionName_ << "_list("
	//	<< temp_array_bounds_name <<");" << endl;
	//code.quest_defns << "DummyArrayQuestion* dum_" << questionName_
	//	<< "= new DummyArrayQuestion(\""  << questionName_ << "\","
	//	<< temp_array_bounds_name <<");" << endl;
	//code.quest_defns << "question_list.push_back( dum_" << questionName_ << ");"
	//	<< endl;
	code.quest_defns << "ArrayQuestion " << questionName_ << "_list;"
		<< endl;
	code.quest_defns_init_code << questionName_ << "_list.SetArrayBounds("
		<< temp_array_bounds_name <<");" << endl;
	code.quest_defns << "DummyArrayQuestion* dum_" << questionName_
		<< ";" << endl;
	code.quest_defns_init_code << "dum_" << questionName_
		<< "= new DummyArrayQuestion(\""  << questionName_ << "\","
		<< temp_array_bounds_name <<");" << endl;
	code.quest_defns_init_code << "question_list.push_back( dum_" << questionName_ << ");"
		<< endl;
}

//! this is only called in the compile time environment
RangeQuestion::RangeQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, vector<TextExpression*> text_expr_vec, QuestionType l_q_type, int32_t l_no_mpn
	, DataType l_dt, XtccSet& l_r_data
	, vector<AbstractExpression*> & l_for_bounds_stack
	, CompoundStatement * l_enclosing_scope
	, vector<ActiveVariableInfo* > l_av_info
	, QuestionAttributes  l_question_attributes
	, const XtccSet & p_mutexCodeList
	)
	: AbstractQuestion(this_stmt_type, line_number, l_name, text_expr_vec
			   , l_q_type, l_no_mpn, l_dt , l_for_bounds_stack
			   , l_enclosing_scope, l_av_info, l_question_attributes
			   , p_mutexCodeList)
			, r_data(new XtccSet(l_r_data)), displayData_()
{
	maxCode_ = r_data->GetMax();
}

#if 0

	//! this is only called in the runtime environment
RangeQuestion::RangeQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, string l_q_text, QuestionType l_q_type, int32_t l_no_mpn
	, DataType l_dt , XtccSet& l_r_data
	, QuestionAttributes  l_question_attributes
	)
	: AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text
			   , l_q_type, l_no_mpn, l_dt, l_question_attributes)
	, r_data(new XtccSet(l_r_data)), displayData_()
{
	maxCode_ = r_data->GetMax();
}
#endif /* 0 */

	//! this is only called in the compile time environment
RangeQuestion::RangeQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, vector<TextExpression*> text_expr_vec, QuestionType l_q_type, int32_t l_no_mpn
	, DataType l_dt , XtccSet& l_r_data
	, CompoundStatement * l_enclosing_scope
	, vector<ActiveVariableInfo* > l_av_info
	, QuestionAttributes  l_question_attributes
	, const XtccSet & p_mutexCodeList
	)
	: AbstractQuestion(this_stmt_type, line_number, l_name, text_expr_vec
			   , l_q_type, l_no_mpn, l_dt
			   , l_enclosing_scope, l_av_info, l_question_attributes
			   , p_mutexCodeList
			   )
	, r_data(new XtccSet(l_r_data)), displayData_()
{
	maxCode_ = r_data->GetMax();
}

#if 0
	//! this is only called from the runtime environment
RangeQuestion::RangeQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, string l_q_text, QuestionType l_q_type
	, int32_t l_no_mpn, DataType l_dt,	XtccSet& l_r_data
	, const vector<int32_t> & l_loop_index_values
	, DummyArrayQuestion * l_dummy_array
	, QuestionAttributes  l_question_attributes
	):
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt, l_loop_index_values, l_dummy_array
		, l_question_attributes
		)
	, r_data(new XtccSet(l_r_data)), displayData_()
{
	maxCode_ = r_data->GetMax();
}
#endif /* 0 */

#if 0
bool RangeQuestion::IsValid(int32_t value)
{
	return (r_data->exists(value))? true: false;
}
#endif /* 0 */

void RangeQuestion::eval(/*qs_ncurses::*/WINDOW * question_window
			 , /*qs_ncurses::*/WINDOW* stub_list_window
			 , /*qs_ncurses::*/WINDOW* data_entry_window)
{ }

#if 0
//void RangeQuestion::eval()
void RangeQuestion::eval(/*qs_ncurses::*/WINDOW * question_window
			 , /*qs_ncurses::*/WINDOW* stub_list_window
			 , /*qs_ncurses::*/WINDOW* data_entry_window)
{
	if(displayData_.begin() == displayData_.end()){
		for(	set<int32_t>::iterator it = r_data->indiv.begin();
				it != r_data->indiv.end(); ++it){
			//displayData_.insert(*it);
			displayData_.push_back(display_data::DisplayDataUnit(*it));
		}
		for(int32_t i = 0; i < r_data->range.size(); ++i){
			/*
			for(int32_t j = r_data->range[i].first; j <= r_data->range[i].second
					;++j){
				displayData_.insert(j);
			}
			*/
			displayData_.push_back(display_data::DisplayDataUnit(r_data->range[i].first, r_data->range[i].second));
		}
		std::sort(displayData_.begin(), displayData_.end(), display_data::DisplayDataUnitOrder());
	}
	if(question_window ==0 || stub_list_window  == 0 || data_entry_window  == 0 ){
		cout << questionName_ << ".";
		if(loop_index_values.size()>0){
			for(uint32_t i=0; i<loop_index_values.size(); ++i){
				cout << loop_index_values[i]+1 << ".";
			}
		}
		cout << questionText_ << endl << endl;
		//for(	set<int32_t>::iterator it = displayData_.begin();
		//		it != displayData_.end(); ++it)
		for(	vector<display_data::DisplayDataUnit>::iterator it = displayData_.begin();
				it != displayData_.end(); ++it)
		{
			//cout << *it << endl;
			if ( (*it).displayDataType_ == display_data::single_element) {
				cout << (*it).startOfRangeOrSingle_ << ", ";
			} else if ( (*it).displayDataType_ == display_data::range_element) {
				cout << (*it).startOfRangeOrSingle_ << " - " << (*it).endOfRange_ << endl;
			}
		}

		if(input_data.begin() != input_data.end()){
			cout << "Current data values: ";

			for(set<int32_t>::iterator iter = input_data.begin();
				iter != input_data.end(); ++iter){
				cout << *iter << " ";
			}
			cout << endl;
		}

		//AbstractQuestion::GetDataFromUser(data_entry_window);
	} else {
		wclear(question_window);
		box(question_window, 0, 0);
		wclear(stub_list_window);
		box(stub_list_window, 0, 0);
		wclear(data_entry_window);
		box(data_entry_window, 0, 0);
		mvwprintw(question_window,1, 1, "%s.", questionName_.c_str());
		int len_qno = questionName_.length()+2;
		if(loop_index_values.size()>0){
			for(uint32_t i=0; i<loop_index_values.size(); ++i){
				//cout << loop_index_values[i]+1 << ".";
				mvwprintw(question_window, 1, len_qno, "%d.", loop_index_values[i]+1);
				if (loop_index_values[i]+1<10) {
					len_qno += 1;
				} else if (loop_index_values[i]+1<100) {
					len_qno += 2;
				} else if (loop_index_values[i]+1<1000) {
					len_qno += 3;
				} else if (loop_index_values[i]+1<10000) {
					len_qno += 4;
				}
				len_qno += 1; // for the "."
			}
		}
		mvwprintw(question_window, 1, len_qno+1, " %s", questionText_.c_str() );
		//wrefresh(question_window);
		update_panels();
		doupdate();

		int32_t maxWinX, maxWinY;
		getmaxyx(data_entry_window, maxWinY, maxWinX);
		int32_t currXpos = 1, currYpos = 1;
#if 0
		for(	set<int32_t>::iterator it = displayData_.begin();
				it != displayData_.end(); ++it){
			stringstream s;
			s << *it;
			int32_t len = s.str().length();
			set<int32_t>::iterator found= input_data.find(*it);
			if(found != input_data.end()){
				// is an input value
				//YELLOW
					wattroff(stub_list_window, COLOR_PAIR(2));
					wattron(stub_list_window, COLOR_PAIR(4));
					mvwprintw(stub_list_window, currYpos, currXpos, "%s ", s.str().c_str());
					wattroff(stub_list_window, COLOR_PAIR(4));
					wattron(stub_list_window, COLOR_PAIR(2));
			} else {
				mvwprintw(stub_list_window, currYpos, currXpos, "%s ", s.str().c_str());
			}
			if(currXpos+len +1 /* 1 for the trailing space below */ >= maxWinX){
				currXpos = 1, ++currYpos;
			} else {
				currXpos+= len + 1;
			}
		}
#endif /* 0 */
		for(	vector<display_data::DisplayDataUnit>::iterator it = displayData_.begin();
				it != displayData_.end(); ++it)
		{
			//cout << *it << endl;
			stringstream s;

			if ( (*it).displayDataType_ == display_data::single_element) {
				s << (*it).startOfRangeOrSingle_ << ",";
			} else if ( (*it).displayDataType_ == display_data::range_element) {
				s << (*it).startOfRangeOrSingle_ << " - " << (*it).endOfRange_ << endl;
			}
			if (currXpos + s.str().length() > maxWinX) {
				currXpos =1, ++currYpos;
			}
			mvwprintw(stub_list_window, currYpos, currXpos, "%s", s.str().c_str());
			currXpos += s.str().length() + 1;
		}

		//wrefresh(stub_list_window);
		update_panels();
		doupdate();
		//AbstractQuestion::GetDataFromUser(data_entry_window);
	}

	user_response::UserResponseType user_resp = AbstractQuestion::GetDataFromUser(data_entry_window);

/*
get_data_again:
	user_response::UserResponseType user_resp = AbstractQuestion::GetDataFromUser(data_entry_window);
	stringstream mesg; mesg << "user_resp: " << user_resp;
	cout << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
		<< mesg.str() << endl;
	if (user_resp == user_response::UserClearedData && question_attributes.isAllowBlank()) {
		// valid response if blanks are allowed but dont do isAnswered_ = true
		// because otherwise when visiting the questionnaire it will skip this
		// question and data entry will have an off by 1 error everytime they
		// are reviewing this question - since blank is a valid answer
	} else if (user_resp == user_response::UserEnteredData) {
	} else if (user_resp == user_response::UserEnteredNavigation
			&& user_navigation == NAVIGATE_PREVIOUS) {
	} else {
		goto get_data_again;
	}
	*/

}
#endif /* 0 */

void RangeQuestion::WriteDataToDisk(ofstream& data_file)
{ }

#if 0
void RangeQuestion::WriteDataToDisk(ofstream& data_file)
{
	if(loop_index_values.size()>0){
		data_file << questionName_;
		for(int32_t i = 0; i< loop_index_values.size(); ++i){
			data_file << "$" << loop_index_values[i];
		}
	} else {
		data_file << questionName_;
	}
	data_file << ":";
	if (isAnswered_) {
		for( set<int32_t>::iterator iter = input_data.begin();
				iter != input_data.end(); ++iter){
			data_file << *iter << " ";
		}
	}
	data_file << endl;
	stringstream mesg;

	//mesg << "I think this is the wrong place to clear - should be done at the end of main while loop in generated code, when user loads a new serial number"
	//	<< " right now if the user presses 's' 2ice - we lose data" << endl;
	//LOG_MAINTAINER_MESSAGE(mesg.str());
	//input_data.clear();
}
#endif /* 0 */

#if 0
bool NamedStubQuestion::IsValid(int32_t value)
{
	//vector<stub_pair> & vec= *stub_ptr;
	vector<stub_pair> & vec= (nr_ptr->stubs);
	for (uint32_t j = 0; j < vec.size(); ++j) {
		if (vec[j].code == value && vec[j].mask) {
			return true;
		}
	}
	return false;
}
#endif /* 0 */

void NamedStubQuestion::eval(/*qs_ncurses::*/WINDOW * question_window
			     , /*qs_ncurses::*/WINDOW* stub_list_window
			     , /*qs_ncurses::*/WINDOW* data_entry_window)
{ }

#if 0
//void NamedStubQuestion::eval()
void NamedStubQuestion::eval(/*qs_ncurses::*/WINDOW * question_window
			     , /*qs_ncurses::*/WINDOW* stub_list_window
			     , /*qs_ncurses::*/WINDOW* data_entry_window)
{
	if(question_window  == 0 || stub_list_window  == 0 || data_entry_window  == 0 ){
		cout << questionName_ << ".";
		if(loop_index_values.size()>0){
			for(uint32_t i=0; i<loop_index_values.size(); ++i){
				cout << loop_index_values[i]+1 << ".";
			}
		}
		cout << questionText_ << endl << endl;

		//cout << questionName_ << "." << questionText_ << endl << endl;
		//vector<stub_pair> vec= *stub_ptr;
		vector<stub_pair> & vec= (nr_ptr->stubs);
		for(uint32_t i = 0; i< vec.size(); ++i){
			if( vec[i].mask)
				cout << vec[i].stub_text << ": " << vec[i].code << endl;
		}

		if(input_data.begin() != input_data.end()){
			cout << "Current data values: ";

			for(set<int32_t>::iterator iter = input_data.begin();
				iter != input_data.end(); ++iter){
				cout << *iter << " ";
			}
			cout << endl;
		}

		//user_response::UserResponseType user_resp = AbstractQuestion::GetDataFromUser(data_entry_window);

	} else {
		wclear(question_window);
		box(question_window, 0, 0);
		wclear(stub_list_window);
		box(stub_list_window, 0, 0);
		wclear(data_entry_window);
		box(data_entry_window, 0, 0);
		mvwprintw(question_window,1,1, "%s. %s", questionName_.c_str(), questionText_.c_str() );
		//wrefresh(question_window);
		update_panels();
		doupdate();
		//int32_t maxWinX, maxWinY;
		//getmaxyx(data_entry_window, maxWinY, maxWinX);
		int32_t currXpos = 1, currYpos = 1;

		//vector<stub_pair> & vec= *stub_ptr;
		vector<stub_pair> & vec= (nr_ptr->stubs);
		for(uint32_t i = 0; i< vec.size(); ++i){
			if( vec[i].mask) {
				//cout << vec[i].stub_text << ": " << vec[i].code << endl;
				//mvwprintw(stub_list_window, currYpos, currXpos, "%s: %d ", vec[i].stub_text.c_str(), vec[i].code);
				mvwprintw(stub_list_window, currYpos, currXpos, "%s: ", vec[i].stub_text.c_str());
				set<int32_t>::iterator found= input_data.find(vec[i].code);
				if (found != input_data.end() ){
					wattroff(stub_list_window, COLOR_PAIR(2));
					wattron(stub_list_window, COLOR_PAIR(4));
					mvwprintw(stub_list_window, currYpos, currXpos + vec[i].stub_text.length() + 3, "%d ", vec[i].code);
					wattroff(stub_list_window, COLOR_PAIR(4));
					wattron(stub_list_window, COLOR_PAIR(2));
				} else {
					mvwprintw(stub_list_window, currYpos, currXpos + vec[i].stub_text.length() + 3, "%d ", vec[i].code);
				}
				++currYpos;
			}
		}

		//wrefresh(stub_list_window);
		update_panels();
		doupdate();
		// AbstractQuestion::GetDataFromUser(data_entry_window);
	}
	user_response::UserResponseType user_resp = AbstractQuestion::GetDataFromUser(data_entry_window);

	/*
get_data_again:
	user_response::UserResponseType user_resp = AbstractQuestion::GetDataFromUser(data_entry_window);
	stringstream mesg; mesg << "user_resp: " << user_resp;
	cout << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
		<< mesg.str() << endl;
	if (user_resp == user_response::UserClearedData && question_attributes.isAllowBlank()) {
		// valid response if blanks are allowed but dont do isAnswered_ = true
		// because otherwise when visiting the questionnaire it will skip this
		// question and data entry will have an off by 1 error everytime they
		// are reviewing this question - since blank is a valid answer
	} else if (user_resp == user_response::UserEnteredData) {
	} else if (user_resp == user_response::UserEnteredNavigation
		&& user_navigation == NAVIGATE_PREVIOUS) {
	} else {
		goto get_data_again;
	}
	*/

}
#endif /* 0 */


string PrintQuestionTitleCode (vector <TextExpression*> & textExprVec)
{
	stringstream quest_decl;
	quest_decl << "/* Enter: " << __PRETTY_FUNCTION__ << "*/" << endl;
	for (int i=0; i < textExprVec.size(); ++i) {
		if (textExprVec[i]->teType_ == TextExpression::simple_text_type) {
			quest_decl << "text_expr_vec.push_back(new TextExpression(string(\""
				<< textExprVec[i]->text_
				<< "\")));\n";
		} else if (textExprVec[i]->teType_ == TextExpression::question_type) {
			if (textExprVec[i]->questionIndexExpr_ ) {
				ExpressionCompiledCode expr_code;
				textExprVec[i]->questionIndexExpr_->PrintExpressionCode(expr_code);
				quest_decl << "text_expr_vec.push_back( new TextExpression("
						<< textExprVec[i]->pipedQuestion_->questionName_
						<< ", "
						<< expr_code.code_expr.str()
						<< ") ); /*  -NxD- */\n";
			} else {
				quest_decl << "text_expr_vec.push_back( new TextExpression("
						<< textExprVec[i]->pipedQuestion_->questionName_
						<< ") ); /*  -NxD- */\n";
			}
		} else {
			ExpressionCompiledCode expr_code;
			textExprVec[i]->nameExpr_->PrintExpressionCode(expr_code);
			quest_decl << "text_expr_vec.push_back(new TextExpression("
				<< expr_code.code_expr.str()
				<< "));\n";
		}
	}
	quest_decl << "/* Exit: " << __PRETTY_FUNCTION__ << "*/" << endl;
	return quest_decl.str();
}


void RangeQuestion::GenerateCodeSingleQuestion(StatementCompiledCode & code, bool array_mode)
{
	//AbstractQuestion::PrintSetupBackJump(quest_defns, program_code);

	static int32_t xtcc_set_counter = 0;
	const int32_t BUF_SIZE = 100;
	char xtcc_set_name[BUF_SIZE];
	sprintf(xtcc_set_name, "xs_%d", xtcc_set_counter++);
	code.quest_defns  << "XtccSet " << xtcc_set_name << ";" << endl;
	/*
	for(	set<int32_t>::iterator it = r_data->indiv.begin();
			it != r_data->indiv.end(); ++it){
		code.quest_defns << xtcc_set_name << ".indiv.insert(" << *it
			<< ");" << endl;
	}
	for(uint32_t i = 0; i < r_data->range.size(); ++i){
		code.quest_defns << xtcc_set_name
			<< ".range.push_back(pair<int32_t,int32_t>("
			<< r_data->range[i].first << ","
			<< r_data->range[i].second
			<< "));" << endl;
	}
	*/
	//code.quest_defns << r_data->print_replicate_code(string(xtcc_set_name));
	code.quest_defns_init_code << r_data->print_replicate_code(string(xtcc_set_name));
	string q_type_str;
	print_q_type(q_type_str);

	string datatype_str;
	print_data_type(datatype_str);

	ostringstream quest_decl;
#if 0
	quest_decl << "stringstream " << questionName_ << "_str;\n";
	quest_decl << questionName_ << "_str "
			<< "<< \"" << questionName_ << "\" ";
	if (for_bounds_stack.size() > 0 ) {

	}
#endif /* 0 */
	quest_decl << "{\n";
	quest_decl << "vector<TextExpression *> text_expr_vec;\n";

#if 0
	for (int i=0; i < textExprVec_.size(); ++i) {
		/*
		if (textExprVec_[i]->nameExpr_ == 0) {
			quest_decl << "text_expr_vec.push_back(new TextExpression(string(\""
				<< textExprVec_[i]->text_
				<< "\")));\n";
		} else {
			ExpressionCompiledCode expr_code;
			textExprVec_[i]->nameExpr_->PrintExpressionCode(expr_code);
			quest_decl << "text_expr_vec.push_back(new TextExpression("
				<< expr_code.code_expr.str()
				<< "));\n";
		}
		*/
		if (textExprVec_[i]->teType_ == TextExpression::simple_text_type) {
			quest_decl << "text_expr_vec.push_back(new TextExpression(string(\""
				<< textExprVec_[i]->text_
				<< "\")));\n";
		} else if (textExprVec_[i]->teType_ == TextExpression::named_attribute_type) {
			ExpressionCompiledCode expr_code;
			textExprVec_[i]->nameExpr_->PrintExpressionCode(expr_code);
			quest_decl << "text_expr_vec.push_back(new TextExpression("
				<< expr_code.code_expr.str()
				<< "));\n";
		} else if (textExprVec_[i]->teType_ == TextExpression::question_type) {
			ExpressionCompiledCode expr_code;

			if (textExprVec_[i]->questionIndexExpr_)
				textExprVec_[i]->questionIndexExpr_->PrintExpressionCode(expr_code);
			if (textExprVec_[i]->questionIndexExpr_ ) {
				quest_decl << "text_expr_vec.push_back( new TextExpression("
						<< textExprVec_[i]->pipedQuestion_->questionName_
						<< ", "
						<< expr_code.code_expr.str()
						<< ") ); /*  -NxD- */\n";
			} else {
				quest_decl << "text_expr_vec.push_back( new TextExpression("
						<< textExprVec_[i]->pipedQuestion_->questionName_
						<< ") ); /*  -NxD- */\n";
			}
		} else {
			stringstream err_msg;
			err_msg << " unhandled TextExpressionType ";
			print_err(compiler_internal_error, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		}

	}
#endif /* 0 */
	string q_title_code = PrintQuestionTitleCode (textExprVec_);
	quest_decl << q_title_code;

	if (array_mode) {
		quest_decl << "RangeQuestion * " << questionName_;
	} else {
		quest_decl <<  questionName_;
	}
	quest_decl << " = new RangeQuestion("
		<< ((type_ == QUESTION_TYPE) ?"QUESTION_TYPE, " : "QUESTION_ARR_TYPE, " )
		<< lineNo_ << ","
		<< "string( \"" << questionName_.c_str() << "\")" << ",";

	//quest_decl	<< "string(\" " << questionText_ << "\")"
	quest_decl << " text_expr_vec";
	quest_decl	<< ","
		<< q_type_str << ","
		<< no_mpn << ","
		<< datatype_str << ","
		<< xtcc_set_name;
	if (for_bounds_stack.size() > 0) {
		quest_decl << ", stack_of_loop_indices "
			<< ", dum_" << questionName_;
	}
	quest_decl << "," << question_attributes.Print();
	if (isStartOfBlock_) {
		quest_decl << ", true";
	} else {
		quest_decl << ", false";
	}
	quest_decl << ");\n";
	// I think these lines should move into the else clause of the if (array_mode)
	// which currently does not exist
	// if (!array_mode) {
	// 	quest_decl << "}\n";
	// }

	string mutex_range_set_name(questionName_ + "->mutexCodeList_");
	quest_decl << mutexCodeList_.print_replicate_code(mutex_range_set_name);

	if (array_mode) {
		quest_decl << "question_list.push_back(" << questionName_
			<< ");"
			<< questionName_ << " -> setQuestionIndexNo(our_question_index_no);"
			<< endl;
		quest_decl << "print_question_messages(" << questionName_ << ");\n";
		quest_decl << questionName_ << "_list.questionList.push_back(" << questionName_ << ");"
			<< endl;
		quest_decl << "}\n";
	} else {
		quest_decl << "print_question_messages(" << questionName_ << ");\n";
		quest_decl << "}\n";
	}

	if(for_bounds_stack.size() == 0){
		//code.quest_defns << quest_decl.str();
		code.quest_defns << "RangeQuestion * " << questionName_ << ";\n";
		code.quest_defns_init_code << quest_decl.str();
		// new
		code.array_quest_init_area << "question_list.push_back(" << questionName_
			<< "); "
			<< questionName_ << " -> setQuestionIndexNo(our_question_index_no);"
			<< endl;
		code.array_quest_init_area << "print_question_messages(" << questionName_ << ");\n";
	} else {
		code.array_quest_init_area << quest_decl.str();
	}

	if (for_bounds_stack.size() == 0) {
		AbstractQuestion::PrintEvalAndNavigateCode(code.program_code);
	} else {
		AbstractQuestion::PrintEvalArrayQuestion(code);
	}

}



void RangeQuestion::GenerateCode(StatementCompiledCode & code )
{
	if(for_bounds_stack.size() == 0){
		AbstractQuestion::PrintSetupBackJump(code);
		GenerateCodeSingleQuestion(code, false);
	} else {
		AbstractQuestion::PrintSetupBackJump(code);
		PrintArrayDeclarations(code);

		GenerateCodeSingleQuestion(code, true);
		//code.array_quest_init_area << questionName_ << "_list.questionList.push_back(" << questionName_ << ");"
		//	<< endl;
	}
	if(next_){
		next_->GenerateCode(code);
	}
}

//extern vector <scope*> active_scope_list;
void NamedStubQuestion::GenerateCodeSingleQuestion(StatementCompiledCode & code, bool array_mode)
{
	//AbstractQuestion::PrintSetupBackJump(quest_defns, program_code);

	string q_type_str;
	print_q_type(q_type_str);

	string datatype_str;
	print_data_type(datatype_str);

	ostringstream quest_decl;

	quest_decl << "{\n";
	quest_decl << "vector<TextExpression *> text_expr_vec;\n";
#if 0
	for (int i=0; i < textExprVec_.size(); ++i) {
		if (textExprVec_[i]->teType_ == TextExpression::simple_text_type) {
			quest_decl << "text_expr_vec.push_back(new TextExpression(string(\""
				<< textExprVec_[i]->text_
				<< "\")));\n";
		} else if (textExprVec_[i]->teType_ == TextExpression::question_type) {

			if (textExprVec_[i]->questionIndexExpr_ ) {
				ExpressionCompiledCode expr_code;
				textExprVec_[i]->questionIndexExpr_->PrintExpressionCode(expr_code);
				quest_decl << "text_expr_vec.push_back( new TextExpression("
						<< textExprVec_[i]->pipedQuestion_->questionName_
						<< ", "
						<< expr_code.code_expr.str()
						<< ") ); /*  -NxD- */\n";
			} else {
				quest_decl << "text_expr_vec.push_back( new TextExpression("
						<< textExprVec_[i]->pipedQuestion_->questionName_
						<< ") ); /*  -NxD- */\n";
			}
		} else {
			ExpressionCompiledCode expr_code;
			textExprVec_[i]->nameExpr_->PrintExpressionCode(expr_code);
			quest_decl << "text_expr_vec.push_back(new TextExpression("
				<< expr_code.code_expr.str()
				<< "));\n";
		}
	}
#endif /* 0 */
	string q_title_code = PrintQuestionTitleCode (textExprVec_);
	quest_decl << q_title_code;

	if (array_mode)
		quest_decl << "NamedStubQuestion * " << questionName_;
	else
		quest_decl << questionName_;

	quest_decl << " = new NamedStubQuestion("
		<< ((type_ == QUESTION_TYPE) ?"QUESTION_TYPE, " : "QUESTION_ARR_TYPE, " )
		<< lineNo_ << ","
		<< "string( \"" << questionName_ << "\")" << ",";

	quest_decl << " text_expr_vec";
	//quest_decl	<< "string(\" " << questionText_ << "\")"
	quest_decl	<< ","
		<< q_type_str << ","
		<< no_mpn << ","
		<< datatype_str << ",&"
		<< nr_ptr->name;
	if(for_bounds_stack.size() >0 ){
		quest_decl << ", stack_of_loop_indices "
			<< ", dum_" << questionName_;
	}
	quest_decl << "," << question_attributes.Print();
	if (isStartOfBlock_) {
		quest_decl << ", true";
	} else {
		quest_decl << ", false";
	}
	quest_decl << ");\n";
	//if (!array_mode) {
	//	quest_decl << "}\n";
	//}

	if (array_mode) {
		quest_decl << "question_list.push_back(" << questionName_ << "); "
			<< questionName_ << " -> setQuestionIndexNo(our_question_index_no);"
			<< endl;
		quest_decl << "print_question_messages(" << questionName_ << ");\n";
		quest_decl << questionName_ << "_list.questionList.push_back(" << questionName_ << ");"
			<< endl;
		quest_decl << "}\n";
	} else {
		quest_decl << "print_question_messages(" << questionName_ << ");\n";
		quest_decl << "}\n";
	}

	string mutex_range_set_name(questionName_ + "->mutexCodeList_");
	quest_decl << mutexCodeList_.print_replicate_code(mutex_range_set_name);

	if (for_bounds_stack.size() == 0) {
		// code.quest_defns << quest_decl.str();
		code.quest_defns << "NamedStubQuestion * " << questionName_ << ";\n";
		code.quest_defns_init_code << quest_decl.str();
		code.array_quest_init_area << "question_list.push_back(" << questionName_.c_str()
			<< "); "
			<< questionName_ << " -> setQuestionIndexNo(our_question_index_no);"
			<< endl;
		code.array_quest_init_area << "print_question_messages(" << questionName_ << ");\n";
	} else {
		code.array_quest_init_area << quest_decl.str();
	}
	//program_code << "\t\t" << questionName_.c_str() << "->eval();\n";

	if (for_bounds_stack.size() == 0) {
		AbstractQuestion::PrintEvalAndNavigateCode(code.program_code);
	}  else {
		AbstractQuestion::PrintEvalArrayQuestion(code);
	}

}

void NamedStubQuestion::GenerateCode(StatementCompiledCode &code)
{
	if(for_bounds_stack.size() == 0){
		AbstractQuestion::PrintSetupBackJump(code);
		GenerateCodeSingleQuestion(code, false);
	}  else {
		//----------------------------------------
		AbstractQuestion::PrintSetupBackJump(code);
		// PrintArrayDeclarations(code.quest_defns);
		PrintArrayDeclarations(code);
		GenerateCodeSingleQuestion(code, true);
		//code.array_quest_init_area << questionName_ << "_list.questionList.push_back(" << questionName_ << ");"
		//	<< endl;
	}

	if(next_){
		next_->GenerateCode(code);
	}

}

	//! this is only called in the compile time environment
NamedStubQuestion::NamedStubQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, vector<TextExpression*> text_expr_vec
	, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
	, named_range* l_nr_ptr
	, vector<AbstractExpression*>& l_for_bounds_stack
	, CompoundStatement * l_enclosing_scope
	, vector<ActiveVariableInfo* > l_av_info
	, QuestionAttributes  l_question_attributes
	):
	AbstractQuestion(this_stmt_type, line_number, l_name, text_expr_vec
			 , l_q_type, l_no_mpn, l_dt
			 , l_for_bounds_stack, l_enclosing_scope, l_av_info, l_question_attributes)
	, named_list()
	, nr_ptr(l_nr_ptr), stub_ptr(0)
	, displayData_()
	, currentPage_(0)
{
	for(int i=0; i<nr_ptr->stubs.size(); ++i) {
		if (nr_ptr->stubs[i].is_mutex) {
			mutexCodeList_.add_indiv(nr_ptr->stubs[i].code);
		}
		if (maxCode_ < nr_ptr->stubs[i].code) {
			maxCode_ = nr_ptr->stubs[i].code;
		}
	}
}

	//! this is only called in the compile time environment
NamedStubQuestion::NamedStubQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, vector<TextExpression*> text_expr_vec
	, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
	, named_range* l_nr_ptr
	, CompoundStatement * l_enclosing_scope
	, vector<ActiveVariableInfo* > l_av_info
	, QuestionAttributes  l_question_attributes
	):
	AbstractQuestion(this_stmt_type, line_number, l_name, text_expr_vec,
		l_q_type, l_no_mpn, l_dt, l_enclosing_scope, l_av_info, l_question_attributes
		)
	, named_list()
	, nr_ptr(l_nr_ptr), stub_ptr(0)
	, displayData_()
	, currentPage_(0)
{
	for(int i=0; i<nr_ptr->stubs.size(); ++i) {
		if (nr_ptr->stubs[i].is_mutex) {
			mutexCodeList_.add_indiv(nr_ptr->stubs[i].code);
		}
		if (maxCode_ < nr_ptr->stubs[i].code) {
			maxCode_ = nr_ptr->stubs[i].code;
		}
	}
}
#if 0
NamedStubQuestion::NamedStubQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, string l_q_text
	, QuestionType l_q_type, int32_t l_no_mpn
	, DataType l_dt, named_range * l_nr_ptr
	, QuestionAttributes  l_question_attributes
	):
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text
			 ,l_q_type, l_no_mpn, l_dt, l_question_attributes)
	, named_list()
	, nr_ptr(l_nr_ptr), stub_ptr(0)
{
#if 0
	vector <stub_pair> & v= *stub_ptr;
	for (int i=0; i<v.size(); ++i) {
		if (maxCode_ < v[i].code) {
			maxCode_ = v[i].code;
		}
	}
#endif /* 0 */
	for(int i=0; i<nr_ptr->stubs.size(); ++i) {
		if (nr_ptr->stubs[i].is_mutex) {
			mutexCodeList_.add_indiv(nr_ptr->stubs[i].code);
		}
		if (maxCode_ < nr_ptr->stubs[i].code) {
			maxCode_ = nr_ptr->stubs[i].code;
		}
	}
}
#endif /* 0 */
#if 0
//! only called in the runtime environment
NamedStubQuestion::NamedStubQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, string l_q_text
	, QuestionType l_q_type, int32_t l_no_mpn
	// , DataType l_dt , vector<stub_pair>* l_stub_ptr
	, DataType l_dt, named_range * l_nr_ptr
	, const vector<int32_t> & l_loop_index_values
	, DummyArrayQuestion * l_dummy_array
	, QuestionAttributes  l_question_attributes
	):
	AbstractQuestion(this_stmt_type, line_number, l_name, l_q_text,
		l_q_type, l_no_mpn, l_dt, l_loop_index_values, l_dummy_array, l_question_attributes
		)
	, named_list()
	, nr_ptr(l_nr_ptr), stub_ptr(0)
{
#if 0
	vector <stub_pair> & v= *stub_ptr;
	for (int i=0; i<v.size(); ++i) {
		if (maxCode_ < v[i].code) {
			maxCode_ = v[i].code;
		}
	}
#endif /* 0 */
	for(int i=0; i<nr_ptr->stubs.size(); ++i) {
		if (nr_ptr->stubs[i].is_mutex) {
			mutexCodeList_.add_indiv(nr_ptr->stubs[i].code);
		}
		if (maxCode_ < nr_ptr->stubs[i].code) {
			maxCode_ = nr_ptr->stubs[i].code;
		}
	}
}
#endif /* 0 */

void AbstractQuestion::print_q_type(string &s)
{
	const int32_t BUF_SIZE = 200;
	char buff[BUF_SIZE];
	if(q_type == spn){
		s = "spn";
	} else if (q_type == mpn){
		s = "mpn";
	} else {
		sprintf(buff, " internal compiler error: update AbstractQuestion::print_q_type: %d, %s\n",
			__LINE__, __FILE__);
		s = buff;
	}
}



void AbstractQuestion::print_data_type(string &s)
{
	stringstream mesg;
	mesg << "Is this functionality already duplicated somewhere else?"
		<< endl;
	LOG_MAINTAINER_MESSAGE(mesg.str());
#if 0
	if (qscript_debug::MAINTAINER_MESSAGES) {
		cerr << "Is this functionality already duplicated somewhere else?"
			<< ", line: " << __LINE__
			<< ", file: " << __FILE__
			<< ", func: " << __PRETTY_FUNCTION__
		<< endl;
	}
#endif /* 0 */
	if (dt == VOID_TYPE) {
		s = "VOID_TYPE";
	} else if (dt == INT8_TYPE) {
		s = "INT8_TYPE";
	} else if (dt ==  INT16_TYPE) {
		s = "INT16_TYPE";
	} else if (dt ==   INT32_TYPE) {
		s = "INT32_TYPE";
	} else if (dt ==  FLOAT_TYPE) {
		s = "FLOAT_TYPE";
	} else if (dt ==  DOUBLE_TYPE) {
		s = "DOUBLE_TYPE";
	} else if (dt ==  BOOL_TYPE){
		s = "BOOL_TYPE";
	} else if (dt ==  STRING_TYPE) {
		s = "STRING_TYPE";
	} else {
		const int32_t BUF_SIZE = 200;
		char buff[BUF_SIZE];
		sprintf(buff, " internal compiler error: update AbstractQuestion::print_data_type : %d, %s",
			__LINE__, __FILE__);
		s = buff;
	}
}

void NamedStubQuestion::WriteDataToDisk(ofstream& data_file)
{ }
#if 0
void NamedStubQuestion::WriteDataToDisk(ofstream& data_file)
{
	if(loop_index_values.size()>0){

		data_file << questionName_;
		for(int32_t i = 0; i< loop_index_values.size(); ++i){
			data_file << "$" << loop_index_values[i];
		}
	} else  {
		data_file << questionName_;
	}
	data_file << ":";
	if (isAnswered_) {
		for( set<int32_t>::iterator iter = input_data.begin();
				iter != input_data.end(); ++iter){
			data_file << *iter << " ";
		}
	}
	data_file << endl;
	stringstream mesg;
	//mesg << "I think this is the wrong place to clear - should be done at the end of main while loop in generated code, when user loads a new serial number";
	//LOG_MAINTAINER_MESSAGE(mesg.str());
	//input_data.clear();
}
#endif /* 0 */

void AbstractQuestion::PrintSetupBackJump(StatementCompiledCode &code)
{
	using qscript_parser::map_of_active_vars_for_questions;
	code.program_code << "/* ENTER: AbstractRuntimeQuestion::PrintSetupBackJump() : for_bounds_stack.size():"
		<< for_bounds_stack.size() << " */\n";
	if (program_options_ns::no_question_save_restore_optimization==false) {
		code.quest_defns << "map <string,int8_t> " << questionName_ << "_scope_int8_t;\n";
		code.quest_defns << "map <string,int16_t> " << questionName_ << "_scope_int16_t;\n";
		code.quest_defns << "map <string,int32_t> " << questionName_ << "_scope_int32_t;\n";
		code.quest_defns << "map <string,float> " << questionName_ << "_scope_float_t;\n";
		code.quest_defns << "map <string,double> " << questionName_ << "_scope_double_t;\n";
		code.quest_defns << "map <string,set<int32_t> > " << questionName_ << "_scope_question_t;\n";
	}


	code.program_code << "lab_" << questionName_ << ":" << endl;



	if(for_bounds_stack.size() == 0){
		code.program_code << "if( back_jump == true  && " << questionName_ <<  "->isAnswered_ == true ) {" << endl;
		//for(int32_t i = active_pop_vars_for_this_question.size()-1; i>=0; --i){
		//	code.program_code << active_pop_vars_for_this_question[i] << endl;
		//}
		// ostringstream &s(code.program_code);
		// the code below should be extracted to a method: NxD 11-Jun-2010

		// enable this later: virtual memory exhaustion because generated code too big
		if (program_options_ns::no_question_save_restore_optimization == false)
			SetupSimpleQuestionRestore(code);
		code.program_code << "if( jumpToQuestion == \"" << questionName_ << "\")\n{ back_jump = false;\n}\n";
		code.program_code << "}" << endl;


		// enable this later: virtual memory exhaustion because generated code too big
		if (program_options_ns::no_question_save_restore_optimization == false)
			SetupSimpleQuestionSave(code);
	} else {
		// Handle Array Question here

		ostringstream &s(code.program_code);
		s << "if( back_jump == true  && " << questionName_
			<<  "_list.questionList["
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< "]->isAnswered_ == true ) {" << endl;
		// enable this later: virtual memory exhaustion because generated code too big
		if (program_options_ns::no_question_save_restore_optimization == false)
			SetupArrayQuestionRestore(code);
		s << "}" << endl;
		// enable this later: virtual memory exhaustion because generated code too big
		if (program_options_ns::no_question_save_restore_optimization == false)
			SetupArrayQuestionSave(code);
	}
	code.program_code << "/* EXIT: AbstractRuntimeQuestion::PrintSetupBackJump()  */\n";
}


void AbstractQuestion::PrintEvalArrayQuestion(StatementCompiledCode & code)
{
	// ----------------------------------
	code.program_code << "// if (data_entry_window == 0) {\n\t//cout << \"jumpToQuestion = \" << jumpToQuestion << endl;"
			<< "//\tcout << \"jumpToIndex = \" << jumpToIndex << endl;"
			<< "//}\n"
			<< endl;
	string consolidated_for_loop_index = PrintConsolidatedForLoopIndex(for_bounds_stack);
	code.program_code << "if (" << endl
		<< "("
		<< questionName_ << "_list.questionList[" << consolidated_for_loop_index << "]"
		<< "->isAnswered_ == false  && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) ||" << endl
		<< " stopAtNextQuestion ||" << endl
		<< "( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited.size() == 0) || " << endl
		<< "  (p_navigation_mode == NAVIGATE_NEXT && " << endl
		<< "  " << questionName_ << "_list.questionList[" << consolidated_for_loop_index << "]"
		<< "->questionNoIndex_ > last_question_visited[last_question_visited.size()-1]->questionNoIndex_"
		<< ")) ||" << endl
		//<< "(jumpToQuestion == \"" << questionName_ << "\""
		//<< " && " << "jumpToIndex ==  "
		//<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
		//<< ") "
		<<  "( p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractRuntimeQuestion*>("
		<< questionName_ << "_list.questionList[" << consolidated_for_loop_index << "]"
		<< ") == p_jump_to_index)) ||"  << endl
		<< "((write_data_file_flag || write_qtm_data_file_flag || write_xtcc_data_file_flag) " << endl
		<< "  && !("
		<< questionName_ << "_list.questionList[" << consolidated_for_loop_index << "]"
		<< "->question_attributes.isAllowBlank()) && "
		<< questionName_ << "_list.questionList[" << consolidated_for_loop_index << "]"
		<< "->isAnswered_ == false "
		<< ")"
		<< ") "
		<< "{\n";
	code.program_code
		<<  "cout << \"reached here because: \" << " << endl
		<< "\""
		<< questionName_ << "_list.questionList[" << consolidated_for_loop_index << "]"
		<< "->isAnswered_ == false  && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) "
		<< ":\" " << endl
		<< "<< ("
		<< questionName_ << "_list.questionList[" << consolidated_for_loop_index << "]"
		<< "->isAnswered_ == false  && !(write_data_file_flag || write_qtm_data_file_flag||write_xtcc_data_file_flag)) "
		<< " << endl << "
		<< questionName_ << "_list.questionList[" << consolidated_for_loop_index << "]->isAnswered_"
		<<" << endl;"
		<< endl;

	code.program_code << "label_eval_" << questionName_ << ":\n";
	code.program_code << "if( jumpToQuestion == \"" << questionName_
		<< "\" && jumpToIndex == "
		<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
		<< "){\n"
		<< "back_jump = false;\n"
		<< "jumpToIndex = -1;\n"
		<< "}\n";

	code.program_code
		<< "if (p_navigation_mode == NAVIGATE_NEXT && last_question_visited[last_question_visited.size()-1] == "
		<< questionName_  << "_list.questionList["
		<< consolidated_for_loop_index << "]"
		<< " &&  "
		<< questionName_  << "_list.questionList["
		<< consolidated_for_loop_index << "]->isAnswered_ == true"
		<< ") {\n"
		<< " stopAtNextQuestion = true;\n";
	if (program_options_ns::emscripten_flag) {
		code.program_code
			<< "//fprintf (qscript_stdout, \" at question:  " << questionName_;
	} else {
		code.program_code
			<< "fprintf (qscript_stdout, \" at question:  " << questionName_;
	}
	code.program_code
		<< " arming stopAtNextQuestion = true \\n\");\n"
		<< "}";
	code.program_code	<< " else if ( " << questionName_ << "_list.questionList["
		<< consolidated_for_loop_index << "] ->question_attributes.hidden_==false) {\n";

	if (qscript_parser::page_nest_lev > 0) {
		code.program_code 
			<< "vec_page_" << qscript_parser::globalActivePageName_ << "_ret_val.push_back("
			<< questionName_ << "_list.questionList["
			<< consolidated_for_loop_index
			<< "]"
			<< ");" << endl;
		code.program_code << "\n\t}\n";
	} else {
		code.program_code << "\t vector<AbstractRuntimeQuestion*> ret_vec;" << endl
			<< "ret_vec.push_back (" << questionName_ << "_list.questionList["
			<< consolidated_for_loop_index
			<< "]);\n";
		code.program_code << "\t\tlast_question_visited = ret_vec;" << endl;
		code.program_code << "\t\tstopAtNextQuestion = false;\n";
		//code.program_code << "\t\treturn ret_vec;" << endl;

		code.program_code 
			<< "\t last_question_visited.clear();" << endl
			<< "\t last_question_visited.push_back("
			//<< questionName_ 
			<< questionName_ << "_list.questionList["
			<< consolidated_for_loop_index
			<< "]"
			<< ");" << endl
			<< "\t EvalReturnValue ev_ret_val; " << endl
			<< "\t ev_ret_val.qVec_ = ret_vec; " << endl 
			<< "\t ev_ret_val.errMessageVec_ = error_messages_vec; " << endl 
			<< "\t return ev_ret_val;" << endl;
		code.program_code << "\n\t}\n";
		//PrintUserNavigationArrayQuestion(code.program_code);
	}

	code.program_code << "}\n";
	//code.program_code << "*/\n";
}

#if 0
RangeQuestion::~RangeQuestion()
{
	delete r_data ; r_data = 0;
}
#endif /* 0 */


// -----------------------------------------------------
// DummyArrayQuestion


void DummyArrayQuestion::WriteDataToDisk(ofstream& data_file)
{ }

#if 0
void DummyArrayQuestion::WriteDataToDisk(ofstream& data_file)
{
	data_file << questionName_ << " BOUNDS";
	for(int32_t i = 0; i < array_bounds.size(); ++i){
		data_file << " "<< array_bounds[i];
	}
	data_file << endl;
}
#endif /* 0 */

int32_t GetTempMapKeyNumber()
{
	static int32_t temp_map_key_number;
	return temp_map_key_number++;
}

// ----------------------------------------
void AbstractQuestion::SetupSimpleQuestionRestore(StatementCompiledCode & code)
{
	ostringstream &s(code.program_code);
	s << "/* AbstractQuestion::SetupSimpleQuestionRestore */\n";
	for(int32_t i = 0; i < activeVarInfo_.size(); ++i){

		switch(activeVarInfo_[i]->type_){
		case INT8_TYPE:
		case INT16_TYPE:
		case INT32_TYPE:
		case FLOAT_TYPE:
		case DOUBLE_TYPE:
		case QUESTION_TYPE:
			s << GetRestoreVariableName(activeVarInfo_[i])
				<< " = "
				<< GetRestoreVariableContainerName(activeVarInfo_[i], questionName_)
				<< ";\n";
			break;
		case QUESTION_ARR_TYPE:
			s << PrintRestoreArrayQuestion(activeVarInfo_[i]);
			break;
		default:
			string err_msg = "unhandled type in SetupSimpleQuestionRestore()";
			s << err_msg;
			print_err(compiler_internal_error, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		}
	}
}

string GetRestoreVariableName(ActiveVariableInfo * av_info)
{
	ostringstream s;
	switch(av_info->type_){
	case INT8_TYPE:
		s << av_info->name_;
		break;
	case INT16_TYPE:
		s << av_info->name_;
		break;
	case INT32_TYPE:
		s << av_info->name_;
		break;
	case FLOAT_TYPE:
		s << av_info->name_;
		break;
	case DOUBLE_TYPE:
		s << av_info->name_;
		break;
	case QUESTION_TYPE:
		s << av_info->name_ << "->input_data";
		break;
	case QUESTION_ARR_TYPE:
		s << "/* GetRestoreVariableName::QUESTION_ARR_TYPE not yet handled */\n";
		break;
	default: {
			string err_msg = "unhandled type in print_pop_stack\"";
			s << err_msg;
			print_err(compiler_sem_err, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		}
	}
	return s.str();
}

string GetRestoreVariableContainerName(ActiveVariableInfo * av_info, string & questionName_)
{
	ostringstream s;
	switch(av_info->type_){
	case INT8_TYPE:
		s << questionName_ << "_scope_int8_t[\"" << av_info->name_ << "\"]";
		break;
	case INT16_TYPE:
		s << questionName_ << "_scope_int16_t[\"" << av_info->name_ << "\"]";
		break;
	case INT32_TYPE:
		s << questionName_ << "_scope_int32_t[\"" << av_info->name_ << "\"]";
		break;
	case FLOAT_TYPE:
		s << questionName_ << "_scope_float_t[\"" << av_info->name_ << "\"]";
		break;
	case DOUBLE_TYPE:
		s << questionName_ << "_scope_double_t[\"" << av_info->name_ << "\"]";
		break;
	case QUESTION_TYPE:
		s << av_info->name_ << "_scope_question_t"<<  "[\"" << questionName_ << "\"]";
		break;
		/*
	case QUESTION_ARR_TYPE:
		s << av_info->name_ << "_scope_question_t"<<  "[\"" << questionName_ << "\"]" << endl;
		break;
		*/
	default: {
			string err_msg = "unhandled type in GetRestoreVariableContainerName";
			s << err_msg;
			print_err(compiler_sem_err, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		}
	}
	return s.str();
}

string AbstractQuestion::PrintRestoreArrayQuestion(ActiveVariableInfo * av_info)
{
	ostringstream s;
	s << "/* ENTER AbstractQuestion::PrintRestoreArrayQuestion "
		<< av_info->name_
		<< " at location: " << questionName_
		<< " */\n";
	if(enclosingCompoundStatement_){
		vector<AbstractQuestion*> & questions_in_block =
			enclosingCompoundStatement_->questionsInBlock_;
		s << "/* questionsInBlock_: ";
		for(int32_t i = 0; i < questions_in_block.size(); ++i){
			s << questions_in_block[i]->questionName_ << " ";
		}
		s << " */\n";
	} else {
		ostringstream err_msg;
		err_msg << " enclosingCompoundStatement_ ==  0 ... exiting \n";
		print_err(compiler_internal_error, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
	}

	AbstractQuestion * restore_array_quest = 0;
	for(int32_t i = 0; i< qscript_parser::question_list.size(); ++i){
		if( qscript_parser::question_list[i]->questionName_
			== av_info->name_){
			restore_array_quest = qscript_parser::question_list[i];
			break;
		}
	}
	if(restore_array_quest == 0){
		string err_msg = "Could not find " + av_info->name_ + " in question list while generating restore array code"
			+ " PrintRestoreArrayQuestion ";
		print_err(compiler_internal_error, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
	}
	if(IsInTheSameScopeAndLevel(this, restore_array_quest)) {
		s << "/*"
			<< questionName_ << " and "
			<< restore_array_quest->questionName_
			<< " :are at the same scope and level */"
			<< endl;
		s << "for(int32_t xtcc_i = 0; xtcc_i < ";
		s << restore_array_quest->enclosingCompoundStatement_
			->ConsolidatedForLoopIndexStack_.back();
		s << ";++xtcc_i){\n";
		s<< "ostringstream map_key;\n"
			<< "map_key << \"" << questionName_ << "\""
			<< " << "
			<< "\"_\" << xtcc_i << \"$\" << "
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< ";" << endl
			<< restore_array_quest->questionName_
			<< "_list.questionList[xtcc_i]->input_data = "
			<< restore_array_quest->questionName_ << "_scope_question_t["
			<< "map_key.str()" << "];\n"
			<< endl;
		s << "}\n";

	} else if (NotInTheSameBlock(this, restore_array_quest)){
		s << PrintCodeRestoreArrayQuestionNotInTheSameBlock(restore_array_quest);
#if 0
		s << "/*"
			<< questionName_ << " and "
			<< restore_array_quest->questionName_
			<< " :belong to different blocks "
			<< "*/"
			<< endl;

		s << "for(int32_t xtcc_i = 0; xtcc_i < ";
		for(int32_t i1 = 0; i1 < restore_array_quest->for_bounds_stack.size(); ++i1) {
			BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
					restore_array_quest->for_bounds_stack[i1]);
			if(bin_expr_ptr){
				AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
				ExpressionCompiledCode expr_code;
				rhs->PrintExpressionCode(expr_code);
				s << expr_code.code_bef_expr.str() /* should be empty */
					<< expr_code.code_expr.str();
				if(i1<restore_array_quest->for_bounds_stack.size()-1) {
					s << "*";
				}
			} else {
				print_err(compiler_code_generation_error
					, "for loop index condition is not a binary expression"
					, 0, __LINE__, __FILE__);
			}
		}
		s << ";++xtcc_i){\n";
		s 	<< "ostringstream map_key;\n";
		s	<< "map_key << \"" << questionName_ << "\"";
		s	<< " << ";
		s	<< "\"_\" << xtcc_i << \"$\" << ";
			//delete later

		cerr 	<< "enclosingCompoundStatement_: " << enclosingCompoundStatement_
			<< "questionName_ : " << questionName_
			<< endl;
			//end delete later
		s	<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back();
		s	<< ";" << endl;
		s	<< restore_array_quest->questionName_;
		s	<< "_list.questionList[xtcc_i]->input_data = ";
		s	<< restore_array_quest->questionName_ << "_scope_question_t[";
		s	<< "map_key.str()" << "];\n";
		s	<< endl;
		s << "}\n";
#endif /* 0 */
	} else if (IsAtAHigherNestLevelInTheSameBlock(this, restore_array_quest)){
		s << "/*"
			<< questionName_
			<< " is at a higher nest level than "
			<< restore_array_quest->questionName_
			<< "*/"
			<< endl;

		// cerr 	<< "restore_array_quest: " << restore_array_quest
		// 	<< " restore_array_quest->for_bounds_stack: " << & (restore_array_quest->for_bounds_stack)
		// 	<< " for_bounds_stack.size(): " << for_bounds_stack.size() << " "
		// 	<< endl;
		if (for_bounds_stack.size() > 0 && restore_array_quest->for_bounds_stack.size() > 0) {
			s << "/* restore_array_quest: "
				<< " find where my for_bounds_stack\n"
				<< " and other question for_bounds_stack DONT match\n"
				<< " then from that point on in other question find bounds\n"
				<< " and multiply with current consolidated_for_loop_index\n"
				<< " and save all these to the question scope map\n"
				<< "*/\n"
				<< endl;
			s << "for(int32_t xtcc_i = 0; xtcc_i < ";
			vector <AbstractExpression * > e_stack;
			int32_t i1 = 0;
			for(i1 = 0; i1 < restore_array_quest->for_bounds_stack.size()
					&& i1 < for_bounds_stack.size()
					&& restore_array_quest->for_bounds_stack[i1]
						== for_bounds_stack[i1]
					; ++i1){
				e_stack.push_back(restore_array_quest->for_bounds_stack[i1]);
			}
			s << PrintConsolidatedForLoopIndex(e_stack);
			if (i1 < restore_array_quest->for_bounds_stack.size()) {
				s << "*";
			}
			for(; i1 < restore_array_quest->for_bounds_stack.size(); ++i1) {
				BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
						restore_array_quest->for_bounds_stack[i1]);
				if(bin_expr_ptr){
					AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
					ExpressionCompiledCode expr_code;
					rhs->PrintExpressionCode(expr_code);
					s << expr_code.code_bef_expr.str() /* should be empty */
						<< expr_code.code_expr.str();
					if(i1<restore_array_quest->for_bounds_stack.size()-1) {
						s << "*";
					}
				} else {
					print_err(compiler_code_generation_error
						, "for loop index condition is not a binary expression"
						, 0, __LINE__, __FILE__);
				}
			}
			s 	<< ";++xtcc_i){\n";
			s	<< "ostringstream map_key;\n";
			s	<< "map_key << \"" << questionName_ << "\"";
			s	<< " << ";
			s	<< "\"_\" << xtcc_i << \"$\" << ";
					//<< consolidated_for_loop_index_stack.back()
				s	<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back();
			s	<< ";" << endl;
			s	<< restore_array_quest->questionName_;
			s	<< "_list.questionList[xtcc_i]->input_data = ";
			s	<< restore_array_quest->questionName_ << "_scope_question_t[";
			s	<< "map_key.str()" << "];\n";
			s	<< endl;
			s 	<< "}\n";
		} else {
			s << "/* treat as if the question is outside our block */\n";
			s << PrintCodeRestoreArrayQuestionNotInTheSameBlock(restore_array_quest);
		}
	} else if (IsAtADeeperNestLevelInTheSameBlock(this, restore_array_quest)){
		s << "/*"
			<< questionName_
			<< " is at a deeper nest level than "
			<< restore_array_quest->questionName_
			<< "*/"
			<< endl;
		s << "for(int32_t xtcc_i = 0; xtcc_i < "
			<< PrintConsolidatedForLoopIndex(restore_array_quest->for_bounds_stack)
			<< "; ++xtcc_i){\n"
			<< "ostringstream map_key;\n"
			<< "map_key << \"" << questionName_ << "\""
			<< " << "
			<< "\"_\" << xtcc_i << \"$\" << "
			<< restore_array_quest->enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< ";" << endl
			<< restore_array_quest->questionName_ << "_list.questionList[xtcc_i]->input_data = "
			<< restore_array_quest->questionName_ << "_scope_question_t["
			<< "map_key.str()" << "];\n"
			<< endl;
		s << "}\n";
	} else {
		print_err(compiler_code_generation_error
		, "unhandled case in compiler ... exiting code generation"
		, 0, __LINE__, __FILE__);
		cerr << "questionName_:"
			<< questionName_
			<< ", restore_array_quest->questionName_"
			<< restore_array_quest->questionName_
			<< endl;
		{
			vector<AbstractQuestion*> & questions_in_block =
				enclosingCompoundStatement_->questionsInBlock_;
			cerr << "/* questionsInBlock_: quest_loc "
				<< questionName_ << ":";
			for(int32_t i = 0; i < questions_in_block.size(); ++i){
				cerr << questions_in_block[i]->questionName_ << " ";
			}
			cerr << " */\n";
		}
		{
			vector<AbstractQuestion*> & questions_in_block =
				restore_array_quest->enclosingCompoundStatement_->questionsInBlock_;
			cerr << "/* questionsInBlock_: restore_array_quest "
				<< restore_array_quest->questionName_ << ":";
			for(int32_t i = 0; i < questions_in_block.size(); ++i){
				cerr << questions_in_block[i]->questionName_ << " ";
			}
			cerr << " */\n";
		}

		exit(1);
	}

	s << "/* EXIT AbstractQuestion::PrintRestoreArrayQuestion */\n";
	return s.str();
}

string AbstractQuestion::PrintSaveArrayQuestion(ActiveVariableInfo * av_info)
{
	ostringstream s;
	s << "/* ENTER PrintSaveArrayQuestion "
		<< av_info->name_
		<< " at location: " << questionName_
		<< "*/\n";
	if(enclosingCompoundStatement_){
		vector<AbstractQuestion*> & questions_in_block =
			enclosingCompoundStatement_->questionsInBlock_;
		s << "/* questionsInBlock_: ";
		for(int32_t i = 0; i < questions_in_block.size(); ++i){
			s << questions_in_block[i]->questionName_ << " ";
		}
		s << " */\n";
	} else {
		ostringstream err_msg;
		err_msg << " enclosingCompoundStatement_ ==  0 ... exiting \n";
		print_err(compiler_internal_error, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
	}

	AbstractQuestion * save_array_quest = 0;
	for(int32_t i = 0; i< qscript_parser::question_list.size(); ++i){
		if( qscript_parser::question_list[i]->questionName_
			== av_info->name_){
			save_array_quest = qscript_parser::question_list[i];
			break;
		}
	}
	if(save_array_quest == 0){
		string err_msg = "Could not find "
			+ av_info->name_
			+ " in question list while generating restore array code"
			+ " PrintSaveArrayQuestion... exiting\n";
		print_err(compiler_internal_error, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		exit(1);
	}
	if(IsInTheSameScopeAndLevel(this, save_array_quest)){
		s << "/*"
			<< questionName_ << " and "
			<< save_array_quest->questionName_
			<< " :are at the same scope and level */"
			<< endl;
		s << "for(int32_t xtcc_i = 0; xtcc_i < ";
		s << save_array_quest->enclosingCompoundStatement_
			->ConsolidatedForLoopIndexStack_.back();
		s << ";++xtcc_i){\n";
		s<< "ostringstream map_key;\n"
			<< "map_key << \"" << questionName_ << "\""
			<< " << "
			<< "\"_\" << xtcc_i << \"$\" << "
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< ";" << endl
			<< save_array_quest->questionName_ << "_scope_question_t["
			<< "map_key.str()" << "] = "
			<< save_array_quest->questionName_ << "_list.questionList[xtcc_i]->input_data;\n"
			<< endl;
		s << "}\n";

	} else if (NotInTheSameBlock(this, save_array_quest)){
		s << PrintCodeSaveArrayQuestionNotInTheSameBlock(save_array_quest);
#if 0
		s << "/*"
			<< questionName_ << " and "
			<< save_array_quest->questionName_
			<< " :belong to different blocks "
			<< "*/"
			<< endl;
		s << "for(int32_t xtcc_i = 0; xtcc_i < ";
		for(int32_t i1 = 0; i1 < save_array_quest->for_bounds_stack.size(); ++i1) {
			BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
					save_array_quest->for_bounds_stack[i1]);
			if(bin_expr_ptr){
				AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
				ExpressionCompiledCode expr_code;
				rhs->PrintExpressionCode(expr_code);
				s << expr_code.code_bef_expr.str() /* should be empty */
					<< expr_code.code_expr.str();
				if(i1<save_array_quest->for_bounds_stack.size()-1) {
					s << "*";
				}
			} else {
				print_err(compiler_code_generation_error
					, "for loop index condition is not a binary expression"
					, 0, __LINE__, __FILE__);
			}
		}
		s << ";++xtcc_i){\n"
			<< "ostringstream map_key;\n"
			<< "map_key << \"" << questionName_ << "\""
			<< " << "
			<< "\"_\" << xtcc_i << \"$\" << "
			//<< consolidated_for_loop_index_stack.back()
			<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< ";" << endl
			<< save_array_quest->questionName_ << "_scope_question_t["
			<< "map_key.str()" << "] = "
			<< save_array_quest->questionName_ << "_list.questionList[xtcc_i]->input_data;\n"
			<< endl;
		s << "}\n";
#endif /* 0 */
	} else if (IsAtAHigherNestLevelInTheSameBlock(this, save_array_quest)){
		s << "/*"
			<< questionName_
			<< " is at a higher nest level than "
			<< save_array_quest->questionName_
			<< "*/"
			<< endl;

		if (save_array_quest->for_bounds_stack.size() > 0 && for_bounds_stack.size() > 0 ) {

			s << "/*: save_array_quest"
				<< " find where my for_bounds_stack\n"
				<< " and other question for_bounds_stack DONT match\n"
				<< " then from that point on in other question find bounds\n"
				<< " and multiply with current consolidated_for_loop_index\n"
				<< " and save all these to the question scope map\n"
				<< "*/\n"
				<< endl;
			s << "for(int32_t xtcc_i = 0; xtcc_i < ";
			vector <AbstractExpression * > e_stack;
			int32_t i1 = 0;
			for(i1 = 0; i1 < save_array_quest->for_bounds_stack.size()
					&& save_array_quest->for_bounds_stack[i1]
						 ==  for_bounds_stack[i1]
					; ++i1){
				e_stack.push_back(save_array_quest->for_bounds_stack[i1]);
			}
			s << PrintConsolidatedForLoopIndex(e_stack);
			if (i1 < save_array_quest->for_bounds_stack.size()) {
				s << "*";
			}
			for(; i1 < save_array_quest->for_bounds_stack.size(); ++i1) {
				BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
						save_array_quest->for_bounds_stack[i1]);
				if(bin_expr_ptr){
					AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
					ExpressionCompiledCode expr_code;
					rhs->PrintExpressionCode(expr_code);
					s << expr_code.code_bef_expr.str() /* should be empty */
						<< expr_code.code_expr.str();
					if(i1<save_array_quest->for_bounds_stack.size()-1) {
						s << "*";
					}
				} else {
					print_err(compiler_code_generation_error
						, "for loop index condition is not a binary expression"
						, 0, __LINE__, __FILE__);
				}
			}
			s << ";++xtcc_i){\n"
				<< "ostringstream map_key;\n"
				<< "map_key << \"" << questionName_ << "\""
				<< " << "
				<< "\"_\" << xtcc_i << \"$\" << "
				//<< consolidated_for_loop_index_stack.back()
				<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
				<< ";" << endl
				<< save_array_quest->questionName_ << "_scope_question_t["
				<< "map_key.str()" << "] = "
				<< save_array_quest->questionName_ << "_list.questionList[xtcc_i]->input_data;\n"
				<< endl;
			s << "}\n";
		} else if (for_bounds_stack.size() == 0) {
			s << "/* treat as if the question is outside our block */\n";
			s << PrintCodeSaveArrayQuestionNotInTheSameBlock(save_array_quest);
		}
	} else if (IsAtADeeperNestLevelInTheSameBlock(this, save_array_quest)){
		s << "/*"
			<< questionName_
			<< " is at a deeper nest level than "
			<< save_array_quest->questionName_
			<< "*/"
			<< endl;
		s << "for(int32_t xtcc_i = 0; xtcc_i < "
			<< PrintConsolidatedForLoopIndex(save_array_quest->for_bounds_stack)
			<< "; ++xtcc_i){\n"
			<< "ostringstream map_key;\n"
			<< "map_key << \"" << questionName_ << "\""
			<< " << "
			<< "\"_\" << xtcc_i << \"$\" << "
			<< save_array_quest->enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< ";" << endl
			<< save_array_quest->questionName_ << "_scope_question_t["
			<< "map_key.str()" << "] = "
			<< save_array_quest->questionName_ << "_list.questionList[xtcc_i]->input_data;\n"
			<< endl;
		s << "}\n";
	} else {
		print_err(compiler_code_generation_error
		, "unhandled case in compiler ... exiting code generation"
		, 0, __LINE__, __FILE__);
		cerr << "questionName_:"
			<< questionName_
			<< ", save_array_quest->questionName_"
			<< save_array_quest->questionName_
			<< endl;
		{
			vector<AbstractQuestion*> & questions_in_block =
				enclosingCompoundStatement_->questionsInBlock_;
			cerr << "/* questionsInBlock_: quest_loc "
				<< questionName_ << ":";
			for(int32_t i = 0; i < questions_in_block.size(); ++i){
				cerr << questions_in_block[i]->questionName_ << " ";
			}
			cerr << " */\n";
		}
		{
			vector<AbstractQuestion*> & questions_in_block =
				save_array_quest->enclosingCompoundStatement_->questionsInBlock_;
			cerr << "/* questionsInBlock_: save_array_quest "
				<< save_array_quest->questionName_ << ":";
			for(int32_t i = 0; i < questions_in_block.size(); ++i){
				cerr << questions_in_block[i]->questionName_ << " ";
			}
			cerr << " */\n";
		}

		exit(1);
	}

	s << "/* EXIT PrintSaveArrayQuestion */\n";
	return s.str();

}

void AbstractQuestion::SetupSimpleQuestionSave(StatementCompiledCode &code)
{
	ostringstream &s(code.program_code);
	s << "/* AbstractQuestion::SetupSimpleQuestionSave */\n";
	for(int32_t i = 0; i < activeVarInfo_.size(); ++i){
		switch(activeVarInfo_[i]->type_){
		case INT8_TYPE:
		case INT16_TYPE:
		case INT32_TYPE:
		case FLOAT_TYPE:
		case DOUBLE_TYPE:
		case QUESTION_TYPE:
			s << GetRestoreVariableContainerName(activeVarInfo_[i], questionName_)
				<< " = "
				<< GetRestoreVariableName(activeVarInfo_[i])
				<< ";\n";
			break;
		case QUESTION_ARR_TYPE:
			s << PrintSaveArrayQuestion(activeVarInfo_[i]);
			break;
		default:
			string err_msg = "unhandled type in SetupSimpleQuestionRestore()";
			s << err_msg;
			print_err(compiler_internal_error, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		}
	}
}


void AbstractQuestion::SetupArrayQuestionRestore(StatementCompiledCode &code)
{
	ostringstream &s(code.program_code);
	s << "/* ENTER AbstractQuestion::SetupArrayQuestionRestore */\n";
	PrintRestoreMyPreviousIterationsData(code);
	int32_t temp_map_key_no = GetTempMapKeyNumber();
	s << "ostringstream map_key_" << temp_map_key_no << ";\n";
	for(int32_t i = 0; i < activeVarInfo_.size(); ++i){
		switch(activeVarInfo_[i]->type_){
		case INT8_TYPE:
		case INT16_TYPE:
		case INT32_TYPE:
		case FLOAT_TYPE:
		case DOUBLE_TYPE:
		case QUESTION_TYPE:{


			ostringstream map_key;
			map_key<< "map_key_" << temp_map_key_no;
			s << map_key.str() << "<< \"" << activeVarInfo_[i]->name_ << "\" << \"_\" << "
				<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
				<< ";\n";
			s << GetRestoreVariableName(activeVarInfo_[i])
				<< " = "
				<< GetRestoreVariableContainerNameArray(activeVarInfo_[i]
						, questionName_, map_key.str())
				<< ";\n";
			}
			break;
		case QUESTION_ARR_TYPE:
			s << PrintRestoreArrayQuestion(activeVarInfo_[i]);
			break;
		default:
			string err_msg = "unhandled type in SetupArrayQuestionRestore()";
			s << err_msg;
			print_err(compiler_internal_error, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		}
	}
	RestoreQuestionsInMyBlockThatAreAfterMe(code);
	s << "/* EXIT AbstractQuestion::SetupArrayQuestionRestore */\n";
}

void AbstractQuestion::PrintSaveMyPreviousIterationsData(StatementCompiledCode &code)
{
	ostringstream &s(code.program_code);
	s << "/* ENTER:AbstractQuestion::PrintSaveMyPreviousIterationsData */" << endl;
	s << "for(int32_t xtcc_i = 0; xtcc_i < "
		//<< consolidated_for_loop_index_stack.back() << "-1"
		<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back() << "-1"
		<< ";++xtcc_i){\n";
	s << "ostringstream temp_map_key;\n";
	s << "temp_map_key << \"" << questionName_ << "\" << \"_\" << "
		<< "xtcc_i"
		<< " << \"$\" << "
		//<< consolidated_for_loop_index_stack.back()
		<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
		<< ";\n"
		<< endl;
	//s << "temp_map_key2 << " << questionName_ << " << \"_\" << "
	//	<< "xtcc_i"
	//	<< ";\n";
	s << questionName_ << "_scope_question_t[ temp_map_key.str()"
		<< "] = "
		<< questionName_ << "_list.questionList[xtcc_i]->input_data;\n";
	s << "}\n";

	s << "/* EXIT:AbstractQuestion::PrintSaveMyPreviousIterationsData */" << endl;
}


void AbstractQuestion::SetupArrayQuestionSave(StatementCompiledCode &code)
{
	ostringstream &s(code.program_code);
	s << "/* ENTER AbstractQuestion::SetupArrayQuestionSave */\n";
	PrintSaveMyPreviousIterationsData(code);
	int32_t temp_map_key_no = GetTempMapKeyNumber();
	s << "ostringstream map_key_" << temp_map_key_no << ";\n";
	for(int32_t i = 0; i < activeVarInfo_.size(); ++i){
		switch(activeVarInfo_[i]->type_){
		case INT8_TYPE:
		case INT16_TYPE:
		case INT32_TYPE:
		case FLOAT_TYPE:
		case DOUBLE_TYPE:
		case QUESTION_TYPE:{
			ostringstream map_key;
			map_key<< "map_key_" << temp_map_key_no;
			s << map_key.str() << "<< \"" << activeVarInfo_[i]->name_ << "\" << \"_\" << "
				<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
				<< ";\n";
			s << GetRestoreVariableContainerNameArray(activeVarInfo_[i], questionName_, map_key.str())
				<< " = "
				<< GetRestoreVariableName(activeVarInfo_[i])
				<< ";\n";
			}
			break;
		case QUESTION_ARR_TYPE:
			s << PrintSaveArrayQuestion(activeVarInfo_[i]);
			break;
		default:
			string err_msg = "unhandled type in SetupArrayQuestionSave()";
			s << err_msg;
			print_err(compiler_internal_error, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		}
	}
	SaveQuestionsInMyBlockThatAreAfterMe(code);
	s << "/* EXIT AbstractQuestion::SetupArrayQuestionSave */\n";
}

string GetRestoreVariableContainerNameArray(
	ActiveVariableInfo * av_info
	, string & questionName_, string map_key)
{
	ostringstream s;
	switch(av_info->type_){
	case INT8_TYPE:
		s << questionName_ << "_scope_int8_t[" << map_key << ".str()" << "]";
		break;
	case INT16_TYPE:
		s << questionName_ << "_scope_int16_t[" << map_key << ".str()" << "]";
		break;
	case INT32_TYPE:
		s << questionName_ << "_scope_int32_t[" << map_key << ".str()" << "]";
		break;
	case FLOAT_TYPE:
		s << questionName_ << "_scope_float_t[" << map_key << ".str()" << "]";
		break;
	case DOUBLE_TYPE:
		s << questionName_ << "_scope_double_t[" << map_key << ".str()" << "]";
		break;
	case QUESTION_TYPE:
		s << av_info->name_ << "_scope_question_t"<<  "[" << map_key << ".str()" << "]";
		break;
		/*
	case QUESTION_ARR_TYPE:
		s << av_info->name_ << "_scope_question_t"<<  "[\"" << questionName_ << "\"]" << endl;
		break;
		*/
	default: {
			string err_msg = "unhandled type in print_pop_stack";
			s << err_msg;
			print_err(compiler_sem_err, err_msg, qscript_parser::line_no, __LINE__, __FILE__);
		}
	}
	return s.str();
}

bool AbstractQuestion::QuestionIsInMyBlock(AbstractQuestion *q)
{
	vector<AbstractQuestion*> & questions_in_block =
		enclosingCompoundStatement_->questionsInBlock_;
	for(int32_t i = 0; i < questions_in_block.size(); ++i){
		if(q == questions_in_block[i]){
			return true;
		}
	}
	return false;
}

bool IsInTheSameScopeAndLevel(AbstractQuestion *q1, AbstractQuestion * q2)
{
	return q1->QuestionIsInMyBlock(q2) && q2->QuestionIsInMyBlock(q1);
}


bool NotInTheSameBlock(AbstractQuestion *q1, AbstractQuestion * q2)
{
	return(!q1->QuestionIsInMyBlock(q2)) && (!q2->QuestionIsInMyBlock(q1));
}

bool IsAtAHigherNestLevelInTheSameBlock(AbstractQuestion *q1, AbstractQuestion *q2)
{
	return (q1->QuestionIsInMyBlock(q2)) && (!q2->QuestionIsInMyBlock(q1));
}

bool IsAtADeeperNestLevelInTheSameBlock(AbstractQuestion *q1, AbstractQuestion *q2)
{
	//cerr << "IsAtADeeperNestLevelInTheSameBlock(q1 = " << q1->questionName_
	//	<< ", q2 = " << q2->questionName_ << endl;
	//cerr << "(q1->QuestionIsInMyBlock(q2)):" << (q1->QuestionIsInMyBlock(q2))
	//	<< endl;
	//cerr << "q2->QuestionIsInMyBlock(q1):" << q2->QuestionIsInMyBlock(q1)
	//	<< endl;
	return (!q1->QuestionIsInMyBlock(q2)) && (q2->QuestionIsInMyBlock(q1));
}


void AbstractQuestion::SaveQuestionsInMyBlockThatAreAfterMe(StatementCompiledCode & code)
{
	ostringstream &s(code.program_code);
	s << "/* ENTER AbstractQuestion::SaveQuestionsInMyBlockThatAreAfterMe */" << endl;
	int32_t pos_start_of_for_loop = -1;
	for(int32_t i = 0; i < enclosingCompoundStatement_->nestedCompoundStatementStack_.size(); ++i){
		if(enclosingCompoundStatement_->nestedCompoundStatementStack_[i]->flagIsAForBody_){
			pos_start_of_for_loop = i;
			break;
		}
	}

	if(pos_start_of_for_loop == -1){
		ostringstream err_msg;
		err_msg << "Compiler internal error: cant find start of for loop in nestedCompoundStatementStack_";
		print_err(compiler_internal_error, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
	}

	vector<AbstractQuestion*> & questions_in_block=  enclosingCompoundStatement_->
		nestedCompoundStatementStack_[pos_start_of_for_loop]->questionsInBlock_;
	s << "/* questions in my block ("
		<< questionName_ << "):";
	for(int32_t i = 0; i < questions_in_block.size(); ++i){
		s << questions_in_block[i]->questionName_ << ",";
	}
	s << "*/" << endl;
	vector<AbstractQuestion*>::iterator my_loc =
		find(questions_in_block.begin(), questions_in_block.end(), this);
	if(my_loc == questions_in_block.end()){
		ostringstream err_msg;
		err_msg << "unable to find self: " << questionName_
			<< "in block: "
			<< " code generated here is\n"
			<< s.str()
			<< "\n... exiting\n";
		print_err(compiler_internal_error, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		exit(1);
	}
	if(my_loc+1 == questions_in_block.end()){
		s << "/* I = " << questionName_ << " is the last question in in block "
			<< " nothing to do */"<< endl;
	} else {
		for( vector<AbstractQuestion*>::iterator it = my_loc+1;
				it != questions_in_block.end(); ++it){
			AbstractQuestion *quest_loc = this, *save_array_quest = *it;

			if(IsInTheSameScopeAndLevel(quest_loc, save_array_quest)){
				s << "/*"
					<< quest_loc->questionName_ << " and "
					<< save_array_quest->questionName_
					<< " :are at the same scope and level */"
					<< endl;
				stringstream mesg;
				mesg << "Need to revisit this to check if condition should be "
					<< "xtcc_i\" <= \" or \"<\" and other similar places  "
					<< endl;
				LOG_MAINTAINER_MESSAGE(mesg.str());
				s << "for(int32_t xtcc_i = 0; xtcc_i < ";
				s << save_array_quest->enclosingCompoundStatement_
					->ConsolidatedForLoopIndexStack_.back();
				s << ";++xtcc_i){\n";
				s<< "ostringstream map_key;\n"
					<< "map_key << \"" << questionName_ << "\""
					<< " << "
					<< "\"_\" << xtcc_i << \"$\" << "
					<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
					<< ";" << endl
					<< save_array_quest->questionName_ << "_scope_question_t["
					<< "map_key.str()" << "] = "
					<< save_array_quest->questionName_
					<< "_list.questionList[xtcc_i]->input_data;\n"
					<< endl;
				s << "}\n";

			} else if (NotInTheSameBlock(quest_loc, save_array_quest)){
				s << "/*"
					<< quest_loc->questionName_ << " and "
					<< save_array_quest->questionName_
					<< " :belong to different blocks "
					<< "*/"
					<< endl;
				s << "for(int32_t xtcc_i = 0; xtcc_i < ";
				for(int32_t i1 = 0; i1 < save_array_quest->for_bounds_stack.size(); ++i1) {
					BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
							save_array_quest->for_bounds_stack[i1]);
					if(bin_expr_ptr){
						AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
						ExpressionCompiledCode expr_code;
						rhs->PrintExpressionCode(expr_code);
						s << expr_code.code_bef_expr.str() /* should be empty */
							<< expr_code.code_expr.str();
						if(i1<save_array_quest->for_bounds_stack.size()-1) {
							s << "*";
						}
					} else {
						print_err(compiler_code_generation_error
							, "for loop index condition is not a binary expression"
							, 0, __LINE__, __FILE__);
					}
				}
				s << ";++xtcc_i){\n"
					<< "ostringstream map_key;\n"
					<< "map_key << \"" << questionName_ << "\""
					<< " << "
					<< "\"_\" << xtcc_i << \"$\" << "
					//<< consolidated_for_loop_index_stack.back()
					<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
					<< ";" << endl
					<< save_array_quest->questionName_ << "_scope_question_t["
					<< "map_key.str()" << "] = "
					<< save_array_quest->questionName_
					<< "_list.questionList[xtcc_i]->input_data;\n"
					<< endl;
				s << "}\n";
			} else if (IsAtAHigherNestLevelInTheSameBlock(quest_loc, save_array_quest)){
				s << "/*"
					<< quest_loc->questionName_
					<< " is at a higher nest level than "
					<< save_array_quest->questionName_
					<< "*/"
					<< endl;
				s << "/* save_array_quest: "
					<< " find where my for_bounds_stack\n"
					<< " and other question for_bounds_stack DONT match\n"
					<< " then from that point on in other question find bounds\n"
					<< " and multiply with current consolidated_for_loop_index\n"
					<< " and save all these to the question scope map\n"
					<< "*/\n"
					<< endl;
				s << "for(int32_t xtcc_i = 0; xtcc_i < ";
				vector <AbstractExpression * > e_stack;
				int32_t i1 = 0;
				for(i1 = 0; i1 < save_array_quest->for_bounds_stack.size()
						&& save_array_quest->for_bounds_stack[i1]
							 ==  for_bounds_stack[i1]
						; ++i1){
					e_stack.push_back(save_array_quest->for_bounds_stack[i1]);
				}
				s 	<< "("
					<< PrintConsolidatedForLoopIndex(e_stack)
					<< ")";

				if (i1 < save_array_quest->for_bounds_stack.size()) {
					s << "*";
				}
				for(; i1 < save_array_quest->for_bounds_stack.size(); ++i1) {
					BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
							save_array_quest->for_bounds_stack[i1]);
					if(bin_expr_ptr){
						AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
						ExpressionCompiledCode expr_code;
						rhs->PrintExpressionCode(expr_code);
						s << expr_code.code_bef_expr.str() /* should be empty */
							<< expr_code.code_expr.str();
						if(i1<save_array_quest->for_bounds_stack.size()-1) {
							s << "*";
						}
					} else {
						print_err(compiler_code_generation_error
							, "for loop index condition is not a binary expression"
							, 0, __LINE__, __FILE__);
					}
				}
				s << ";++xtcc_i){\n"
					<< "ostringstream map_key;\n"
					<< "map_key << \"" << questionName_ << "\""
					<< " << "
					<< "\"_\" << xtcc_i << \"$\" << "
					//<< consolidated_for_loop_index_stack.back()
					<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
					<< ";" << endl
					<< save_array_quest->questionName_ << "_scope_question_t["
					<< "map_key.str()" << "] = "
					<< save_array_quest->questionName_
					<< "_list.questionList[xtcc_i]->input_data;\n"
					<< endl;
				s << "}\n";

			} else if (IsAtADeeperNestLevelInTheSameBlock(quest_loc, save_array_quest)){
				s << "/*"
					<< quest_loc->questionName_
					<< " is at a deeper nest level than "
					<< save_array_quest->questionName_
					<< "*/"
					<< endl;
				s << "for(int32_t xtcc_i = 0; xtcc_i < ";
				s << save_array_quest->enclosingCompoundStatement_
					->ConsolidatedForLoopIndexStack_.back()
					<< "-1";
				s << ";++xtcc_i){\n";
				s<< "ostringstream map_key;\n"
					<< "map_key << \"" << questionName_ << "\""
					<< " << "
					<< "\"_\" << xtcc_i << \"$\" << "
					<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
					<< ";" << endl
					<< save_array_quest->questionName_ << "_scope_question_t["
					<< "map_key.str()" << "] = "
					<< save_array_quest->questionName_
					<< "_list.questionList[xtcc_i]->input_data;\n"
					<< endl;
				s << "}\n";

			} else {
				print_err(compiler_code_generation_error
				, "unhandled case in compiler ... exiting code generation"
				, 0, __LINE__, __FILE__);
				cerr << "quest_loc->questionName_:"
					<< quest_loc->questionName_
					<< ", save_array_quest->questionName_"
					<< save_array_quest->questionName_
					<< endl;
				{
					vector<AbstractQuestion*> & questions_in_block =
						quest_loc->enclosingCompoundStatement_->questionsInBlock_;
					cerr << "/* questionsInBlock_: quest_loc "
						<< quest_loc->questionName_ << ":";
					for(int32_t i = 0; i < questions_in_block.size(); ++i){
						cerr << questions_in_block[i]->questionName_ << " ";
					}
					cerr << " */\n";
				}
				{
					vector<AbstractQuestion*> & questions_in_block =
						save_array_quest->enclosingCompoundStatement_->questionsInBlock_;
					cerr << "/* questionsInBlock_: save_array_quest "
						<< save_array_quest->questionName_ << ":";
					for(int32_t i = 0; i < questions_in_block.size(); ++i){
						cerr << questions_in_block[i]->questionName_ << " ";
					}
					cerr << " */\n";
				}

				exit(1);
			}
		}
	}
	s << "/* EXIT AbstractQuestion::SaveQuestionsInMyBlockThatAreAfterMe */" << endl;
}

void AbstractQuestion::RestoreQuestionsInMyBlockThatAreAfterMe(StatementCompiledCode & code)
{
	ostringstream &s(code.program_code);
	s << "/* ENTER AbstractQuestion::RestoreQuestionsInMyBlockThatAreAfterMe */" << endl;
	int32_t pos_start_of_for_loop = -1;
	for(int32_t i = 0; i < enclosingCompoundStatement_->nestedCompoundStatementStack_.size(); ++i){
		if(enclosingCompoundStatement_->nestedCompoundStatementStack_[i]->flagIsAForBody_){
			pos_start_of_for_loop = i;
			break;
		}
	}

	if(pos_start_of_for_loop == -1){
		ostringstream err_msg;
		err_msg << "Compiler internal error: cant find start of for loop in nestedCompoundStatementStack_";
		print_err(compiler_internal_error, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
	}

	vector<AbstractQuestion*> & questions_in_block=  enclosingCompoundStatement_->
		nestedCompoundStatementStack_[pos_start_of_for_loop]->questionsInBlock_;
	s << "/* questions in my block ("
		<< questionName_ << "):";
	for(int32_t i = 0; i < questions_in_block.size(); ++i){
		s << questions_in_block[i]->questionName_ << ",";
	}
	s << "*/" << endl;
	vector<AbstractQuestion*>::iterator my_loc =
		find(questions_in_block.begin(), questions_in_block.end(), this);
	if(my_loc == questions_in_block.end()){
		ostringstream err_msg;
		err_msg << "unable to find self : " << questionName_
			<< " in block "
			<< " code generated here is\n"
			<< s.str()
			<< "\n... exiting\n";
		print_err(compiler_internal_error, err_msg.str(), qscript_parser::line_no, __LINE__, __FILE__);
		exit(1);
	}
	if(my_loc+1 == questions_in_block.end()){
		s << "/* I = " << questionName_ << " is the last question in in block "
			<< " nothing to do */"<< endl;
	} else {
		for( vector<AbstractQuestion*>::iterator it = my_loc+1;
				it != questions_in_block.end(); ++it){
			AbstractQuestion *quest_loc = this, *restore_array_quest = *it;
			if(IsInTheSameScopeAndLevel(quest_loc, restore_array_quest)){
				s << "/*"
					<< quest_loc->questionName_ << " and "
					<< restore_array_quest->questionName_
					<< " :are at the same scope and level */"
					<< endl;
				stringstream mesg;
				mesg << "Need to revisit this to check if condition should be "
					<< "xtcc_i\" <= \" or \"<\" and other similar places  "
					<< endl;
				LOG_MAINTAINER_MESSAGE(mesg.str());
				s << "for(int32_t xtcc_i = 0; xtcc_i < ";
				s << restore_array_quest->enclosingCompoundStatement_
					->ConsolidatedForLoopIndexStack_.back();
				s << ";++xtcc_i){\n";
				s<< "ostringstream map_key;\n"
					<< "map_key << \"" << questionName_ << "\""
					<< " << "
					<< "\"_\" << xtcc_i << \"$\" << "
					<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
					<< ";" << endl
					<< restore_array_quest->questionName_
					<< "_list.questionList[xtcc_i]->input_data = "
					<< restore_array_quest->questionName_ << "_scope_question_t["
					<< "map_key.str()" << "];\n"
					<< endl;
				s << "}\n";
			} else if (NotInTheSameBlock(quest_loc, restore_array_quest)){
				s << "/*"
					<< quest_loc->questionName_ << " and "
					<< restore_array_quest->questionName_
					<< " :belong to different blocks "
					<< "*/"
					<< endl;
				s << "for(int32_t xtcc_i = 0; xtcc_i < ";
				for(int32_t i1 = 0; i1 < restore_array_quest->for_bounds_stack.size(); ++i1) {
					BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
							restore_array_quest->for_bounds_stack[i1]);
					if(bin_expr_ptr){
						AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
						ExpressionCompiledCode expr_code;
						rhs->PrintExpressionCode(expr_code);
						s << expr_code.code_bef_expr.str() /* should be empty */
							<< expr_code.code_expr.str();
						if(i1<restore_array_quest->for_bounds_stack.size()-1) {
							s << "*";
						}
					} else {
						print_err(compiler_code_generation_error
							, "for loop index condition is not a binary expression"
							, 0, __LINE__, __FILE__);
					}
				}
				s << ";++xtcc_i){\n"
					<< "ostringstream map_key;\n"
					<< "map_key << \"" << questionName_ << "\""
					<< " << "
					<< "\"_\" << xtcc_i << \"$\" << "
					//<< consolidated_for_loop_index_stack.back()
					<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
					<< ";" << endl
					<< restore_array_quest->questionName_
					<< "_list.questionList[xtcc_i]->input_data = "
					<< restore_array_quest->questionName_ << "_scope_question_t["
					<< "map_key.str()" << "]  ;\n"
					<< endl;
				s << "}\n";

			} else if (IsAtAHigherNestLevelInTheSameBlock(quest_loc, restore_array_quest)){
				s << "/*"
					<< quest_loc->questionName_
					<< " is at a higher nest level than "
					<< restore_array_quest->questionName_
					<< "*/"
					<< endl;
				s << "/* restore_array_quest:"
					<< " find where my for_bounds_stack\n"
					<< " and other question for_bounds_stack DONT match\n"
					<< " then from that point on in other question find bounds\n"
					<< " and multiply with current consolidated_for_loop_index\n"
					<< " and save all these to the question scope map\n"
					<< "*/\n"
					<< endl;
				s << "for(int32_t xtcc_i = 0; xtcc_i < ";
				vector <AbstractExpression * > e_stack;
				int32_t i1 = 0;
				for(i1 = 0; i1 < restore_array_quest->for_bounds_stack.size()
						&& restore_array_quest->for_bounds_stack[i1]
							== for_bounds_stack[i1]
						; ++i1){
					e_stack.push_back(restore_array_quest->for_bounds_stack[i1]);
				}
				s 	<< "("
					<< PrintConsolidatedForLoopIndex(e_stack)
					<< ")";

				if (i1 < restore_array_quest->for_bounds_stack.size()) {
					s << "*";
				}
				for(; i1 < restore_array_quest->for_bounds_stack.size(); ++i1) {
					BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
							restore_array_quest->for_bounds_stack[i1]);
					if(bin_expr_ptr){
						AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
						ExpressionCompiledCode expr_code;
						rhs->PrintExpressionCode(expr_code);
						s << expr_code.code_bef_expr.str() /* should be empty */
							<< expr_code.code_expr.str();
						if(i1<restore_array_quest->for_bounds_stack.size()-1) {
							s << "*";
						}
					} else {
						print_err(compiler_code_generation_error
							, "for loop index condition is not a binary expression"
							, 0, __LINE__, __FILE__);
					}
				}
				s << ";++xtcc_i){\n"
					<< "ostringstream map_key;\n"
					<< "map_key << \"" << questionName_ << "\""
					<< " << "
					<< "\"_\" << xtcc_i << \"$\" << "
					//<< consolidated_for_loop_index_stack.back()
					<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
					<< ";" << endl
					<< restore_array_quest->questionName_
					<< "_list.questionList[xtcc_i]->input_data = "
					<< restore_array_quest->questionName_ << "_scope_question_t["
					<< "map_key.str()" << "];\n"
					<< endl;
				s << "}\n";

			} else if (IsAtADeeperNestLevelInTheSameBlock(quest_loc, restore_array_quest)){
				s << "/*"
					<< quest_loc->questionName_
					<< " is at a deeper nest level than "
					<< restore_array_quest->questionName_
					<< "*/"
					<< endl;
				s << "for(int32_t xtcc_i = 0; xtcc_i < ";
				s << restore_array_quest->enclosingCompoundStatement_
					->ConsolidatedForLoopIndexStack_.back()
					<< "-1";
				s << ";++xtcc_i){\n";
				s<< "ostringstream map_key;\n"
					<< "map_key << \"" << questionName_ << "\""
					<< " << "
					<< "\"_\" << xtcc_i << \"$\" << "
					<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
					<< ";" << endl
					<< restore_array_quest->questionName_
					<< "_list.questionList[xtcc_i]->input_data = "
					<< restore_array_quest->questionName_ << "_scope_question_t["
					<< "map_key.str()" << "];\n"
					<< endl;
				s << "}\n";
			} else {
				print_err(compiler_code_generation_error
				, "unhandled case in compiler ... exiting code generation"
				, 0, __LINE__, __FILE__);
				cerr << "quest_loc->questionName_:"
					<< quest_loc->questionName_
					<< ", restore_array_quest->questionName_"
					<< restore_array_quest->questionName_
					<< endl;
				{
					vector<AbstractQuestion*> & questions_in_block =
						quest_loc->enclosingCompoundStatement_->questionsInBlock_;
					cerr << "/* questionsInBlock_: quest_loc "
						<< quest_loc->questionName_ << ":";
					for(int32_t i = 0; i < questions_in_block.size(); ++i){
						cerr << questions_in_block[i]->questionName_ << " ";
					}
					cerr << " */\n";
				}
				{
					vector<AbstractQuestion*> & questions_in_block =
						restore_array_quest->enclosingCompoundStatement_->questionsInBlock_;
					cerr << "/* questionsInBlock_: restore_array_quest "
						<< restore_array_quest->questionName_ << ":";
					for(int32_t i = 0; i < questions_in_block.size(); ++i){
						cerr << questions_in_block[i]->questionName_ << " ";
					}
					cerr << " */\n";
				}
				exit(1);
			}
		}
	}
	s << "/* EXIT AbstractQuestion::RestoreQuestionsInMyBlockThatAreAfterMe */" << endl;
}


void AbstractQuestion::PrintRestoreMyPreviousIterationsData(StatementCompiledCode &code)
{
	ostringstream &s(code.program_code);
	s << "/* ENTER:AbstractQuestion::PrintRestoreMyPreviousIterationsData */" << endl;
	s << "for(int32_t xtcc_i = 0; xtcc_i < "
		//<< consolidated_for_loop_index_stack.back() << "-1"
		<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back() << "-1"
		<< ";++xtcc_i){\n";
	s << "ostringstream temp_map_key;\n";
	s << "temp_map_key << \"" << questionName_ << "\" << \"_\" << "
		<< "xtcc_i"
		<< " << \"$\" << "
		//<< consolidated_for_loop_index_stack.back()
		<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
		<< ";\n"
		<< endl;
	//s << "temp_map_key2 << \"" << questionName_ << "\" << \"_\" << "
	//	<< "xtcc_i"
	//	<< ";\n";
	s << questionName_ << "_list.questionList[xtcc_i]->input_data = "
		<< questionName_ << "_scope_question_t[ temp_map_key.str()"
		<< "];\n";
	s << "}\n";

	s << "/* EXIT:AbstractQuestion::PrintRestoreMyPreviousIterationsData */" << endl;
}

std::string AbstractQuestion::PrintCodeSaveArrayQuestionNotInTheSameBlock(AbstractQuestion * save_array_quest)
{
	stringstream s;
	s << "/*"
		<< questionName_ << " and "
		<< save_array_quest->questionName_
		<< " :belong to different blocks "
		<< "*/"
		<< endl;
	s << "for(int32_t xtcc_i = 0; xtcc_i < ";
	for(int32_t i1 = 0; i1 < save_array_quest->for_bounds_stack.size(); ++i1) {
		BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
				save_array_quest->for_bounds_stack[i1]);
		if(bin_expr_ptr){
			AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
			ExpressionCompiledCode expr_code;
			rhs->PrintExpressionCode(expr_code);
			s << expr_code.code_bef_expr.str() /* should be empty */
				<< expr_code.code_expr.str();
			if(i1<save_array_quest->for_bounds_stack.size()-1) {
				s << "*";
			}
		} else {
			print_err(compiler_code_generation_error
				, "for loop index condition is not a binary expression"
				, 0, __LINE__, __FILE__);
		}
	}
	s << ";++xtcc_i){\n"
		<< "ostringstream map_key;\n"
		<< "map_key << \"" << questionName_ << "\""
		<< " << "
		<< "\"_\" << xtcc_i ";
	if (enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.size()>0) {
		s	<< "<< \"$\" << " << enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< ";" << endl;
	} else {
		s	<< ";\n";
	}
	s	<< save_array_quest->questionName_ << "_scope_question_t["
		<< "map_key.str()" << "] = "
		<< save_array_quest->questionName_ << "_list.questionList[xtcc_i]->input_data;\n"
		<< endl;
	s << "}\n";
	return s.str();
}

std::string AbstractQuestion::PrintCodeRestoreArrayQuestionNotInTheSameBlock(AbstractQuestion * restore_array_quest)
{
	stringstream s;
	s << "/*"
		<< questionName_ << " and "
		<< restore_array_quest->questionName_
		<< " :belong to different blocks "
		<< "*/"
		<< endl;

	s << "for(int32_t xtcc_i = 0; xtcc_i < ";
	for(int32_t i1 = 0; i1 < restore_array_quest->for_bounds_stack.size(); ++i1) {
		BinaryExpression * bin_expr_ptr = dynamic_cast<BinaryExpression*>(
				restore_array_quest->for_bounds_stack[i1]);
		if(bin_expr_ptr){
			AbstractExpression * rhs = bin_expr_ptr->rightOperand_;
			ExpressionCompiledCode expr_code;
			rhs->PrintExpressionCode(expr_code);
			s << expr_code.code_bef_expr.str() /* should be empty */
				<< expr_code.code_expr.str();
			if(i1<restore_array_quest->for_bounds_stack.size()-1) {
				s << "*";
			}
		} else {
			print_err(compiler_code_generation_error
				, "for loop index condition is not a binary expression"
				, 0, __LINE__, __FILE__);
		}
	}
	s << ";++xtcc_i){\n";
	s 	<< "ostringstream map_key;\n";
	s	<< "map_key << \"" << questionName_ << "\"";
	s	<< " << ";
	s	<< "\"_\" << xtcc_i ";
		//delete later
	if (enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.size()>0) {
		s	<< "<< \"$\" << " << enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
			<< ";" << endl;
	} else {
		s	<< ";\n";
	}

	// s	<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back();
	// s	<< ";" << endl;
	s	<< restore_array_quest->questionName_;
	s	<< "_list.questionList[xtcc_i]->input_data = ";
	s	<< restore_array_quest->questionName_ << "_scope_question_t[";
	s	<< "map_key.str()" << "];\n";
	s	<< endl;
	s << "}\n";
	return s.str();
}

//Wt::WString NamedStubQuestion::PrintSelectedAnswers()
string NamedStubQuestion::PrintSelectedAnswers()
{
	return string();
	//return Wt::WString();
}


//Wt::WString NamedStubQuestion::PrintSelectedAnswers(int code_index)
string NamedStubQuestion::PrintSelectedAnswers(int code_index)
{
	return string();
	//return Wt::WString();
}

//Wt::WString RangeQuestion::PrintSelectedAnswers()
string RangeQuestion::PrintSelectedAnswers()
{
	return string();
	//return Wt::WString();
}


//Wt::WString RangeQuestion::PrintSelectedAnswers(int code_index)
string RangeQuestion::PrintSelectedAnswers(int code_index)
{
	return string();
	//return Wt::WString();
}

// TextExpression::TextExpression(string text)
// 	: text_(text), nameExpr_(0)
// { }
// TextExpression::TextExpression(Unary2Expression * expr)
// 	: text_(), nameExpr_(expr)
// { }
// // for DummyArrayQuestion
// TextExpression::TextExpression()
// 	: text_(), nameExpr_(0)
// { }
//
void VideoQuestion:: GenerateCode(StatementCompiledCode &code)
{
	code.program_code << "/* START ======== VideoQuestion::GenerateCode code goes here */"
		<< endl;
	if (for_bounds_stack.size() == 0) {
		AbstractQuestion::PrintSetupBackJump(code);
		GenerateCodeSingleQuestion(code, false);
	}

	code.program_code << "/* END ======== VideoQuestion::GenerateCode code goes here */"
		<< endl;
	if (next_) {
		next_->GenerateCode(code);
	}
}

void VideoQuestion:: GenerateCodeSingleQuestion(StatementCompiledCode &code, bool array_mode)
{
	ostringstream quest_decl;
	code.program_code << "/* START ======== VideoQuestion::GenerateCodeSingleQuestion code goes here */"
		<< endl;
	quest_decl << "{\n";
	quest_decl << "vector<TextExpression *> text_expr_vec;\n";
	string q_title_code = PrintQuestionTitleCode (textExprVec_);
	quest_decl << q_title_code;

	if (array_mode)
		quest_decl << "VideoQuestion * " << questionName_;
	else
		quest_decl << questionName_;

	quest_decl
		<< " = new VideoQuestion("
		<< ((type_ == QUESTION_TYPE) ? "QUESTION_TYPE, " : "QUESTION_ARR_TYPE, " )
		<< lineNo_ << ","
		<< " string( \"" << questionName_ << "\")"
		<< ", text_expr_vec";

	if (q_type == video) {
		quest_decl << ", video" ;
	} else if (q_type == audio) {
		quest_decl << ", audio" ;
	} else if (q_type == image) {
		quest_decl << ", image" ;
	} else {
		quest_decl << " , trigger syntax error - unhanled type";
	}
	quest_decl
		<< ", QuestionAttributes(false, false)"
		;

	if (isStartOfBlock_) {
		quest_decl << ", true";
	} else {
		quest_decl << ", false";
	}

	quest_decl
		<< ", string(\"" << file_path << "\")"
		<< ");"
		<< endl;


	quest_decl << "}\n";

	if (for_bounds_stack.size() == 0) {
		// code.quest_defns << quest_decl.str();
		code.quest_defns << "/* VideoQuestion::GenerateCodeSingleQuestion */" << endl;
		code.quest_defns << "VideoQuestion * " << questionName_ << ";\n";
		code.quest_defns_init_code << quest_decl.str();
		code.array_quest_init_area << "question_list.push_back(" << questionName_
			<< ");"
			<< questionName_ << " -> setQuestionIndexNo(our_question_index_no);"
			<< endl;
		code.array_quest_init_area << "print_question_messages(" << questionName_ << ");\n";
		code.program_code
			<< "if ((" << questionName_ << "->isAnswered_ == false) || "
			<< "( (p_navigation_mode == NAVIGATE_NEXT && last_question_visited == 0) || (p_navigation_mode == NAVIGATE_NEXT && "
			<< questionName_
			<< "->questionNoIndex_ >  last_question_visited-> questionNoIndex_ )) ||"
			<< "( p_navigation_mode == NAVIGATE_PREVIOUS && (dynamic_cast<AbstractRuntimeQuestion*>("
			<< questionName_
			<< ") == p_jump_to_index)) )" << endl

			<< "{" << endl
			<< "last_question_visited = " << questionName_ << ";" << endl
			<< "fprintf(qscript_stdout, \"last_question_visited:" << questionName_ << "\\n\");\n"
			<< "\treturn " << questionName_ << ";" << endl
			<< "}"
			<< endl;
	}

	code.program_code << "/* END ======== VideoQuestion::GenerateCodeSingleQuestion code goes here */"
		<< endl;
}

#if 0
bool AbstractQuestion::VerifyResponse(user_response::UserResponseType user_resp)
{
	stringstream mesg; mesg << "user_resp: " << user_resp;
	// cout << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
	// 	<< mesg.str() << endl;
	if (user_resp == user_response::UserClearedData && question_attributes.isAllowBlank()) {
		// valid response if blanks are allowed but dont do isAnswered_ = true
		// because otherwise when visiting the questionnaire it will skip this
		// question and data entry will have an off by 1 error everytime they
		// are reviewing this question - since blank is a valid answer
		return true;
	} else if (user_resp == user_response::UserEnteredData) {
		return true;
	} else if (user_resp == user_response::UserEnteredNavigation
			&& user_navigation == NAVIGATE_PREVIOUS) {
		return true;
	} else if (user_resp == user_response::UserEnteredNavigation
			&& user_navigation == NAVIGATE_NEXT
			&& question_attributes.isAllowBlank() == false
			&& isAnswered_ == true) {
		return true;
	} else if (user_resp == user_response::UserEnteredNavigation
			&& user_navigation == NAVIGATE_NEXT
			&& question_attributes.isAllowBlank() == true) {
		return true;
	} else if (user_resp == user_response::UserSavedData && user_navigation == SAVE_DATA) {
		return true;
	} else {
		return false;
	}
}


#endif /* 0 */

void VideoQuestion::eval(/*qs_ncurses::*/WINDOW * question_window
			 , /*qs_ncurses::*/WINDOW* stub_list_window
			 , /*qs_ncurses::*/WINDOW* data_entry_window)
{ }

void VideoQuestion::WriteDataToDisk(ofstream& data_file)
{ }

string VideoQuestion::PrintSelectedAnswers()
{
	return string();
}

string VideoQuestion::PrintSelectedAnswers(int code_index)
{

	return string();
}

VideoQuestion::VideoQuestion(
		DataType this_stmt_type, int32_t line_number, string l_name
		, vector<TextExpression*> text_expr_vec, QuestionType l_q_type
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
		, QuestionAttributes  l_question_attributes
		, const string& path_to_media)
	:
	AbstractQuestion(this_stmt_type, line_number, l_name, text_expr_vec
			 , l_q_type, 1, INT32_TYPE /* dummy */
			 , l_enclosing_scope
			 , l_av_info, l_question_attributes),
	file_path (path_to_media)
{

}
