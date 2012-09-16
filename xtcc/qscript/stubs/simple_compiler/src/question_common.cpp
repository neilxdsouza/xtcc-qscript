#include <algorithm>
#include <iostream>
#include "question.h"
#include "named_range.h"
#include "utils.h"
#include "UserResponse.h"
#include "expr.h"

using namespace std;

namespace qscript_parser {

	extern int32_t line_no;
}


#if 0
AbstractQuestion::AbstractQuestion(
	DataType l_type, int32_t l_no, string l_name, string l_text
	, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
	, QuestionAttributes  l_question_attributes
	, bool l_isStartOfBlock
	)
	: AbstractStatement(l_type, l_no), questionName_(l_name)
	, questionText_(l_text)
	, questionDiskName_(l_name)
	, q_type(l_q_type)
	, no_mpn(l_no_mpn), dt(l_dt), input_data()
	, for_bounds_stack(0), loop_index_values(0)
	, isAnswered_(false), isModified_(false)
	, enclosingCompoundStatement_(0), activeVarInfo_(0)
	, dummyArrayQuestion_(0), currentResponse_()
	, question_attributes(l_question_attributes)
	  , mutexCodeList_()
	  , maxCode_(0), isStartOfBlock_(l_isStartOfBlock)
{
	//cout << "creating AbstractQuestion: " << questionName_ << endl;
	if(enclosingCompoundStatement_ == 0){
		print_err(compiler_internal_error, " no enclosing CompoundStatement scope for question "
			, qscript_parser::line_no, __LINE__, __FILE__  );
	}
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
			, vector <TextExpression*> () //string(l_qno + "_dummy")
			, spn, 0
			   , INT32_TYPE, QuestionAttributes(true, true), false /* isStartOfBlock_ does not matter i think for DummyArrayQuestion */)
	,  array_bounds(l_array_bounds)
{ 
	TextExpression * t_expr = new TextExpression(l_qno + string("dummy"));
	textExprVec_.push_back (t_expr);
}

void DummyArrayQuestion::eval(/*qs_ncurses::*/WINDOW * question_window
		  , /*qs_ncurses::*/WINDOW* stub_list_window
		  , /*qs_ncurses::*/WINDOW* data_entry_window
		  , WINDOW * error_msg_window)
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

// Used in runtime mode
TextExpression::TextExpression(AbstractQuestion * q, int code_index)
	: teType_(TextExpression::question_type),
	  text_(), nameExpr_(0),
	  naPtr_(0), naIndex_(0),
	  pipedQuestion_(q), questionIndexExpr_(0), codeIndex_ (code_index)
{ }


// Used in compilation mode
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


std::string DummyArrayQuestion::PrintSelectedAnswers()
{
	return std::string();
}


std::string DummyArrayQuestion::PrintSelectedAnswers(int code_index)
{
	return std::string();
}

// Will be called in the runtime mode - 
string AbstractQuestion::AxPrepareQuestionTitleXtcc()
{
	stringstream quest_decl;
	for (int i=0; i < textExprVec_.size(); ++i) {
		if (textExprVec_[i]->teType_ == TextExpression::simple_text_type) { 
			quest_decl 
				<< textExprVec_[i]->text_
				;
		} else if (textExprVec_[i]->teType_ == TextExpression::question_type) {
			// since we are called in runtime env
			// questionIndexExpr_ will be null - instead codeIndex_ will be active
			// if (textExprVec_[i]->questionIndexExpr_ ) {
				//ExpressionCompiledCode expr_code;
				//textExprVec_[i]->questionIndexExpr_->PrintExpressionCode(expr_code);
				//quest_decl << "text_expr_vec.push_back( new TextExpression(" 
				//		<< textExprVec_[i]->pipedQuestion_->questionName_
				//		<< ", "
				//		<< expr_code.code_expr.str()
				//		<< ") ); /*  -NxD- */\n";
			if (textExprVec_[i]->codeIndex_ != -1) {
				quest_decl << textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(textExprVec_[i]->codeIndex_);
			} else {
				quest_decl << textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers();
			}
			//} else {
			//	quest_decl << "text_expr_vec.push_back( new TextExpression(" 
			//			<< textExprVec_[i]->pipedQuestion_->questionName_
			//			<< ") ); /* :::  -NxD- */\n";
			//}

#if 0
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
#endif /*  0 */
		} else if (textExprVec_[i]->teType_ == TextExpression::named_attribute_type) {
			quest_decl << textExprVec_[i]->naPtr_->attribute[textExprVec_[i]->naIndex_];
		} else {
			ExpressionCompiledCode expr_code;
			textExprVec_[i]->nameExpr_->PrintExpressionCode(expr_code);
			quest_decl << "text_expr_vec.push_back(new TextExpression("
				<< expr_code.code_expr.str()
				<< "));\n";
		}
	}
	return quest_decl.str();
}

