/*! \file
    \brief The "AbstractQuestion" statement classes of the qscript language
           are contained in this file. The AbstractQuestion classes are
	   required in the runtime as well as compile environment.
	   Hence they have been factored out to speed up compilation
	   and prevent unnecessary code from entering the runtime binary

 *  xtcc/xtcc/qscript/stubs/simple_compiler/AbstractQuestion.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009
 *	Neil Xavier D'Souza
 */

#ifndef qscript_question_h
#define qscript_question_h
#include <sys/types.h>
#include <iosfwd>
//#include <fstream>
#include <iostream>
#include <string>
#include "stmt.h"
#include "compiled_code.h"
#include "curses_namespace.h"
#include "qscript_debug.h"
#include "display_data.h"
#include "QuestionAttributes.h"
#include "UserResponse.h"

using std::ostringstream;
using std::ofstream;
struct named_range;
struct DummyArrayQuestion;


//! The AbstractQuestion pure virtual base class - inherits from AbstractStatement
struct AbstractQuestion: public AbstractStatement
{
	string questionName_;
	string questionText_;
	string questionDiskName_;
	QuestionType q_type;
	int32_t no_mpn;
	DataType dt;
	set<int32_t> input_data;
	//AbstractExpression * arr_sz;
	vector<AbstractExpression*> for_bounds_stack;
	vector<int32_t> loop_index_values;
	bool isAnswered_;
	bool isModified_;
	CompoundStatement * enclosingCompoundStatement_;
	vector <ActiveVariableInfo*> activeVarInfo_;
	DummyArrayQuestion * dummyArrayQuestion_;
	//! this variable should never be used in the compile time environment
	string currentResponse_;
	QuestionAttributes question_attributes;
	XtccSet mutexCodeList_;
	int maxCode_;
	bool isStartOfBlock_;
	//int nestLevel_;
	//! this is only called in the compile time environment
	AbstractQuestion(
		DataType l_type, int32_t l_no
		, int32_t l_nest_level, int32_t l_for_nest_level
		, string l_name, string l_text
		, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
		, vector<AbstractExpression*>& l_for_bounds_stack
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
		, QuestionAttributes  l_question_attributes
		, const XtccSet & p_mutexCodeList=XtccSet()
		);

	AbstractQuestion(
		DataType l_type, int32_t l_no
		, int32_t l_nest_level, int32_t l_for_nest_level
		, string l_name, string l_text
		, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);
	//! this is only called in the compile time environment
	AbstractQuestion(
		DataType l_type,int32_t l_no
		, int32_t l_nest_level, int32_t l_for_nest_level
		, string l_name, string l_text
		, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
		, QuestionAttributes  l_question_attributes
		, const XtccSet & p_mutexCodeList=XtccSet()
		);

