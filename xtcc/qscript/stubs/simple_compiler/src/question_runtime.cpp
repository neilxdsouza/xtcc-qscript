#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include "question.h"
#include "named_range.h"
#include "qscript_readline.h"
#include "user_navigation.h"
#include "utils.h"

using namespace std;
//extern vector<int32_t> data;
extern UserNavigation user_navigation;
extern FILE * qscript_stdout;

void Print_DisplayDataUnitVector (WINDOW * stub_list_window, 
		vector<display_data::DisplayDataUnit> & disp_vec,
		int &xPos, int &yPos, int maxWinX);

	//! this is only called in the runtime environment
RangeQuestion::RangeQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, vector<TextExpression*> text_expr_vec, QuestionType l_q_type, int32_t l_no_mpn
	, DataType l_dt , XtccSet& l_r_data
	, QuestionAttributes  l_question_attributes
	, bool l_isStartOfBlock
	)
	: AbstractQuestion(this_stmt_type, line_number, 0, 0
			, l_name, text_expr_vec
			   , l_q_type, l_no_mpn, l_dt, l_question_attributes
			   , l_isStartOfBlock)
	, r_data(new XtccSet(l_r_data)), displayData_()
{ 
	maxCode_ = r_data->GetMax();
}

#if 1
AbstractQuestion::AbstractQuestion(
	DataType l_type, int32_t l_no
	, int32_t l_nest_level, int32_t l_for_nest_level
	, string l_name
	//, string l_text
	, vector<TextExpression*> text_expr_vec
	, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
	, QuestionAttributes  l_question_attributes
	, bool l_isStartOfBlock
	)
	: AbstractStatement(l_type, l_no, l_nest_level, l_for_nest_level)
	, questionName_(l_name)
	, textExprVec_ (text_expr_vec)
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
	//if(enclosingCompoundStatement_ == 0){
	//	print_err(compiler_internal_error, " no enclosing CompoundStatement scope for question "
	//		, 0, __LINE__, __FILE__  );
	//}
}
#endif /* 0 */


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

	//! this is only called from the runtime environment
RangeQuestion::RangeQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, vector<TextExpression*> text_expr_vec, QuestionType l_q_type
	, int32_t l_no_mpn, DataType l_dt,	XtccSet& l_r_data
	, const vector<int32_t> & l_loop_index_values
	, DummyArrayQuestion * l_dummy_array
	, QuestionAttributes  l_question_attributes
	, bool l_isStartOfBlock
	):
	AbstractQuestion(this_stmt_type, line_number, 0, 0
			, l_name, text_expr_vec
			, l_q_type, l_no_mpn, l_dt
			, l_loop_index_values, l_dummy_array
		, l_question_attributes, l_isStartOfBlock
		)
	, r_data(new XtccSet(l_r_data)), displayData_()
{ 
	maxCode_ = r_data->GetMax();
}

string AbstractQuestion::getNamedAttributeText()
{
	string question_text;
	for (int i=0; i<textExprVec_.size(); ++i)
	{
		//question_text += "<p>";
		if (textExprVec_[i]->teType_ == TextExpression::simple_text_type)
		{
			//stringstream mesg_id;
			//mesg_id << part_mesg_id.str() << "_" << i;
			//question_text += WString::tr(mesg_id.str().c_str());
			//question_text += textExprVec_[i]->text_;
		}
		else if (textExprVec_[i]->teType_ == TextExpression::named_attribute_type)
		{
			//stringstream named_attribute_key;
			//named_attribute_key << textExprVec_[i]->naPtr_->name;
			//named_attribute_key << "_" << textExprVec_[i]->naIndex_;
			//question_text += WString::tr(named_attribute_key.str().c_str());
			question_text += textExprVec_[i]->naPtr_->attribute[textExprVec_[i]->naIndex_];
		}
		else if (textExprVec_[i]->teType_ == TextExpression::question_type)
		{
			if (textExprVec_[i]->codeIndex_ != -1)
			{
				question_text += textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(textExprVec_[i]->codeIndex_);
			}
			else
			{
				question_text += textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers();
			}
		}
		//question_text += "</p>";
	}
	return question_text;
}