string AbstractQuestion::AxPrepareQuestionTitleSPSS()
{
	stringstream quest_decl;
	for (int i=0; i < textExprVec_.size(); ++i) {
		if (textExprVec_[i]->teType_ == TextExpression::simple_text_type) { 
			quest_decl 
				<< textExprVec_[i]->text_
				;
		} else if (textExprVec_[i]->teType_ == TextExpression::question_type) {
			// if (textExprVec_[i]->questionIndexExpr_ ) {
				//ExpressionCompiledCode expr_code;
				//textExprVec_[i]->questionIndexExpr_->PrintExpressionCode(expr_code);
				//quest_decl << "text_expr_vec.push_back( new TextExpression(" 
				//		<< textExprVec_[i]->pipedQuestion_->questionName_
				//		<< ", "
				//		<< expr_code.code_expr.str()
				//		<< ") ); /*  -NxD- */\n";
				if (textExprVec_[i]->codeIndex_ != -1)
				{
					quest_decl << textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(textExprVec_[i]->codeIndex_);
				}
				else
				{
					quest_decl << textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers();
				}
			//} else {
			//	quest_decl << "text_expr_vec.push_back( new TextExpression(" 
			//			<< textExprVec_[i]->pipedQuestion_->questionName_
			//			<< ") ); /* :::  -NxD- */\n";
			//}
		} else if (textExprVec_[i]->teType_ == TextExpression::named_attribute_type) {
			quest_decl << textExprVec_[i]->naPtr_->attribute[textExprVec_[i]->naIndex_];
		} else {
			ExpressionCompiledCode expr_code;
			textExprVec_[i]->nameExpr_->PrintExpressionCode(expr_code);
			quest_decl << "text_expr_vec.push_back(new TextExpression("
				<< expr_code.code_expr.str()
				<< "));\n";
		}
	}
	return quest_decl.str();
}

string AbstractQuestion::AxPrepareQuestionTitle()
{
	stringstream quest_decl;
	for (int i=0; i < textExprVec_.size(); ++i) {
		if (textExprVec_[i]->teType_ == TextExpression::simple_text_type) { 
			quest_decl 
				<< textExprVec_[i]->text_
				;
		} else if (textExprVec_[i]->teType_ == TextExpression::question_type) {
			//if (textExprVec_[i]->questionIndexExpr_ ) {
			//	ExpressionCompiledCode expr_code;
			//	textExprVec_[i]->questionIndexExpr_->PrintExpressionCode(expr_code);
			//	quest_decl << "text_expr_vec.push_back( new TextExpression(" 
			//			<< textExprVec_[i]->pipedQuestion_->questionName_
			//			<< ", "
			//			<< expr_code.code_expr.str()
			//			<< ") ); /*  -NxD- */\n";
			//} else {
			//	quest_decl << "text_expr_vec.push_back( new TextExpression(" 
			//			<< textExprVec_[i]->pipedQuestion_->questionName_
			//			<< ") ); /*  -NxD- */\n";
			//}
		} else {
			//ExpressionCompiledCode expr_code;
			//textExprVec_[i]->nameExpr_->PrintExpressionCode(expr_code);
			//quest_decl << "text_expr_vec.push_back(new TextExpression("
			//	<< expr_code.code_expr.str()
			//	<< "));\n";
		}
	}
	return quest_decl.str();
}

string AbstractQuestion::PrepareQuestionTitle()
{
	stringstream quest_decl;
	quest_decl << "vector<TextExpression *> text_expr_vec;\n";
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
	return quest_decl.str();
}