	//! this is only called in the runtime environment
	AbstractQuestion(
		DataType l_type, int32_t l_no
		, int32_t l_nest_level, int32_t l_for_nest_level
		, string l_name, string l_text
		, QuestionType l_q_type, int32_t l_no_mpn , DataType l_dt
		, const vector<int32_t>& l_loop_index_values
		, DummyArrayQuestion * l_dummy_array
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);
	virtual ~AbstractQuestion();
//	virtual void GenerateCode(ostringstream & quest_defns
//			, ostringstream& program_code)=0;
	virtual void GenerateCode(StatementCompiledCode &code)=0;
	virtual void GenerateCodeSingleQuestion(StatementCompiledCode &code, bool array_mode)=0;
	virtual void Generate_ComputeFlatFileMap(StatementCompiledCode & code);
	virtual void eval(/*qs_ncurses::*/WINDOW * question_window
			  , /*qs_ncurses::*/WINDOW* stub_list_window
			  , /*qs_ncurses::*/WINDOW* data_entry_window
			  , WINDOW * error_msg_window)=0;
	virtual bool IsValid(int32_t value)=0;
	void print_q_type(string &s);
	void print_data_type(string &s);
	void init_arr(int32_t n, AbstractQuestion* q);
	virtual void WriteDataToDisk(ofstream & data_file, string time_stamp, string jno, int ser_no);
	string GetDataFileQuestionName();
	string GetResponseForDataFile();
	void PrintSetupBackJump(StatementCompiledCode &code);
	void SetupSimpleQuestionSave(StatementCompiledCode &code);
	void SetupSimpleQuestionRestore(StatementCompiledCode &code);
	void SetupArrayQuestionSave(StatementCompiledCode &code);
	void SetupArrayQuestionRestore(StatementCompiledCode &code);
	void PrintEvalArrayQuestion(StatementCompiledCode &code);
	const char * CurrentResponseToCharString();
	//virtual AbstractQuestion * IsAQuestionStatement()=0;
	virtual void GetQuestionNames(vector<string> & question_list
				      , AbstractStatement * endStatement)=0;
	virtual void GetQuestionsInBlock(
		vector<AbstractQuestion*> & question_list
		, AbstractStatement * stop_at);
	void PrintEvalAndNavigateCode(ostringstream & program_code);
	user_response::UserResponseType GetDataFromUser
		(WINDOW * question_window, WINDOW * stub_list_window,
		 WINDOW * data_entry_window, WINDOW * error_msg_window);

	bool VerifyData(string & err_mesg, string & re_arranged_buffer
				, int32_t &pos_1st_invalid_data, vector<int32_t> * data_ptr);
	bool VerifyResponse(user_response::UserResponseType user_resp);
	// void PrintArrayDeclarations(ostringstream & quest_defns);
	void PrintArrayDeclarations(StatementCompiledCode & code);
	//void PrintQuestionArrayInitialisation(
	//	StatementCompiledCode & code);
	std::string PrintCodeSaveArrayQuestionNotInTheSameBlock(AbstractQuestion * save_array_quest);
	std::string PrintCodeRestoreArrayQuestionNotInTheSameBlock(AbstractQuestion * restore_array_quest);
	string PrintSaveArrayQuestion(ActiveVariableInfo * av_info);
	string PrintRestoreArrayQuestion(ActiveVariableInfo * av_info);
	void PrintSaveMyPreviousIterationsData(StatementCompiledCode &code);
	void PrintRestoreMyPreviousIterationsData(StatementCompiledCode &code);
	friend bool IsInTheSameScopeAndLevel(AbstractQuestion *q1
					     , AbstractQuestion * q2);
	friend bool NotInTheSameBlock(AbstractQuestion *q1, AbstractQuestion * q2);
	friend bool IsAtAHigherNestLevelInTheSameBlock(AbstractQuestion *q1
						       , AbstractQuestion * q2);
	friend bool IsAtADeeperNestLevelInTheSameBlock(AbstractQuestion *q1
						       , AbstractQuestion * q2);
	bool QuestionIsInMyBlock(AbstractQuestion *q);
	void SaveQuestionsInMyBlockThatAreAfterMe(StatementCompiledCode & code);
	void RestoreQuestionsInMyBlockThatAreAfterMe(StatementCompiledCode & code);
	void PrintUserNavigation(ostringstream & program_code);
	void PrintUserNavigationArrayQuestion(ostringstream & program_code);
	int32_t GetMaxCode();
	bool VerifyQuestionIntegrity();
	private:
		AbstractQuestion& operator=(const AbstractQuestion&);
		AbstractQuestion (const AbstractQuestion&);
};