//void RangeQuestion::eval()
void RangeQuestion::eval(/*qs_ncurses::*/WINDOW * question_window
			 , /*qs_ncurses::*/WINDOW* stub_list_window
			 , /*qs_ncurses::*/WINDOW* data_entry_window
			 , WINDOW * error_msg_window)
{
	if (displayData_.begin() == displayData_.end()) {
		for(	set<int32_t>::iterator it = r_data->indiv.begin(),
			end = r_data->indiv.end()
				;
				it != end; ++it){
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
		//cout << questionText_ << endl << endl;
		cout << textExprVec_[0]->text_ << endl << endl;
		//for(	set<int32_t>::iterator it = displayData_.begin();
		//		it != displayData_.end(); ++it)
		for(	vector<display_data::DisplayDataUnit>::iterator it = displayData_.begin(),
				end = displayData_.end()
				;
				it != end; ++it)
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

			for(set<int32_t>::iterator iter = input_data.begin(),
				end = input_data.end()
					;
				iter != end; ++iter) {
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
		int32_t maxWinX, maxWinY;
		getmaxyx(data_entry_window, maxWinY, maxWinX);
#if 0
		for (int i=0; i<maxWinX; ++i) {
			mvwprintw(question_window, 1, i, " ");
			mvwprintw(question_window, 2, i, " ");
		}
		box(data_entry_window, 0, 0);
		redrawwin(data_entry_window);
		clearok(data_entry_window, TRUE);
		wclrtoeol(data_entry_window);
		wrefresh (data_entry_window);
		update_panels();
		doupdate();
#endif /* 0 */
		mvwprintw(question_window, 1, 1, "%s.", questionName_.c_str());
		wmove(data_entry_window, 1, 1);
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
	
		string question_text;
		for (int i=0; i<textExprVec_.size(); ++i)
		{
			question_text += "<p>";
			if (textExprVec_[i]->teType_ == TextExpression::simple_text_type)
			{
				//stringstream mesg_id;
				//mesg_id << part_mesg_id.str() << "_" << i;
				//question_text += WString::tr(mesg_id.str().c_str());
				question_text += textExprVec_[i]->text_;
			}
			else if (textExprVec_[i]->teType_ == TextExpression::named_attribute_type)
			{
				//stringstream named_attribute_key;
				//named_attribute_key << textExprVec_[i]->naPtr_->name;
				//named_attribute_key << "_" << textExprVec_[i]->naIndex_;
				//question_text += WString::tr(named_attribute_key.str().c_str());
				question_text += textExprVec_[i]->naPtr_->attribute[textExprVec_[i]->naIndex_];
			}
			else if (textExprVec_[i]->teType_ == TextExpression::question_type)
			{
				if (textExprVec_[i]->codeIndex_ != -1)
				{
					question_text += textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(textExprVec_[i]->codeIndex_);
				}
				else
				{
					question_text += textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers();
				}
			}
			question_text += "</p>";
		}
		mvwprintw(question_window, 1, len_qno+1, " %s", question_text.c_str() );

		//for (int i=1; i<textExprVec_.size(); ++i) {
		//	mvwprintw(question_window, 2+i, 1, " %s", textExprVec_[i]->text_.c_str() );
		//}	



		mvwprintw(data_entry_window, 1, 1, " ");
		wmove(data_entry_window, 1, 1);
		//wrefresh(question_window);
		update_panels();
		doupdate();

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
		/*
		for (vector<display_data::DisplayDataUnit>::iterator it = displayData_.begin();
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
		*/
		Print_DisplayDataUnitVector (stub_list_window, 
				displayData_, currXpos, currYpos, maxWinX);
		// mvwprintw(data_entry_window, 2, 1, "just before exit eval");

		//wrefresh(stub_list_window);
		wmove(data_entry_window, 1,1);
		update_panels();
		doupdate();
		//AbstractQuestion::GetDataFromUser(data_entry_window);
	}

	user_response::UserResponseType user_resp = 
		AbstractQuestion::GetDataFromUser
			(question_window, stub_list_window,
			 data_entry_window, error_msg_window);

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


// this is only called from the runtime
AbstractQuestion::AbstractQuestion(
	DataType l_type, int32_t l_no
	, int32_t l_nest_level, int32_t l_for_nest_level
	, string l_name
	, vector<TextExpression*> text_expr_vec
	, QuestionType l_q_type, int32_t l_no_mpn, DataType l_dt
	, const vector<int32_t>& l_loop_index_values
	, DummyArrayQuestion * l_dummy_array
	, QuestionAttributes  l_question_attributes
	, bool l_isStartOfBlock
	)
	: AbstractStatement(l_type, l_no, l_nest_level, l_for_nest_level)
	, questionName_(l_name)
	, textExprVec_(text_expr_vec), q_type(l_q_type)
	, no_mpn(l_no_mpn), dt(l_dt), input_data()
	, for_bounds_stack(0)
	, loop_index_values(l_loop_index_values)
	, isAnswered_(false), isModified_(false)
	, enclosingCompoundStatement_(0) // this is only used in the compile time environment
	, activeVarInfo_(0)
	, dummyArrayQuestion_(l_dummy_array), currentResponse_()
	, question_attributes(l_question_attributes)
	  , mutexCodeList_()
	  , maxCode_(0)
	  , isStartOfBlock_(l_isStartOfBlock)
{
	//for(int32_t i = 0; i < l_loop_index_values.size(); ++i){
	//	cout << "l_loop_index_values " << i << ":" << l_loop_index_values[i] << endl;
	//}
	stringstream s;
	s << questionName_;
	for (int i=0; i<loop_index_values.size(); ++i) {
		s << "$" << loop_index_values[i];
	}
	questionDiskName_ = s.str();
}

void NamedStubQuestion::MakeDisplaySummaryDataRanges()
{
	fprintf (qscript_stdout, "displayData_.begin == displayData_.end \n");
	vector<stub_pair> & vec= (nr_ptr->stubs);
	if (vec.size() == 0) {
		cerr << "runtime error: Impossible !!! stubs with no codes: "
			<< __LINE__ << ", " << __FILE__ << __PRETTY_FUNCTION__
			<< " question name: " << questionName_ << endl;
		exit(1);
	}
	int start_code = vec[0].code;
	int previous_code = start_code;
	int current_code = start_code;
	// so what's with start_code, previous_code and current_code ?
	// start_code -> start of interval
	// previous_code -> last code we visited in stubs
	// current_code -> the current code we are visiting in stubs
	for (int32_t i=0; i<vec.size(); ++i) {
		current_code = vec[i].code;
		fprintf (qscript_stdout, "current_code: %d, previous_code: %d\n", current_code, previous_code);
		if (current_code - previous_code == 0) {
			// 1st iteration thru the loop 
			// cant make any decision yet
		} else if (current_code - previous_code == 1) {
			// continuous range - just keep going along we are in an interval
		} else if (current_code - previous_code > 1) {
			if (start_code < previous_code) {
				displayData_.push_back(display_data::DisplayDataUnit(start_code, previous_code));
				fprintf (qscript_stdout, "> 1 pushed back pair: %d - %d\n", start_code, previous_code);
				start_code = current_code;
				previous_code = current_code;
			} else {
				displayData_.push_back(display_data::DisplayDataUnit(start_code));
				fprintf (qscript_stdout, "> 1 pushed back singleteon: %d\n", start_code);
				start_code = current_code;
				previous_code = current_code;
			}
		} else {
			// current_code - previous_code < 0
			if (start_code < previous_code) {
				displayData_.push_back(display_data::DisplayDataUnit(start_code, previous_code));
				fprintf (qscript_stdout, "< 0 pushed back pair: %d - %d\n", start_code, previous_code);
				start_code = current_code;
				previous_code = current_code;
			} else if (start_code == previous_code) {
				displayData_.push_back(display_data::DisplayDataUnit(start_code));
				fprintf (qscript_stdout, "< 0 pushed back singleteon: %d\n", start_code);
				start_code = current_code;
				previous_code = current_code;
			}
		}
		if (i > 0) {
			previous_code = current_code;
		}
		//displayData_.push_back(display_data::DisplayDataUnit(vec[i].code));
	}
	if (start_code < previous_code) {
		displayData_.push_back(display_data::DisplayDataUnit(start_code, previous_code));
		fprintf (qscript_stdout, "pushed back pair: %d - %d\n", start_code, previous_code);
		start_code = current_code;
		previous_code = current_code;
	} else {
		displayData_.push_back(display_data::DisplayDataUnit(start_code));
		fprintf (qscript_stdout, "pushed back singleteon: %d\n", start_code);
		start_code = current_code;
		previous_code = current_code;
	}
}

//void NamedStubQuestion::eval()
void NamedStubQuestion::eval(/*qs_ncurses::*/WINDOW * question_window
			     , /*qs_ncurses::*/WINDOW* stub_list_window
			     , /*qs_ncurses::*/WINDOW* data_entry_window
			     , WINDOW * error_msg_window)
{
	if (displayData_.begin() == displayData_.end()) {
		MakeDisplaySummaryDataRanges();
#if 0
		fprintf (qscript_stdout, "displayData_.begin == displayData_.end \n");
		vector<stub_pair> & vec= (nr_ptr->stubs);
		if (vec.size() == 0) {
			cerr << "runtime error: Impossible !!! stubs with no codes: "
				<< __LINE__ << ", " << __FILE__ << __PRETTY_FUNCTION__
				<< " question name: " << questionName_ << endl;
			exit(1);
		}
		int start_code = vec[0].code;
		int previous_code = start_code;
		int current_code = start_code;
		// so what's with start_code, previous_code and current_code ?
		// start_code -> start of interval
		// previous_code -> last code we visited in stubs
		// current_code -> the current code we are visiting in stubs
		for (int32_t i=0; i<vec.size(); ++i) {
			current_code = vec[i].code;
			fprintf (qscript_stdout, "current_code: %d, previous_code: %d\n", current_code, previous_code);
			if (current_code - previous_code == 0) {
				// 1st iteration thru the loop 
				// cant make any decision yet
			} else if (current_code - previous_code == 1) {
				// continuous range - just keep going along we are in an interval
			} else if (current_code - previous_code > 1) {
				if (start_code < previous_code) {
					displayData_.push_back(display_data::DisplayDataUnit(start_code, previous_code));
					fprintf (qscript_stdout, "> 1 pushed back pair: %d - %d\n", start_code, previous_code);
					start_code = current_code;
					previous_code = current_code;
				} else {
					displayData_.push_back(display_data::DisplayDataUnit(start_code));
					fprintf (qscript_stdout, "> 1 pushed back singleteon: %d\n", start_code);
					start_code = current_code;
					previous_code = current_code;
				}
			} else {
				// current_code - previous_code < 0
				if (start_code < previous_code) {
					displayData_.push_back(display_data::DisplayDataUnit(start_code, previous_code));
					fprintf (qscript_stdout, "< 0 pushed back pair: %d - %d\n", start_code, previous_code);
					start_code = current_code;
					previous_code = current_code;
				} else if (start_code == previous_code) {
					displayData_.push_back(display_data::DisplayDataUnit(start_code));
					fprintf (qscript_stdout, "< 0 pushed back singleteon: %d\n", start_code);
					start_code = current_code;
					previous_code = current_code;
				}
			}
			if (i > 0) {
				previous_code = current_code;
			}
			//displayData_.push_back(display_data::DisplayDataUnit(vec[i].code));
		}
		if (start_code < previous_code) {
			displayData_.push_back(display_data::DisplayDataUnit(start_code, previous_code));
			fprintf (qscript_stdout, "pushed back pair: %d - %d\n", start_code, previous_code);
			start_code = current_code;
			previous_code = current_code;
		} else {
			displayData_.push_back(display_data::DisplayDataUnit(start_code));
			fprintf (qscript_stdout, "pushed back singleteon: %d\n", start_code);
			start_code = current_code;
			previous_code = current_code;
		}
#endif /*  0 */
	}
	if (question_window  == 0 || stub_list_window  == 0 || data_entry_window  == 0) {
		cout << questionName_ << ".";
		if (loop_index_values.size()>0) {
			for(uint32_t i=0; i<loop_index_values.size(); ++i){
				cout << loop_index_values[i]+1 << ".";
			}
		}
		//cout << questionText_ << endl << endl;
		cout << "fix me: questionText_" << endl << endl;

		//cout << questionName_ << "." << questionText_ << endl << endl;
		//vector<stub_pair> vec= *stub_ptr;
		vector<stub_pair> & vec= (nr_ptr->stubs);
		for (uint32_t i = 0; i< vec.size(); ++i) {
			if( vec[i].mask)
				cout << vec[i].stub_text << ": " << vec[i].code << endl;
		}

		if (input_data.begin() != input_data.end()) {
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
		update_panels ();
		doupdate ();
		int32_t maxWinX, maxWinY;
		getmaxyx(data_entry_window, maxWinY, maxWinX);
#if 0
		for (int i=0; i<maxWinX; ++i) {
			mvwprintw(question_window, 1, i, " ");
			mvwprintw(question_window, 2, i, " ");
		}
		box(data_entry_window, 0, 0);
		redrawwin(data_entry_window);
		clearok(data_entry_window, TRUE);
		wclrtoeol(data_entry_window);
		wrefresh (data_entry_window);
		update_panels();
		doupdate();
#endif /*  0 */
		mvwprintw(question_window, 1, 1, "%s.", questionName_.c_str());
		int len_qno = questionName_.length()+2;
		if (loop_index_values.size() > 0) {
			for (uint32_t i=0; i < loop_index_values.size(); ++i) {
				//cout << loop_index_values[i]+1 << ".";
				mvwprintw(question_window, 1, len_qno, "%d.", loop_index_values[i]+1);
				if (loop_index_values[i] + 1 < 10) {
					len_qno += 1;
				} else if (loop_index_values[i] + 1 < 100) {
					len_qno += 2;
				} else if (loop_index_values[i] + 1 < 1000) {
					len_qno += 3;
				} else if (loop_index_values[i] + 1 < 10000) {
					len_qno += 4;
				}
				len_qno += 1; // for the "."
			}
		}
		//mvwprintw(question_window,1,1, "%s. %s", questionName_.c_str(), questionText_.c_str() );
		//wrefresh(question_window);
		//mvwprintw (question_window, 1, len_qno + 1, " %s", questionText_.c_str() );
		//mvwprintw(question_window, 1, len_qno+1, " %s", textExprVec_[0]->text_.c_str() );
		//for (int i=1; i<textExprVec_.size(); ++i) {
		//	mvwprintw(question_window, 2+i, 1, " %s", textExprVec_[i]->text_.c_str() );
		//}
	
		string question_text;
		for (int i=0; i<textExprVec_.size(); ++i)
		{
			question_text += "<p>";
			if (textExprVec_[i]->teType_ == TextExpression::simple_text_type)
			{
				//stringstream mesg_id;
				//mesg_id << part_mesg_id.str() << "_" << i;
				//question_text += WString::tr(mesg_id.str().c_str());
				question_text += textExprVec_[i]->text_;
			}
			else if (textExprVec_[i]->teType_ == TextExpression::named_attribute_type)
			{
				//stringstream named_attribute_key;
				//named_attribute_key << textExprVec_[i]->naPtr_->name;
				//named_attribute_key << "_" << textExprVec_[i]->naIndex_;
				//question_text += WString::tr(named_attribute_key.str().c_str());
				question_text += textExprVec_[i]->naPtr_->attribute[textExprVec_[i]->naIndex_];
			}
			else if (textExprVec_[i]->teType_ == TextExpression::question_type)
			{
				if (textExprVec_[i]->codeIndex_ != -1)
				{
					question_text += textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(textExprVec_[i]->codeIndex_);
				}
				else
				{
					question_text += textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers();
				}
			}
			question_text += "</p>";
		}
		mvwprintw(question_window, 1, len_qno+1, " %s", question_text.c_str() );

		//for (int i=1; i<textExprVec_.size(); ++i) {
		//	mvwprintw(question_window, 2+i, 1, " %s", textExprVec_[i]->text_.c_str() );
		//}	

		mvwprintw (data_entry_window, 1, 1, " ");
		wmove (data_entry_window, 1, 2);
		update_panels ();
		doupdate ();
		//int32_t maxWinX, maxWinY;
		//getmaxyx(data_entry_window, maxWinY, maxWinX);
		int32_t currXpos = 1, currYpos = 1;
		fprintf (qscript_stdout, "displayData_.size(): %d\n", displayData_.size());
		wclear (stub_list_window);
		Print_DisplayDataUnitVector (stub_list_window, displayData_, currXpos, currYpos, maxWinX);
		//getchar();
		++currYpos; currXpos = 1;

		vector<stub_pair> & vec= (nr_ptr->stubs);
		stubStartYIndex_ = currYpos;
		ComputeVisiblePages (question_window, stub_list_window,
					data_entry_window, error_msg_window);
		/* 
		if (totPages_ == 0) {
			int start_page_index = 0, end_page_index = 0;
			stubStartYIndex_ = currYpos;
			int y_pos_tracker = currYpos;
			for (uint32_t i = 0; i < vec.size(); ++i) {
				if (vec[i].mask) {
					++ y_pos_tracker;
					if (y_pos_tracker == maxWinY) {
						pageIndices_.push_back ( pair <int, int> (start_page_index, i) );
						start_page_index = i + 1;
						y_pos_tracker = 0;
					}
				}
			}
			if (start_page_index < vec.size())
				pageIndices_.push_back ( pair <int, int> (start_page_index, vec.size()-1) );
			//cout << "n Pages: " << pageIndices_.size() << endl;
			//for (int i=0; i < pageIndices_.size(); ++i) {
			//	cout << pageIndices_[i].first << ", "
			//		<< pageIndices_[i].second
			//		<< endl;
			//}
		}
		*/

		//for (uint32_t i = 0; i < vec.size(); ++i) 
		// this block below has become DisplayStubsPage
#if 0
		for (uint32_t i = pageIndices_[currentPage_].first; i <= pageIndices_[currentPage_].second; ++i) {
			if (vec[i].mask) {
				//cout << vec[i].stub_text << ": " << vec[i].code << endl;
				//mvwprintw(stub_list_window, currYpos, currXpos, "%s: %d ", vec[i].stub_text.c_str(), vec[i].code);
				set<int32_t>::iterator found = input_data.find(vec[i].code);
				if (found != input_data.end()) {
					wattroff(stub_list_window, COLOR_PAIR(3));
					wattron(stub_list_window, COLOR_PAIR(5));
					mvwprintw(stub_list_window, currYpos, currXpos , "%d :", vec[i].code);
					wattroff(stub_list_window, COLOR_PAIR(5));
					wattron(stub_list_window, COLOR_PAIR(3));
				} else {
					mvwprintw(stub_list_window, currYpos, currXpos , "%d :", vec[i].code);
				}
				mvwprintw(stub_list_window, currYpos, currXpos + 8, "%s", vec[i].stub_text.c_str());
				++currYpos;
				// this should not be necessary - the paging algo should already have calculated this
				//if (currYpos >= maxWinY) {
				//	break;
				//}
			}
		}
#endif /* 0   */
		DisplayStubsPage( question_window
			     ,  stub_list_window
			     ,  data_entry_window
			     ,  error_msg_window);

		//wrefresh(stub_list_window);
		wmove(data_entry_window, 1, 1);
		update_panels();
		doupdate();
		// AbstractQuestion::GetDataFromUser(data_entry_window);
	}
	user_response::UserResponseType user_resp = 
		AbstractQuestion::GetDataFromUser
			(question_window, stub_list_window,
			 data_entry_window, error_msg_window);

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
void NamedStubQuestion::ComputeVisiblePages (/*qs_ncurses::*/WINDOW * question_window
			     , /*qs_ncurses::*/WINDOW* stub_list_window
			     , /*qs_ncurses::*/WINDOW* data_entry_window
			     , WINDOW * error_msg_window)
{
	pageIndices_.clear();
	vector<stub_pair> & vec= (nr_ptr->stubs);
	int32_t maxWinX, maxWinY;
	getmaxyx(stub_list_window, maxWinY, maxWinX);
	//if (totPages_ == 0) {
		int start_page_index = 0, end_page_index = 0;
		//stubStartYIndex_ = currYpos;
		int y_pos_tracker = stubStartYIndex_;
		for (uint32_t i = 0; i < vec.size(); ++i) {
			if (vec[i].mask) {
				++ y_pos_tracker;
				if (y_pos_tracker == maxWinY - 1) {
					pageIndices_.push_back ( pair <int, int> (start_page_index, i) );
					start_page_index = i + 1;
					y_pos_tracker = stubStartYIndex_;
				}
			}
		}
		if (start_page_index < vec.size())
			pageIndices_.push_back ( pair <int, int> (start_page_index, vec.size()-1) );
		//cout << "n Pages: " << pageIndices_.size() << endl;
		//for (int i=0; i < pageIndices_.size(); ++i) {
		//	cout << pageIndices_[i].first << ", "
		//		<< pageIndices_[i].second
		//		<< endl;
		//}
	//}
}

void NamedStubQuestion::DisplayStubsPage(/*qs_ncurses::*/WINDOW * question_window
			     , /*qs_ncurses::*/WINDOW* stub_list_window
			     , /*qs_ncurses::*/WINDOW* data_entry_window
			     , WINDOW * error_msg_window)
{
	//fstream file_display_stubs_log("file_display_stubs.log", ios_base::out|ios_base::app);

	int32_t currXpos = 1, currYpos = stubStartYIndex_;
	
	int32_t maxWinX, maxWinY;
	getmaxyx(data_entry_window, maxWinY, maxWinX);
	vector<stub_pair> & vec= (nr_ptr->stubs);
	//wclear(stub_list_window);
	//for (int i=stubStartYIndex_; i < maxWinY; ++i) {
	//	for (int j = 1; j < maxWinX -1; ++j) {
	//		mvwaddch(stub_list_window, currYpos, currXpos , ' ');
	//	}
	//}
	//update_panels ();
	//doupdate ();
	for (int y = currYpos; y < maxWinY; ++y) {
		for (int x=1; x < maxWinX-1; ++x) {
			//mvwprintw (stub_list_window, y, x, " ");
			//cout << "reached here\n";
			mvwaddch(stub_list_window, y, x , ' ');
		}
	}
	//wmove(data_entry_window, 1, 1);
	update_panels ();
	doupdate ();
	//file_display_stubs_log << "currentPage_: " << currentPage_ << endl;
	for (uint32_t i = pageIndices_[currentPage_].first; i <= pageIndices_[currentPage_].second; ++i) {
		if (vec[i].mask) {
			//file_display_stubs_log << vec[i].stub_text << ": " << vec[i].code << endl;
			//mvwprintw(stub_list_window, currYpos, currXpos, "%s: %d ", vec[i].stub_text.c_str(), vec[i].code);
			set<int32_t>::iterator found = input_data.find(vec[i].code);
			if (found != input_data.end()) {
				wattroff(stub_list_window, COLOR_PAIR(3));
				wattron(stub_list_window, COLOR_PAIR(5));
				mvwprintw(stub_list_window, currYpos, currXpos , "%03d :", vec[i].code);
				wattroff(stub_list_window, COLOR_PAIR(5));
				wattron(stub_list_window, COLOR_PAIR(3));
			} else {
				mvwprintw(stub_list_window, currYpos, currXpos , "%03d :", vec[i].code);
			}
			mvwprintw(stub_list_window, currYpos, currXpos + 8, "%s", vec[i].stub_text.c_str());
			++currYpos;
			// this should not be necessary - the paging algo should already have calculated this
			//if (currYpos >= maxWinY) {
			//	break;
			//}
		}
	}
	if (currYpos < maxWinY) {
		char space = ' ';
		for (int y = currYpos; y < maxWinY; ++y) {
			for (int x = 1; x < maxWinX; ++x) {
				mvwaddch (stub_list_window, currYpos, currXpos , ' ');
				//cout << "reached here\n";
			}
		}
	}
	update_panels ();
	doupdate ();
	wmove(data_entry_window, 1, 1);
	update_panels ();
	doupdate ();
}

//! only called in the runtime environment
NamedStubQuestion::NamedStubQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, vector<TextExpression*> text_expr_vec
	, QuestionType l_q_type, int32_t l_no_mpn
	// , DataType l_dt , vector<stub_pair>* l_stub_ptr
	, DataType l_dt, named_range * l_nr_ptr
	, const vector<int32_t> & l_loop_index_values
	, DummyArrayQuestion * l_dummy_array
	, QuestionAttributes  l_question_attributes
	, bool l_isStartOfBlock
	):
	AbstractQuestion(this_stmt_type, line_number
			, 0, 0
			, l_name, text_expr_vec,
		l_q_type, l_no_mpn, l_dt, l_loop_index_values, l_dummy_array, l_question_attributes, l_isStartOfBlock
		)
	, named_list()
	, nr_ptr(l_nr_ptr), stub_ptr(0), displayData_(), currentPage_(0)
	, totPages_ (0), pageIndices_ (), stubStartYIndex_ (0)
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


user_response::UserResponseType AbstractQuestion::GetDataFromUser
	(WINDOW * question_window, WINDOW * stub_list_window,
	 WINDOW * data_entry_window, WINDOW * error_msg_window)
{
	// cout << __PRETTY_FUNCTION__ << ", " << __LINE__ << ", " << __FILE__ << endl;
	string err_mesg, re_arranged_buffer;
	int32_t pos_1st_invalid_data;
	if (data_entry_window == 0) {
		bool invalid_code = false;
		string prompt = "Enter Data:";
		vector <int> data;
		do {
ask_again:
			user_response::UserResponseType user_resp = read_data(prompt.c_str(), &data);
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
			invalid_code = VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data, &data);
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
		vector <int> data;
		do {
label_ask_again:
			user_response::UserResponseType user_resp 
				= read_data_from_window(
						question_window, stub_list_window,
						data_entry_window, error_msg_window, err_mesg.c_str()
					      //, (!invalid_code), re_arranged_buffer
					      , false, re_arranged_buffer
					      , pos_1st_invalid_data, this, &data);
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
				mvwprintw(error_msg_window, 1, 1, err_mesg.c_str());
				wmove(data_entry_window, 1, 1);
				goto label_ask_again;
			}
			if (!valid_input) {
				goto label_ask_again;
			}

			invalid_code = VerifyData(err_mesg, re_arranged_buffer, pos_1st_invalid_data, &data);


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
		wclear (error_msg_window);
		return user_response::UserEnteredData;
	}
}


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


// re_arranged_buffer will contain the data like this: valid_data invalid_data
bool AbstractQuestion::VerifyData(
	string & err_mesg, string & re_arranged_buffer
	, int32_t & pos_1st_invalid_data, vector<int32_t>* data_ptr)
{
	vector <int> & data = * data_ptr;
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
		//cout << "reached here: " << __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__ << endl;
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
				// cout << "mutexCodeList_ contains: " << data[i];
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


void AbstractQuestion::Generate_ComputeFlatFileMap(StatementCompiledCode & code)
{ }

void RangeQuestion::GenerateCode(StatementCompiledCode & code )
{ }

void NamedStubQuestion::GenerateCode(StatementCompiledCode &code)
{ }

void NamedStubQuestion::GenerateCodeSingleQuestion(StatementCompiledCode & code, bool array_mode)
{ }

void RangeQuestion::GenerateCodeSingleQuestion(StatementCompiledCode & code, bool array_mode)
{ }

void AbstractQuestion::WriteDataToDisk(ofstream& data_file, const string & time_stamp, const string & jno, int ser_no)
{


	//if (loop_index_values.size() > 0) {
	//	data_file << questionName_;
	//	for(int32_t i = 0; i< loop_index_values.size(); ++i){
	//		data_file << "$" << loop_index_values[i];
	//	}
	//} else {
	//	data_file << questionName_;
	//}
	data_file << GetDataFileQuestionName();
	data_file << ":";
	if (isAnswered_) {
		//for (set<int32_t>::iterator iter = input_data.begin();
		//		iter != input_data.end(); ++iter) {
		//	data_file << *iter << " ";
		//}
		data_file << GetResponseForDataFile();
	}
	data_file << endl;
	//stringstream mesg;
	//mesg << "I think this is the wrong place to clear - should be done at the end of main while loop in generated code, when user loads a new serial number";
	//LOG_MAINTAINER_MESSAGE(mesg.str());
	//input_data.clear();
	// clean file
	stringstream fname_clean_str;
	fname_clean_str << jno << "_clean_" << ser_no << "_" << time_stamp << ".dat";
	std::ofstream clean_data_file;
	clean_data_file.exceptions(std::ios::failbit | std::ios::badbit);
	clean_data_file.open(fname_clean_str.str().c_str(), ios_base::out| ios_base::app);
	//if (loop_index_values.size() > 0) {
	//	clean_data_file << questionName_;
	//	for(int32_t i = 0; i< loop_index_values.size(); ++i){
	//		clean_data_file << "$" << loop_index_values[i];
	//	}
	//} else {
	//	clean_data_file << questionName_;
	//}
	clean_data_file << GetDataFileQuestionName();
	clean_data_file << ":";
	if (isAnswered_) {
		//for (set<int32_t>::iterator iter = input_data.begin();
		//		iter != input_data.end(); ++iter) {
		//	clean_data_file << *iter << " ";
		//}
		clean_data_file << GetResponseForDataFile();
	}
	clean_data_file << endl;

	//
	//
	//
	// dirty file
	//
	stringstream fname_dirty_str;
	fname_dirty_str << jno << "_dirty_" << ser_no << "_" << time_stamp << ".dat";
	std::ofstream dirty_data_file;
	dirty_data_file.exceptions(std::ios::failbit | std::ios::badbit);
	dirty_data_file.open(fname_dirty_str.str().c_str(), ios_base::out| ios_base::app);
	//if (loop_index_values.size() > 0) {
	//	dirty_data_file << questionName_;
	//	for(int32_t i = 0; i< loop_index_values.size(); ++i){
	//		dirty_data_file << "$" << loop_index_values[i];
	//	}
	//} else {
	//	dirty_data_file << questionName_;
	//}
	dirty_data_file << GetDataFileQuestionName();
	dirty_data_file << ":";
	//for (set<int32_t>::iterator iter = input_data.begin();
	//		iter != input_data.end(); ++iter) {
	//	dirty_data_file << *iter << " ";
	//}
	dirty_data_file << GetResponseForDataFile();
	dirty_data_file << endl;
}

void NamedStubQuestion::WriteDataToDisk(ofstream& data_file, const string & time_stamp, const string & jno, int ser_no)
{
	AbstractQuestion::WriteDataToDisk(data_file, time_stamp, jno, ser_no);
#if 0
	if (loop_index_values.size() > 0) {
		data_file << questionName_;
		for(int32_t i = 0; i< loop_index_values.size(); ++i){
			data_file << "$" << loop_index_values[i];
		}
	} else {
		data_file << questionName_;
	}
	data_file << ":";
	if (isAnswered_) {
		for (set<int32_t>::iterator iter = input_data.begin();
				iter != input_data.end(); ++iter) {
			data_file << *iter << " ";
		}
	}
	data_file << endl;
	stringstream mesg;
	//mesg << "I think this is the wrong place to clear - should be done at the end of main while loop in generated code, when user loads a new serial number";
	//LOG_MAINTAINER_MESSAGE(mesg.str());
	//input_data.clear();
	// clean file
	stringstream fname_clean_str;
	fname_clean_str << jno << "_clean_" << ser_no << "_" << time_stamp << ".dat";
	std::ofstream clean_data_file;
	clean_data_file.exceptions(std::ios::failbit | std::ios::badbit);
	clean_data_file.open(fname_clean_str.str().c_str(), ios_base::out| ios_base::app);
	if (loop_index_values.size() > 0) {
		clean_data_file << questionName_;
		for(int32_t i = 0; i< loop_index_values.size(); ++i){
			clean_data_file << "$" << loop_index_values[i];
		}
	} else {
		clean_data_file << questionName_;
	}
	clean_data_file << ":";
	if (isAnswered_) {
		for (set<int32_t>::iterator iter = input_data.begin();
				iter != input_data.end(); ++iter) {
			clean_data_file << *iter << " ";
		}
	}
	clean_data_file << endl;

	//
	//
	//
	// dirty file
	//
	stringstream fname_dirty_str;
	fname_dirty_str << jno << "_dirty_" << ser_no << "_" << time_stamp << ".dat";
	std::ofstream dirty_data_file;
	dirty_data_file.exceptions(std::ios::failbit | std::ios::badbit);
	dirty_data_file.open(fname_dirty_str.str().c_str(), ios_base::out| ios_base::app);
	if (loop_index_values.size() > 0) {
		dirty_data_file << questionName_;
		for(int32_t i = 0; i< loop_index_values.size(); ++i){
			dirty_data_file << "$" << loop_index_values[i];
		}
	} else {
		dirty_data_file << questionName_;
	}
	dirty_data_file << ":";
	for (set<int32_t>::iterator iter = input_data.begin();
			iter != input_data.end(); ++iter) {
		dirty_data_file << *iter << " ";
	}
	dirty_data_file << endl;
#endif /*  0 */
}

void DummyArrayQuestion::WriteDataToDisk(ofstream& data_file, const string & time_stamp, const string & jno, int ser_no)
{
	data_file << questionName_ << " BOUNDS";
	for(int32_t i = 0; i < array_bounds.size(); ++i){
		data_file << " "<< array_bounds[i];
	}
	data_file << endl;

	stringstream fname_clean_str;
	fname_clean_str << jno << "_clean_" << ser_no << "_" << time_stamp << ".dat";
	std::ofstream clean_data_file;
	clean_data_file.exceptions(std::ios::failbit | std::ios::badbit);
	clean_data_file.open(fname_clean_str.str().c_str(), ios_base::out| ios_base::app);
	clean_data_file << questionName_ << " BOUNDS";
	for(int32_t i = 0; i < array_bounds.size(); ++i){
		clean_data_file << " "<< array_bounds[i];
	}
	clean_data_file << endl;

	stringstream fname_dirty_str;
	fname_dirty_str << jno << "_dirty_" << ser_no << "_" << time_stamp << ".dat";
	std::ofstream dirty_data_file;
	dirty_data_file.exceptions(std::ios::failbit | std::ios::badbit);
	dirty_data_file.open(fname_dirty_str.str().c_str(), ios_base::out| ios_base::app);
	dirty_data_file << questionName_ << " BOUNDS";
	for(int32_t i = 0; i < array_bounds.size(); ++i){
		dirty_data_file << " "<< array_bounds[i];
	}
	dirty_data_file << endl;
}

void RangeQuestion::WriteDataToDisk(ofstream& data_file, const string & time_stamp, const string & jno, int ser_no)
{
	AbstractQuestion::WriteDataToDisk(data_file, time_stamp, jno, ser_no);
#if 0
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
#endif /* 0 */
}


NamedStubQuestion::NamedStubQuestion(
	DataType this_stmt_type, int32_t line_number
	, string l_name, vector<TextExpression*> text_expr_vec
	, QuestionType l_q_type, int32_t l_no_mpn
	, DataType l_dt, named_range * l_nr_ptr
	, QuestionAttributes  l_question_attributes
	, bool l_isStartOfBlock
	):
	AbstractQuestion(this_stmt_type, line_number, 0, 0
			 , l_name, text_expr_vec
			 , l_q_type, l_no_mpn, l_dt, l_question_attributes
			 , l_isStartOfBlock)
	, named_list()
	, nr_ptr(l_nr_ptr), stub_ptr(0), displayData_(), currentPage_(0)
	, totPages_ (0), pageIndices_ (), stubStartYIndex_ (0)
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

// a question can lose integrity because of modification to a previous question

bool AbstractQuestion::VerifyQuestionIntegrity()
{
	bool has_integrity = true;

	for (set<int32_t>::iterator inp_data_iter = input_data.begin(),
			end = input_data.end()
			;
			inp_data_iter != end; ++inp_data_iter) {
		bool invalid_code = !IsValid(*inp_data_iter);
		if (invalid_code) {
			has_integrity = false;
			break;
		}
	}
	return has_integrity;
}

void Print_DisplayDataUnitVector(WINDOW * stub_list_window, 
		vector<display_data::DisplayDataUnit> & disp_vec,
		int &xPos, int &yPos, int maxWinX)
{
	using display_data::DisplayDataUnit;
	int loop_count = 0;
	for (vector<DisplayDataUnit>::iterator it = disp_vec.begin();
				it != disp_vec.end(); ++it)
	{
		//cout << *it << endl;
		stringstream s;
		fprintf (qscript_stdout, "Print_DisplayDataUnitVector: loop_count: %d\n", loop_count++);

		if ( (*it).displayDataType_ == display_data::single_element) {
			s << (*it).startOfRangeOrSingle_ << ",";
			fprintf (qscript_stdout, "Print_DisplayDataUnitVector: startOfRangeOrSingle_: %d\n"
					, (*it).startOfRangeOrSingle_);
		} else if ( (*it).displayDataType_ == display_data::range_element) {
			s << (*it).startOfRangeOrSingle_ << " - " << (*it).endOfRange_ << endl;
			fprintf (qscript_stdout, "Print_DisplayDataUnitVector: startOfRangeOrSingle_: %d to %d\n"
					, (*it).startOfRangeOrSingle_, (*it).endOfRange_);
		}
		if (xPos + s.str().length() > maxWinX) {
			xPos =1, ++yPos;
		} 
		mvwprintw(stub_list_window, yPos, xPos, "%s", s.str().c_str());
		xPos += s.str().length() + 1;
	}
	//wmove(data_entry_window, 1, 1);
	
	update_panels();
	doupdate();
}

string AbstractQuestion::GetDataFileQuestionName()
{
	stringstream disk_question_name;
	if (loop_index_values.size() > 0) {
		disk_question_name << questionName_;
		for(int32_t i = 0; i< loop_index_values.size(); ++i){
			disk_question_name << "$" << loop_index_values[i];
		}
	} else {
		disk_question_name << questionName_;
	}
	return disk_question_name.str();
}

// Note to myself: when i add floating questions 
// will need to extract this by the type in the question
string AbstractQuestion::GetResponseForDataFile()
{
	stringstream question_response;
	for (set<int32_t>::iterator iter = input_data.begin(),
			end = input_data.end()
			;
			iter != end; ++iter) {
		question_response << *iter << " ";
	}
	return question_response.str();
}


std::string NamedStubQuestion::PrintSelectedAnswers()
{
	//return string("hello");
	//stringstream select_answers_text;
	std::string select_answers_text;
	bool first_time = true;
	for (set<int32_t>::iterator inp_data_iter = input_data.begin(),
			end = input_data.end()
			;
			inp_data_iter != end; ++inp_data_iter) {
		stringstream mesg_key;
		mesg_key << nr_ptr->name << "_" << *inp_data_iter - 1;
		if (first_time) {
			//select_answers_text << nr_ptr->stubs[*inp_data_iter-1].stub_text;
			cout << "searching for : " << mesg_key.str() << endl;
			select_answers_text += nr_ptr->stubs[*inp_data_iter-1].stub_text;
			first_time = false;
		} else {
			//select_answers_text << ", " << nr_ptr->stubs[*inp_data_iter-1].stub_text ;
			cout << "searching for : " << mesg_key.str() << endl;
			select_answers_text += std::string(", ") +  nr_ptr->stubs[*inp_data_iter-1].stub_text;
		}
	}
	//select_answers_text << nr_ptr->stubs[codeIndex_].stub_text;
	//return select_answers_text.str();
	return select_answers_text;
}


std::string NamedStubQuestion::PrintSelectedAnswers(int code_index)
{
	//return string("hello");
	std::string select_answers_text;
	bool first_time = true;
	//for (set<int32_t>::iterator inp_data_iter = input_data.begin();
	//		inp_data_iter != input_data.end(); ++inp_data_iter) {
	//	if (first_time) {
	//		select_answers_text << nr_ptr->stubs[*inp_data_iter-1].stub_text;
	//		first_time = false;
	//	} else {
	//		select_answers_text << ", " << nr_ptr->stubs[*inp_data_iter-1].stub_text ;
	//	}
	//}
	stringstream mesg_key;
	mesg_key << nr_ptr->name << "_" << code_index ;
	return nr_ptr->stubs[code_index].stub_text;
	//select_answers_text << WString::tr(mesg_key.str());
	//return select_answers_text.str();
	//return std::string::tr(mesg_key.str());
}


std::string RangeQuestion::PrintSelectedAnswers()
{
	return std::string("hello");
}


std::string RangeQuestion::PrintSelectedAnswers (int code_index)
{
	return std::string("hello");
}
