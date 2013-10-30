#include <algorithm>
#include <iostream>
#include "question.h"
#include "named_range.h"
#include "utils.h"
#include "UserResponse.h"
#include "expr.h"

using namespace std;

int AbstractQuestion::nQuestions_ = 0 ;


namespace  qscript_parser {
	extern std::string globalActivePageName_;
}


#if 1
AbstractQuestion::AbstractQuestion(
	DataType l_type, int32_t l_no
	, int32_t l_nest_level, int32_t l_for_nest_level
	, string l_name, vector<TextExpression*> text_expr_vec
	, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
	, QuestionAttributes  l_question_attributes
	, bool l_isStartOfBlock
	)
	: AbstractStatement(l_type, l_no, l_nest_level, l_for_nest_level), questionName_(l_name)
	, textExprVec_(text_expr_vec)
	, questionDiskName_(l_name)
	, q_type(l_q_type)
	, no_mpn(l_no_mpn), dt(l_dt), input_data()
	, for_bounds_stack(0), loop_index_values(0)
	, isAnswered_(false), isModified_(false)
	, enclosingCompoundStatement_(0), activeVarInfo_(0)
	, dummyArrayQuestion_(0), currentResponse_()
	, question_attributes(l_question_attributes)
	  , mutexCodeList_()
	  , maxCode_(0)
	, isStartOfBlock_(l_isStartOfBlock)
	  , questionNoIndex_(++AbstractQuestion::nQuestions_)
	, pageName_(qscript_parser::globalActivePageName_)
{
	//if(enclosingCompoundStatement_ == 0){
	//	print_err(compiler_internal_error, " no enclosing CompoundStatement scope for question "
	//		, qscript_parser::line_no, __LINE__, __FILE__  );
	//}
}
#endif /* 0 */

AbstractQuestion::~AbstractQuestion()
{
	for (int i=0; i<activeVarInfo_.size(); ++i) {
		delete activeVarInfo_[i];
		activeVarInfo_[i]=0;
	}
}


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


RangeQuestion::~RangeQuestion()
{
	delete r_data ; r_data = 0;
}

DummyArrayQuestion::DummyArrayQuestion(string l_qno, vector<int32_t> l_array_bounds)
	: AbstractQuestion(QUESTION_TYPE, 0, 0, 0, l_qno
			//, string(l_qno + "_dummy")
			, vector<TextExpression*>()
			, spn, 0
			   , INT32_TYPE, QuestionAttributes(true, true), false /* isStartOfBlock_ does not matter i think for DummyArrayQuestion */)
	,  array_bounds(l_array_bounds)
	  
{ }

void DummyArrayQuestion::eval(/*qs_ncurses::*/WINDOW * question_window
		  , /*qs_ncurses::*/WINDOW* stub_list_window
		  , /*qs_ncurses::*/WINDOW* data_entry_window)
{ }


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


bool RangeQuestion::IsValid(int32_t value)
{
	return (r_data->exists(value))? true: false;
}


TextExpression::TextExpression(string text)
	: teType_(TextExpression::simple_text_type), 
	  text_(text), nameExpr_(0),
	  naPtr_(0), naIndex_(-1),
	  pipedQuestion_(0), questionIndexExpr_(0), codeIndex_(-1)
{ }

TextExpression::TextExpression(Unary2Expression * expr)
	: teType_(TextExpression::named_attribute_type), 
	  text_(), nameExpr_(expr),
	  naPtr_(0), naIndex_(-1),
	  pipedQuestion_(0), questionIndexExpr_(0), codeIndex_(-1)
{ }
// for DummyArrayQuestion
TextExpression::TextExpression()
	: teType_(TextExpression::simple_text_type), 
	  text_(), nameExpr_(0),
	  naPtr_(0), naIndex_(0),
	  pipedQuestion_(0), questionIndexExpr_(0), codeIndex_(-1)
{ }

TextExpression::TextExpression(named_attribute_list * na_ptr, int na_index)
	: teType_(TextExpression::named_attribute_type),
	  text_(), nameExpr_(0),
	  naPtr_(na_ptr), naIndex_(na_index),
	  pipedQuestion_(0), questionIndexExpr_(0), codeIndex_(-1)
{ }

TextExpression::TextExpression(AbstractQuestion * q, int code_index)
	: teType_(TextExpression::question_type),
	  text_(), nameExpr_(0),
	  naPtr_(0), naIndex_(0),
	  pipedQuestion_(q), questionIndexExpr_(0), codeIndex_ (code_index)
{ }

TextExpression::TextExpression (AbstractQuestion * q, AbstractExpression * expr)
	: teType_ (TextExpression::question_type), 
	  text_(), nameExpr_(0),
	  naPtr_ (0), naIndex_ (-1),
	  pipedQuestion_ (q), questionIndexExpr_ (expr), codeIndex_ (-1)
{ }

TextExpression::TextExpression (AbstractQuestion * q)
	: teType_ (TextExpression::question_type), 
	  text_(), nameExpr_(0),
	  naPtr_ (0), naIndex_ (-1),
	  pipedQuestion_ (q), questionIndexExpr_ (0), codeIndex_ (-1)
{ }



void DummyArrayQuestion::GetQuestionNames(vector<string> & question_list
			      , AbstractStatement* endStatement)
{
	if (this==endStatement)
		return;
	if (next_) {
		next_->GetQuestionNames(question_list, endStatement);
	}
}

void NamedStubQuestion::GetQuestionNames(vector<string> & question_list
			       , AbstractStatement* endStatement)
{
	if (qscript_debug::DEBUG_NamedStubQuestion) {
		std::cout << "NamedStubQuestion::GetQuestionNames" << std::endl;
	}
	if (this==endStatement)
		return;
	if (for_bounds_stack.size() == 0) {
		question_list.push_back(questionName_);
	} else {
		//std::stringstream s;
		//s << questionName_  << "_list.questionList["
		//<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
		//<< "]";
		//question_list.push_back(s.str());
		question_list.push_back(questionName_);
	}
	if (next_) {
		next_->GetQuestionNames(question_list, endStatement);
	}
}


void  RangeQuestion::GetQuestionNames(vector<string> & question_list,
			       AbstractStatement* endStatement)
{
	if (qscript_debug::DEBUG_RangeQuestion) {
		std::cout << "RangeQuestion::GetQuestionNames"
			  << std::endl;
	}
	if (this==endStatement)
		return;
	if (for_bounds_stack.size() == 0) {
		question_list.push_back(questionName_);
	} else {
		//std::stringstream s;
		//s << questionName_  << "_list.questionList["
		//<< enclosingCompoundStatement_->ConsolidatedForLoopIndexStack_.back()
		//<< "]";
		//question_list.push_back(s.str());
		question_list.push_back(questionName_);
	}
	if (next_) {
		next_->GetQuestionNames(question_list,endStatement);
	}
}

//Wt::WString DummyArrayQuestion::PrintSelectedAnswers()
string DummyArrayQuestion::PrintSelectedAnswers()
{
	return string();
	//return Wt::WString();
}


//Wt::WString DummyArrayQuestion::PrintSelectedAnswers(int code_index)
string DummyArrayQuestion::PrintSelectedAnswers(int code_index)
{
	return string();
	//return Wt::WString();
}