//! RangeQuestion range questions in the qscript language become object instantiations of this class.
/*!
  	Below is an example of a RangeQuestion  - the allowed codes are hard coded
	numbers -> (1,2,5-8)
		q2 "Q2. This is AbstractQuestion 2" mp (5) int32_t (1,2,5-8);
*/
struct RangeQuestion: public AbstractQuestion
{
	XtccSet * r_data;
	//vector <int32_t> stack_loop_index_values;
	//set<int32_t> displayData_;
	vector<display_data::DisplayDataUnit> displayData_;
	//! this is only called in the compile time environment
	RangeQuestion(
		DataType this_stmt_type, int32_t line_number
		, int32_t l_nest_level, int32_t l_for_nest_level
		, string l_name
		, string l_q_text, QuestionType l_q_type, int32_t l_no_mpn
		, DataType l_dt, XtccSet& l_r_data
		, vector<AbstractExpression*>& l_for_bounds_stack
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
		, QuestionAttributes  l_question_attributes
		, const XtccSet & p_mutexCodeList
		);
	//! this is only called in the runtime environment
	RangeQuestion(
		DataType this_stmt_type, int32_t line_number, string l_name
		, string l_q_text, QuestionType l_q_type, int32_t l_no_mpn
		, DataType l_dt, XtccSet& l_r_data
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);

	//! this is only called in the compile time environment
	RangeQuestion(
		DataType this_stmt_type, int32_t line_number
		, int32_t l_nest_level, int32_t l_for_nest_level
		, string l_name
		, string l_q_text, QuestionType l_q_type, int32_t l_no_mpn
		, DataType l_dt, XtccSet& l_r_data
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
		, QuestionAttributes  l_question_attributes
		, const XtccSet & p_mutexCodeList
		);
	//! this is only called in the runtime environment
	RangeQuestion(
		DataType this_stmt_type, int32_t line_number, string l_name
		, string l_q_text, QuestionType l_q_type, int32_t l_no_mpn
		, DataType l_dt, XtccSet& l_r_data
		, const vector<int32_t> & l_loop_index_values
		, DummyArrayQuestion * l_dummy_array
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);

	void GenerateCode(StatementCompiledCode &code);
	void GenerateCodeSingleQuestion(StatementCompiledCode &code, bool array_mode);
	virtual bool IsValid(int32_t value);
	//void eval();
	void eval(/*qs_ncurses::*/WINDOW * question_window
		  , /*qs_ncurses::*/WINDOW* stub_list_window
		  , /*qs_ncurses::*/WINDOW* data_entry_window
		  , WINDOW * error_msg_window
		  );
	void WriteDataToDisk(ofstream& data_file, string time_stamp, string jno, int ser_no);
	//AbstractQuestion*  IsAQuestionStatement(){
	//	return this;
	//}
	void  GetQuestionNames(vector<string> & question_list,
			       AbstractStatement* endStatement);

	~RangeQuestion();
	private:
		RangeQuestion& operator=(const RangeQuestion&);
		RangeQuestion (const RangeQuestion&);
};


//! NamedStubQuestion named  questions in the qscript language become object instantiations of this class.
/*!
  	Below is an example of a NamedStubQuestion - the allowed codes are a
	predefined name like "age" below

		q3 "Q3. Respondents age" sp int32_t age;
*/
class NamedStubQuestion: public AbstractQuestion
{
	public:
	string named_list;
	named_range * nr_ptr;
	vector<stub_pair> * stub_ptr;
	vector<display_data::DisplayDataUnit> displayData_;
	int currentPage_;
	int totPages_;
	// this is a stack of indices - start and stop for each page
	vector <pair<int,int> > pageIndices_;
	int stubStartYIndex_;
	//! this is only called in the compile time environment
	NamedStubQuestion(
		DataType this_stmt_type, int32_t line_number
		, int32_t l_nest_level, int32_t l_for_nest_level
		, string l_name
		, string l_q_text, QuestionType l_q_type, int32_t l_no_mpn
		, DataType l_dt, named_range * l_nr_ptr
		, vector<AbstractExpression*>& l_for_bounds_stack
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
		, QuestionAttributes  l_question_attributes
		);
	//! this is only called in the compile time environment
	NamedStubQuestion(
		DataType this_stmt_type, int32_t line_number
		, int32_t l_nest_level, int32_t l_for_nest_level
		, string l_name
		, string l_q_text, QuestionType l_q_type, int32_t l_no_mpn
		, DataType l_dt, named_range * l_nr_ptr
		, CompoundStatement * l_enclosing_scope
		, vector<ActiveVariableInfo* > l_av_info
		, QuestionAttributes  l_question_attributes
		);

	NamedStubQuestion(
		DataType this_stmt_type, int32_t line_number, string l_name
		, string l_q_text, QuestionType l_q_type, int32_t l_no_mpn
		//, DataType l_dt, vector<stub_pair> * l_stub_ptr
		, DataType l_dt, named_range * l_nr_ptr
		, vector<AbstractExpression*>& l_for_bounds_stack
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);
	NamedStubQuestion(
		DataType this_stmt_type, int32_t line_number
		, string l_name , string l_q_text
		, QuestionType l_q_type, int32_t l_no_mpn
		, DataType l_dt, named_range * l_nr_ptr
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);
	//! only called in the runtime environment
	NamedStubQuestion(
		DataType this_stmt_type, int32_t line_number, string l_name
		, string l_q_text, QuestionType l_q_type, int32_t l_no_mpn
		//, DataType l_dt, vector<stub_pair> * l_stub_ptr
		, DataType l_dt, named_range * l_nr_ptr
		, const vector<int32_t> & l_loop_index_values
		, DummyArrayQuestion * l_dummy_array
		, QuestionAttributes  l_question_attributes
		, bool l_isStartOfBlock
		);

	void GenerateCode(StatementCompiledCode &code);
	void GenerateCodeSingleQuestion(StatementCompiledCode &code, bool array_mode);
	virtual bool IsValid(int32_t value);
	//void eval();
	void eval(/*qs_ncurses::*/WINDOW * question_window
		  , /*qs_ncurses::*/WINDOW* stub_list_window
		  , /*qs_ncurses::*/WINDOW* data_entry_window
		  , WINDOW * error_msg_window
		  );
	void WriteDataToDisk(ofstream& data_file, string time_stamp, string jno, int ser_no);
	//AbstractQuestion* IsAQuestionStatement(){
	//	return this;
	//}
	void  GetQuestionNames(vector<string> & question_list
			       , AbstractStatement* endStatement);

	void DisplayStubsPage(/*qs_ncurses::*/WINDOW * question_window
			     , /*qs_ncurses::*/WINDOW* stub_list_window
			     , /*qs_ncurses::*/WINDOW* data_entry_window
			     , WINDOW * error_msg_window);
	void ComputeVisiblePages (/*qs_ncurses::*/WINDOW * question_window
				     , /*qs_ncurses::*/WINDOW* stub_list_window
				     , /*qs_ncurses::*/WINDOW* data_entry_window
				     , WINDOW * error_msg_window);

	private:
		NamedStubQuestion& operator=(const NamedStubQuestion&);
		NamedStubQuestion (const NamedStubQuestion&);
};

class DummyArrayQuestion: public AbstractQuestion{
	public:
	vector<int32_t> array_bounds;

	DummyArrayQuestion(string l_qno, 
			vector<int32_t> l_array_bounds);

	void WriteDataToDisk(ofstream& data_file, string time_stamp, string jno, int ser_no);
	//void eval(){}
	void eval(/*qs_ncurses::*/WINDOW * question_window
		  , /*qs_ncurses::*/WINDOW* stub_list_window
		  , /*qs_ncurses::*/WINDOW* data_entry_window
		  , WINDOW * error_msg_window);
	

	bool IsValid(int32_t value){ return false;}
	void GenerateCode(StatementCompiledCode &code){}
	void GenerateCodeSingleQuestion(StatementCompiledCode &code, bool array_mode){}
	void GetQuestionNames(vector<string> & question_list
			      , AbstractStatement* endStatement);

	private:
		DummyArrayQuestion& operator=(const DummyArrayQuestion&);
		DummyArrayQuestion (const DummyArrayQuestion&);
};


#endif /* qscript_question_h */
