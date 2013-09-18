/*
 * =====================================================================================
 *
 *       Filename:  question_wt_runtime.cpp
 *
 *    Description:  wx Widgets GUI display for qscript runtime
 *
 *        Version:  1.0
 *        Created:  27-may-2013
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Xavier D'Souza
 *        Company:
 *
 * =====================================================================================
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <locale.h>
#include <libintl.h>
#include <map>
#include <vector>
#include <dirent.h>
#include <signal.h>
#include <Wt/WImage>

#include "question_gtk2_runtime.h"
#include "question.h"
#include "named_range.h"
#include "question_disk_data.h"
#include "qscript_data.hpp"
#include "qscript_lib.h"
#include "AbstractQuestionnaire.h"
#include "question_wt_runtime.h"

extern string jno;

using std::vector;
using std::string;
using namespace Wt;
vector <string> vec_language;


struct TheQuestionnaire * make_questionnaire ();
vector <Session*> wt_sessions;

void QuestionnaireApplication::setLanguage(const std::string lang)
{
	bool haveLang = false;

	for (unsigned i = 0; i < languageSelects_.size(); ++i) {
		WText *t = languageSelects_[i];

		// prefix match, e.g. en matches en-us.
		bool isLang = lang.find(narrow(t->text().value())) == 0;
		t->setStyleClass(isLang ? L"langcurrent" : L"lang");

		haveLang = haveLang || isLang;
	}

	if (!haveLang) {
		languageSelects_[0]->setStyleClass(L"langcurrent");
		WApplication::instance()
			->setLocale(narrow(languageSelects_[0]->text().value()));
	} else
		WApplication::instance()->setLocale(lang);
}


void QuestionnaireApplication::changeLanguage()
{
	WText *t = (WText *)sender();
	setLanguage(narrow(t->text().value()));
}


QuestionnaireApplication::QuestionnaireApplication (const WEnvironment &env)
	: WApplication(env),
	currentForm_(0), formContainer_(0), flagSerialPageRemoved_(false),
	wtxt_err_mesg_(0)
{
	messageResourceBundle().use(WApplication::appRoot() + jno);
	useStyleSheet(string(jno + string("-qscript.css")).c_str());

	serialPage_ = new WContainerWidget(0);
	setTitle("QuestionnaireApplication");
	WCssDecorationStyle langStyle;
	langStyle.font().setSize(WFont::Smaller);
	langStyle.setCursor(PointingHandCursor);
	langStyle.setForegroundColor(blue);
	langStyle.setTextDecoration(WCssDecorationStyle::Underline);
	this->styleSheet().addRule(".lang", langStyle);
	langStyle.setCursor(ArrowCursor);
	langStyle.font().setWeight(WFont::Bold);
	this->styleSheet().addRule(".langcurrent", langStyle);
	langStyle.setForegroundColor(WColor(100, 0, 200, 100));
	langStyle.setCursor(IBeamCursor);
	langStyle.font().setWeight(WFont::Bold);
	langStyle.font().setSize(WFont::XLarge);
	this->styleSheet().addRule(".langtitle", langStyle);
	// warning the statement below modifies the global variable
	//load_languages_available(vec_language);
	WContainerWidget *langLayout = new WContainerWidget();
	langLayout->setStyleClass("qscript-header");
	langLayout->setContentAlignment(AlignRight);
	WText * lang_title = new WText(WString::tr("language"), langLayout);
	lang_title->setStyleClass(L"langtitle");
	for (int i = 0; i < vec_language.size(); ++i) {
		WText *t = new WText(widen(vec_language[i]), langLayout);
		t->setMargin(5);
		t->clicked().connect(this, &QuestionnaireApplication::changeLanguage);
		languageSelects_.push_back(t);
	}
	setLanguage("hn");
	WText * txt_software_info = new WText(WString::tr("qscript_info"), serialPage_);
	WPushButton *b = new WPushButton("Click to start survey", serialPage_); // create a button
	b->setMargin(5, Left);                                 // add 5 pixels margin
	serialPage_->addWidget(new WBreak());                       // insert a line break
	//b->clicked().connect(this, &QuestionnaireApplication::ValidateSerialNo);
	b->clicked().connect(this, &QuestionnaireApplication::ValidateSerialNo);

	wt_SerialNo_ = new WText(serialPage_);
	wt_SerialNo_->setText("Serial No: ");
	wt_lastQuestionVisited_ = new WText(serialPage_);
	le_SerialNo_ = new WLineEdit(serialPage_);

	wt_debug_ = new WText(serialPage_);
	formContainer_ = new WContainerWidget(root());
	formContainer_->addWidget(serialPage_);
	formContainer_->addWidget(langLayout);
	string sess_id = sessionId();
	this_users_session = new Session();
	strcpy (this_users_session->sid, sess_id.c_str());
	wt_sessions.push_back(this_users_session);
}

Wt::WServer server;
Wt::WApplication * createApplication(const Wt::WEnvironment &env)
{
	//return new QuestionnaireApplication (env);
	Wt::WApplication * ptr =  new QuestionnaireApplication (env);
	//cout << "Sizeof (WApplication): " << sizeof (*ptr) << endl;
	return ptr;
}

// warning modifies the input variable
void load_languages_available(vector<string> & vec_language)
{
	cout
		<< "Enter: "
		<< __PRETTY_FUNCTION__ << ": vec_language.size(): " << vec_language.size()
		<< endl;
	DIR * directory_ptr = opendir(".");
	vec_language.push_back("en");
	struct dirent *directory_entry = readdir(directory_ptr);
	while (directory_entry) {
		string dir_entry_name(directory_entry->d_name);
		int len_entry = dir_entry_name.length();
		if (len_entry > 4 &&
				dir_entry_name[len_entry - 1] == 'l' &&
				dir_entry_name[len_entry - 2] == 'm' &&
				dir_entry_name[len_entry - 3] == 'x' &&
				dir_entry_name[len_entry - 4] == '.' ) {
			// the names we are looking for are of the form
			// jno + "[a-z][a-z].xml"
			bool is_our_file = true;
			if (len_entry != jno.length() + 7) {
				is_our_file = false;
				// the above doesnt matter actually,
				// continue takes us back to the top
				goto read_another_entry;
			} else {
				// possibly what we are looking for
				//
				for (int i = 0; i < jno.length(); ++i) {
					if (!(jno[i] == dir_entry_name[i])) {
						// cannot be our data file
						is_our_file = false;
						goto read_another_entry;
					}
				}
				char first_letter = dir_entry_name[jno.length() + 1];
				if (! isalpha (first_letter)) {
					is_our_file = false;
					goto read_another_entry;
				}
				char second_letter = dir_entry_name[jno.length() + 2];
				if (! isalpha (second_letter)) {
					is_our_file = false;
					goto read_another_entry;
				}
				string a_language;
				a_language.push_back(first_letter);
				a_language.push_back(second_letter);
				vec_language.push_back(a_language);
				cout << "found an language traslation file: "
					<< dir_entry_name << endl;
			}
		}
read_another_entry:
		directory_entry = readdir(directory_ptr);
	}
	closedir(directory_ptr);
	cout
		<< "EXIT: "
		<< __PRETTY_FUNCTION__ << ": vec_language.size(): " << vec_language.size()
		<< endl;
}



extern bool write_messages_flag;

extern string qscript_stdout_fname;
extern FILE * qscript_stdout;

void write_messages();
int main(int argc, char ** argv)
{
	//process_options(argc, argv);
	for (int i=0; i<argc; ++i) { if (string(argv[i]) == "-m") { write_messages_flag = 1; break;} }
	if (write_messages_flag) {
		//TheQuestionnaire theQuestionnaire("dummy");
		write_messages();
		exit(0);
	}
#if 0
	if (write_messages_flag) {
		TheQuestionnaire theQuestionnaire("dummy");
		exit(0);
	}
#endif /* 0 */

	load_languages_available(vec_language);
	qscript_stdout = fopen(qscript_stdout_fname.c_str(), "w");
	//SetupSignalHandler();

	//return WRun (argc, argv, &createApplication);
	{
		try
		{
			// use argv[0] as the application name to match a suitable entry
			// in the Wt configuration file, and use the default configuration
			// file (which defaults to /etc/wt/wt_config.xml unless the environment
			// variable WT_CONFIG_XML is set)
			// WServer server(argv[0]);

			// WTHTTP_CONFIGURATION is e.g. "/etc/wt/wthttpd"
			server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);

			// add a single entry point, at the default location (as determined
			// by the server configuration's deploy-path)
			server.addEntryPoint(Wt::Application, createApplication);
			if (server.start()) {
				std::string port_number_fname = jno + string("_port_number");
				std::fstream port_number(port_number_fname.c_str(), ios_base::out);
				port_number << server.httpPort();
				port_number << ' ' << getpid() << std::endl;
				std::cout << server.httpPort() << std::endl;
				port_number.flush();
				int sig = WServer::waitForShutdown(argv[0]);
				std::cerr << "Shutdown (signal = " << sig << ")" << std::endl;
				server.stop();
				if (sig == SIGHUP)
				WServer::restart(argc, argv, environ);
			}
		} catch (WServer::Exception& e) {
			std::cerr << e.what() << std::endl;
			return 1;
		} catch (std::exception& e) {
			std::cerr << "exception: " << e.what() << std::endl;
			return 1;
		}
	}
}


void GetUserInput (
	void (*callback_ui_input) (UserInput p_user_input,
		const vector<AbstractRuntimeQuestion *> & q_vec,
		struct TheQuestionnaire * theQuestionnaire, int nest_level),
	const vector <AbstractRuntimeQuestion *> & q_vec,
	struct TheQuestionnaire * theQuestionnaire, int nest_level)
{
	cerr << "FIXME: Analyse this function in detail from a Point of View of Event Driven UI"
		<< __FILE__ << ", " << ", " << __LINE__
		<< ", " << __PRETTY_FUNCTION__ << endl;
	cerr << "FIXME: add conditions for all questions in input vector, right now we are checking only 1st question "
		<< __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
		<< endl;
	cout << "Enter: " << __PRETTY_FUNCTION__ << ", " << __FILE__ << ", " << __LINE__ << endl;
	cout << __PRETTY_FUNCTION__ << " not implemented for multiple questions per page"
		<< endl;
#if 0

	AbstractRuntimeQuestion * q = q_vec[0];
	static int count = 0;
	cout << __PRETTY_FUNCTION__ << ++count << endl;
	if (q->no_mpn == 1) {
		cout << " Question is single answer, please enter only 1 response." << endl;
	} else {
		cout << " Question accepts multiple answers." << endl;
	}
	string current_response;
	cout << "Enter Data>" << endl;
	cerr << "FIXME: what is the objective of this condition below?"
		<< __FILE__ << ", " << ", " << __LINE__
		<< ", " << __PRETTY_FUNCTION__ << endl;
	if (count < 4) {
		//getline(cin, current_response);
	} else {
		return;
	}
	UserInput user_input;
	if (current_response.size() > 0) {
		if (current_response[0] == 'P') {
			user_input.userNavigation_ = NAVIGATE_PREVIOUS;
			user_input.theUserResponse_ = user_response::UserEnteredNavigation;
		} else if (current_response[0] == 'N') {
			user_input.userNavigation_ = NAVIGATE_NEXT;
			user_input.theUserResponse_ = user_response::UserEnteredNavigation;
		} else if (current_response[0] == 'S') {
			user_input.userNavigation_ = SAVE_DATA;
			user_input.theUserResponse_ = user_response::UserSavedData;
			cout << "Got SAVE_DATA from user" << endl;
		} else  {
			user_input.theUserResponse_ = user_response::UserEnteredData;
			user_input.questionResponseData_ = current_response;
		}

		cout << "reached here" << endl;
		string err_mesg;
		bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
		// if VerifyResponse fails it is the UI's job to get valid input from the user
		// It is not the UI's job to parse the data and validate the answer against the question

		/* moved to VerifyResponse - but seems redundant - it was already there
		if (q->isAnswered_ == false && user_input.userNavigation_ == NAVIGATE_PREVIOUS
				&& user_input.theUserResponse_ == user_response::UserEnteredNavigation) {
			// allow this behaviour - they can go back to the
			// previous question without answering anything -
			// no harm done
			callback_ui_input (user_input, q, theQuestionnaire);
		} else */
		/* moved this into VerifyResponse - final else clause
		 * where all error messages can be reported
		if (q->isAnswered_ == false && user_input.userNavigation_ == NAVIGATE_NEXT
				&& user_input.theUserResponse_ == user_response::UserEnteredNavigation
				&& q->question_attributes.isAllowBlank() == false) {
			// nxd: 18-feb-2013 - note this error message should be passed
			// back as a parameter  - so it can be reported
			err_mesg = "cannot navigate to next question unless this is answered";
			valid_input = false;
		}
		*/

		cout << "reached here: valid_input :" << valid_input <<  endl;

		if (valid_input) {

			if (user_input.theUserResponse_ == user_response::UserSavedData) {
				cout << "invoking callback_ui_input with UserSavedData" << endl;
				// this call will return really fast
				//  (if you consider io fast)
				//  but what I mean is we wont add much to the call stack
				callback_ui_input (user_input, q_vec, theQuestionnaire, nest_level + 1);
				GetUserInput (callback_ui_input, q_vec, theQuestionnaire,  nest_level + 1);
				cout << "callback_ui_input has returned after UserSavedData" << endl;
			} else {
				cout << "reached here: "
					<< __PRETTY_FUNCTION__ << endl;
				callback_ui_input (user_input, q_vec, theQuestionnaire, nest_level + 1);
				cout << "callback_ui_input has returned"
					<< __PRETTY_FUNCTION__ << endl;
			}
			// move all this into callback_ui_input
			// case UserEnteredData
#if 0

			int success;
			vector <int> input_data;
			parse_input_data (current_response, &input_data, success);
			if (success == 0) {
				GetUserInput (callback_ui_input, q, theQuestionnaire);
			} else {
				// default direction - chosen by us
				user_input.userNavigation_ = NAVIGATE_NEXT;
				user_input.inputData_ = input_data;
				callback_ui_input (user_input, q, theQuestionnaire);
			}
#endif /*  0 */
		} else {
			// we should be passing an error message too
			GetUserInput (callback_ui_input, q_vec, theQuestionnaire, nest_level + 1);
		}
		/*
		else {
			// invalid entries
			cout << "invalid input" << endl;
			question_eval_loop (NORMAL_FLOW, NAVIGATE_NEXT,
					last_question_visited, 0, qnre);
			//goto ask_again;
		} */
	} else {
		// nxd: 19-feb-2013
		// I have to change this
		GetUserInput (callback_ui_input, q_vec, theQuestionnaire, nest_level + 1);
	}
#endif /* 0 */
	cout << "Exit: " << __PRETTY_FUNCTION__ << ", " << __FILE__ << ", " << __LINE__ << endl;
}


vector<string>  PrepareQuestionText (AbstractRuntimeQuestion *q)
{
	using std::string;
	using std::stringstream;
	stringstream part_mesg_id;
	part_mesg_id << q->questionName_;
	for (int i=0; i<q->loop_index_values.size(); ++i)
	{
		part_mesg_id << "_" << q->loop_index_values[i];
	}
	vector <string> result;
	stringstream question_no;
	//mvwprintw(question_window, 1, 1, "%s.", questionName_.c_str());
	question_no << q->questionName_;
	//int len_qno = questionName_.length()+2;
	if (q->loop_index_values.size() > 0) {
		for (uint32_t i = 0; i < q->loop_index_values.size(); ++i) {
			//cout << loop_index_values[i]+1 << ".";
			//mvwprintw(question_window, 1, len_qno, "%d.", loop_index_values[i]+1);
			//if (loop_index_values[i]+1<10) {
			//	len_qno += 1;
			//} else if (loop_index_values[i]+1<100) {
			//	len_qno += 2;
			//} else if (loop_index_values[i]+1<1000) {
			//	len_qno += 3;
			//} else if (loop_index_values[i]+1<10000) {
			//	len_qno += 4;
			//}
			//len_qno += 1; // for the "."
			question_no << q->loop_index_values[i] << ".";
		}
	}
	result.push_back (question_no.str());
		//mvwprintw(question_window,1,1, "%s. %s", questionName_.c_str(), questionText_.c_str() );
		//wrefresh(question_window);
		//mvwprintw(question_window, 1, len_qno+1, " %s", questionText_.c_str() );
	//mvwprintw(question_window, 1, len_qno+1, " %s", textExprVec_[0]->text_.c_str() );
	stringstream question_text;
	//question_text << q->textExprVec_[0]->text_;
	//result.push_back (question_text.str());
	//for (int i=1; i<q->textExprVec_.size(); ++i) {
	//	//mvwprintw(question_window, 2+i, 1, " %s", textExprVec_[i]->text_.c_str() );
	//	result.push_back (q->textExprVec_[i]->text_);
	//}
	//WString question_text_str;
	for (int i=0; i<q->textExprVec_.size(); ++i)
        {
        	question_text << "<p>";
		//question_text_str += "<p>";
        	if (q->textExprVec_[i]->teType_ == TextExpression::simple_text_type)
        	{
        		//stringstream mesg_id;
        		//mesg_id << part_mesg_id.str() << "_" << i;
        		//question_text += WString::tr(mesg_id.str().c_str());
			question_text << q->textExprVec_[i]->text_;
			{
			stringstream mesg_id;
			mesg_id << part_mesg_id.str() << "_" << i;
			//question_text_str += WString::tr(mesg_id.str().c_str());
			}
        	}
        	else if (q->textExprVec_[i]->teType_ == TextExpression::named_attribute_type)
        	{
			{
        		stringstream named_attribute_key;
        		named_attribute_key << q->textExprVec_[i]->naPtr_->name;
        		named_attribute_key << "_" << q->textExprVec_[i]->naIndex_;
        		//question_text_str += WString::tr(named_attribute_key.str().c_str());
			}
			question_text << q->textExprVec_[i]->naPtr_->attribute[q->textExprVec_[i]->naIndex_];
        	}
        	else if (q->textExprVec_[i]->teType_ == TextExpression::question_type)
        	{
        		if (q->textExprVec_[i]->codeIndex_ != -1) {
        			question_text << q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(q->textExprVec_[i]->codeIndex_);
				//question_text_str += q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers(q->textExprVec_[i]->codeIndex_);
        		} else {
        			question_text << q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers();
				//question_text_str += q->textExprVec_[i]->pipedQuestion_->PrintSelectedAnswers();
        		}
			//question_text << "pipedQuestion_" << endl;
        	}
        	question_text << "</p>";
        	//question_text_str += "</p>";
        }
	result.push_back (question_text.str());
	return result;

}

void DisplayQuestionTextView (const vector <string> & qno_and_qtxt)
{
	string start_marker("===================== QUESTION TEXT =============================");
	string end_marker  ("================= END OF QUESTION TEXT ==========================");
	if (qno_and_qtxt.size() > 1) {
		cout << start_marker << endl;
		cout << qno_and_qtxt[0] << "." << qno_and_qtxt[1];
		for (int i = 2; i < qno_and_qtxt.size(); ++i) {
			cout <<  qno_and_qtxt[i].c_str();
		}
		cout << endl;

		cout << end_marker << endl;
	}
	cout << endl;
}


void ClearPreviousView ()
{
	cout << __PRETTY_FUNCTION__ << endl;
}

void PrepareStubs (AbstractRuntimeQuestion *q)
{

}

void DisplayStubs (AbstractRuntimeQuestion *q)
{
	string marker_start ("------------------------------- STUBS ------------------------------------");
	string marker_end   ("----------------------------- STUBS END ----------------------------------");
	cout << marker_start << endl;
	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*> (q) ) {
		vector<stub_pair> & vec= (nq->nr_ptr->stubs);
		for (int i=0; i<vec.size(); ++i) {
			cout 	<< vec[i].code << " : " << vec[i].stub_text
				<< endl;
		}
	} else if (RangeQuestion * rq = dynamic_cast<RangeQuestion*> (q) ) {
		rq->MakeDisplaySummaryDataRanges();
		for(	vector<display_data::DisplayDataUnit>::iterator it = rq->displayData_.begin();
				it != rq->displayData_.end(); ++it) {
			//cout << *it << endl;
			if ( (*it).displayDataType_ == display_data::single_element) {
				cout << "  " << (*it).startOfRangeOrSingle_ << " ";
			} else if ( (*it).displayDataType_ == display_data::range_element) {
				cout << "  " << (*it).startOfRangeOrSingle_ << " - " << (*it).endOfRange_;
			}
		}
		cout << endl;
	} else {
		cerr << "Unhandled exception" << endl;
		exit(1);
	}
	cout << marker_end << endl;
}


void DisplayCurrentAnswers (AbstractRuntimeQuestion * q)
{
	if (q->input_data.begin() != q->input_data.end()) {
		cout << "Current Answers values: ";

		for (set<int32_t>::iterator iter = q->input_data.begin();
			iter != q->input_data.end(); ++iter){
			cout << *iter << " ";
		}
		cout << endl;
	}
	string end_marker("----------------- END OF ANSWERS -----------------------");
	cout << end_marker << endl;
}




void stdout_eval (const vector <AbstractRuntimeQuestion *> & q_vec,
	struct TheQuestionnaire * theQuestionnaire,
	void (*callback_ui_input)
		(UserInput p_user_input, const vector <AbstractRuntimeQuestion *> & q_vec,
		struct TheQuestionnaire * theQuestionnaire, int nest_level),
	int nest_level)
{
	cout << "Enter: " << __PRETTY_FUNCTION__
		<< "nest_level: " << nest_level << endl
		<< "q_vec.size(): " << q_vec.size()
		<< endl;
	ClearPreviousView ();
	AbstractRuntimeQuestion * q= q_vec[0];
	vector <string> qno_and_qtxt = PrepareQuestionText (q);
	DisplayQuestionTextView (qno_and_qtxt);

	cout << "About to test if MEDIA or RESPONSE Question" << endl;
	if (q->q_type == spn || q->q_type == mpn) {
		PrepareStubs (q);
		DisplayStubs (q);
		DisplayCurrentAnswers (q);
	} else {
		cout << "MEDIA Question" << endl;
	}
	cout << "reached here " << endl;
	//GetUserInput (callback_ui_input, q, theQuestionnaire);
	QuestionnaireApplication * qapp_ptr =  static_cast<QuestionnaireApplication*> (WApplication::instance());
	// nxd implement: wxGUI->set_callback_ui_input (callback_ui_input);
	qapp_ptr->set_callback_ui_input(callback_ui_input);
	//gtkQuestionnaireApplication->ConstructQuestionForm (q
	//		//, gtkQuestionnaireApplication->this_users_session
	//		);

	// nxd implement: wxGUI->ConstructQuestionForm( q );

	qapp_ptr->ConstructQuestionForm (q_vec);
		/*
	for (int32_t i = 0; i < q_vec.size(); ++i) {
		QuestionUITemplate * q_ui_form = qapp_ptr->ConstructQuestionForm (q);
		qapp_ptr->question_ui_vec.push_back(q_ui_form);
		qapp_ptr->new_form->addWidget (q_ui_form->questionContainer_);
	}
	setCentralWidget(new_form);
	*/
	//GetUserInput (callback_ui_input, q, theQuestionnaire);
	cout << "EXIT:"
		<< __PRETTY_FUNCTION__
		<< ", nest_level:" << nest_level
		<< endl;
}


void QuestionnaireApplication::PrepareMultiCodedStubDisplay (
		QuestionUITemplate * p_q_ui_form, NamedStubQuestion * nq)
{
	cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
	ClearStubsArea();
	p_q_ui_form -> wt_cb_rb_container_ = new WGroupBox();
	p_q_ui_form -> wt_cb_rb_container_->setStyleClass("qscript-rb-cb-container");
	vector<stub_pair> & vec= (nq->nr_ptr->stubs);
	unsigned long count = vec.size();
	for (int i=0; i<vec.size(); ++i) {
		stringstream named_range_key;
		named_range_key << nq->nr_ptr->name << "_" << i;
		if (vec[i].mask) {
			WCheckBox * wt_cb =
				new WCheckBox (WString::tr(
					named_range_key.str().c_str()),
					p_q_ui_form->wt_cb_rb_container_);
			wt_cb->setInline(false);
			//wt_cb->setStyleClass("qscript-check-box");
			wt_cb->setStyleClass("qscript-span-checkbox");
			p_q_ui_form -> vec_cb.push_back(wt_cb);
			//cout << " adding code: " << vec[i].code << " to map_cb_code_index" ;
			//map_cb_code_index[vec_cb.size()-1] = vec[i].code;
			p_q_ui_form-> map_cb_code_index[p_q_ui_form->vec_cb.size()-1] = vec[i].code;
			
			if (vec[i].url_image.length() > 0) {
				cout << "Has an url_image: " << vec[i].url_image << endl;
				Wt::WImage *img = new Wt::WImage (vec[i].url_image, p_q_ui_form -> wt_cb_rb_container_);
			}
		}
	}

	cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
}


void QuestionnaireApplication::PrepareSingleCodedStubDisplay (
		QuestionUITemplate * p_q_ui_form,
		NamedStubQuestion * nq)
{
	cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
	//ClearRadio();
	ClearStubsArea();
	p_q_ui_form -> wt_cb_rb_container_ = new WGroupBox();
	p_q_ui_form -> wt_cb_rb_container_->setStyleClass("qscript-rb-cb-container");
	p_q_ui_form -> wt_rb_container_ = new WButtonGroup(p_q_ui_form->wt_cb_rb_container_);
	vector<stub_pair> & vec= (nq->nr_ptr->stubs);
	unsigned long count = vec.size();
	for (int i=0; i<vec.size(); ++i) {
		stringstream named_range_key;
		named_range_key << nq->nr_ptr->name << "_" << i;
		if (/*q->no_mpn==1 && */ vec[i].mask) {
			//WRadioButton * wt_rb = new WRadioButton( vec[i].stub_text, wt_cb_rb_container_);
			WRadioButton * wt_rb = new WRadioButton (
						WString::tr(named_range_key.str().c_str()),
						p_q_ui_form->wt_cb_rb_container_);
			wt_rb->setStyleClass("qscript-span-radio");
			p_q_ui_form->wt_rb_container_->addButton(wt_rb, vec[i].code);
			new WBreak(p_q_ui_form->wt_cb_rb_container_);
			p_q_ui_form->vec_rb.push_back(wt_rb);
		}
	}
	cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
}


void QuestionnaireApplication::DisplayStubs (
		QuestionUITemplate * p_q_ui_form, AbstractRuntimeQuestion * q)
{
	cout << __PRETTY_FUNCTION__ << endl;
	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*>(q)) {
		// nxd: move both the below functions to a clear() api which we call from here
		//rbData_ = -1; // clear the data basically
		//cbData_.clear();
		if (q->no_mpn==1) {
			PrepareSingleCodedStubDisplay(p_q_ui_form, nq);
		} else {
			PrepareMultiCodedStubDisplay (p_q_ui_form, nq);
		}
		p_q_ui_form-> wt_cb_rb_container_->setStyleClass("qscript-rb-cb-container");
		p_q_ui_form-> questionContainer_ -> addWidget(
				p_q_ui_form->wt_cb_rb_container_);
	} else if (q->q_type == video) {
		DisplayVideo (q);
	} else if (q->q_type == audio) {
		DisplayAudio (q);
	} else if (q->q_type == image) {
		//DisplayImage (q, new_form);
		DisplayImage (q, p_q_ui_form -> questionContainer_);
		cout << "case image question" << endl;
	} else {
		cout << "=== Implement Display Range Question" << endl;
		p_q_ui_form->le_data_ = new WLineEdit();
		p_q_ui_form->le_data_->setStyleClass("qscript-open-end-textbox");
		p_q_ui_form->questionContainer_ -> addWidget(p_q_ui_form->le_data_);
	}
}

void QuestionnaireApplication::set_callback_ui_input (
	void (*p_callback_ui_input) (UserInput p_user_input,
		const vector<AbstractRuntimeQuestion *> & q_vec,
		struct TheQuestionnaire * theQuestionnaire, int nest_level)
	)
{
	callback_ui_input = p_callback_ui_input;
}

void QuestionnaireApplication::DisplayQuestionTextView (
		QuestionUITemplate * p_q_ui_form,
		const vector <string> & qno_and_qtxt)
{

	p_q_ui_form->wt_questionText_ = new WText();
	p_q_ui_form->wt_questionNo_ = new WText();
	std::stringstream question_text;
	for (int i=1; i < qno_and_qtxt.size(); ++i) {
		question_text << qno_and_qtxt[i];
	}
	p_q_ui_form->wt_questionText_->setText(question_text.str());
	p_q_ui_form->wt_questionText_->setStyleClass("qscript-qtext");
	p_q_ui_form->wt_questionNo_->setText(qno_and_qtxt[0]);
	p_q_ui_form->wt_questionNo_->setStyleClass("qscript-qno");

	p_q_ui_form-> questionContainer_->addWidget(p_q_ui_form->wt_questionNo_);
	p_q_ui_form-> questionContainer_->addWidget(p_q_ui_form->wt_questionText_);
}


void QuestionnaireApplication::DisplayVideo (AbstractRuntimeQuestion * q)
{
	cout << __PRETTY_FUNCTION__;

}

void QuestionnaireApplication::DisplayAudio (AbstractRuntimeQuestion * q)
{
	cout << __PRETTY_FUNCTION__;

}

void QuestionnaireApplication::DisplayImage (AbstractRuntimeQuestion * q, WContainerWidget * parent)
{
	cout << __PRETTY_FUNCTION__ << ": image name: ";
	if (VideoQuestion * vq = dynamic_cast <VideoQuestion*> (q)) {
		Wt::WImage *img = new Wt::WImage (vq->file_path, parent);
		cout << vq->file_path ;
	}
	cout << endl;
}

void QuestionnaireApplication::ConstructQuestionForm (
		const vector<AbstractRuntimeQuestion *> & q_vec)
{
	cout << __PRETTY_FUNCTION__ << endl;
	WContainerWidget * new_form = new WContainerWidget();

	question_ui_vec.clear();
	for (int32_t i=0; i < q_vec.size(); ++i) {
		AbstractRuntimeQuestion * q = q_vec[i];
		QuestionUITemplate * q_ui_form = new QuestionUITemplate();
		q_ui_form->questionContainer_ = new WContainerWidget();
		q_ui_form->questionContainer_->setStyleClass("qscript-container");
		q_ui_form->vec_rb.clear();	// memory leak introduced here? no it seems
		q_ui_form->vec_cb.clear();	// memory leak introduced here? no it seems

		vector <string> question_text_vec = PrepareQuestionText (q);
		//the_question = new wxStaticText(panel, -1, wxT("Question No and Question Text"));
		this->DisplayQuestionTextView (q_ui_form, question_text_vec);

		DisplayStubs (q_ui_form, q);
		cerr << "FIXME: Check if below statement is really needed:"
			<< __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
			<< endl;
		//this_users_session -> ptr_last_question_visited = q;
		{
			WPushButton * next = new WPushButton("Next");
			next->clicked().connect(this, &QuestionnaireApplication::handleDataInput);
			q_ui_form-> questionContainer_ -> addWidget( next);
			WPushButton *prev_button = new WPushButton("Previous");
			WPushButton *save_button = new WPushButton("Save");
			save_button->clicked().connect(this, &QuestionnaireApplication::handleSave);
			q_ui_form-> questionContainer_ -> addWidget(save_button);
		}
		new_form->addWidget (q_ui_form->questionContainer_);
		question_ui_vec.push_back (q_ui_form);
	}
	setCentralWidget(new_form);
}


void QuestionnaireApplication::setCentralWidget (WContainerWidget * new_question_form)
{
	if (!flagSerialPageRemoved_) {
		formContainer_->removeWidget (serialPage_);
		flagSerialPageRemoved_ = true;
	}
	if (currentForm_) {
		delete currentForm_;
	}
	currentForm_ = new_question_form;
	formContainer_->addWidget (currentForm_);
}


void QuestionnaireApplication::ClearStubsArea()
{
	//ClearCheckList();
	//ClearRadio();
}

//
// Make changes here.
// The structure of how the handler behaves will now be different
// We report to the calling function 2 things
//	1. Whether the question was answered
//	2. If yes - the data as a string.
//
//	The decision making on whether to send it will be taken
//	by the calling function, after it has seen the response
//	to all the questions, and can conclude that - all questions
//	on the page were answered

UIReturnValue QuestionnaireApplication::handleRBDataInput (int nest_level,
		int form_index)
{
	vector<int32_t> data;
	stringstream s1;
	UIReturnValue  ret_val;
	bool isAnswered = false;
	if (question_ui_vec[form_index]->wt_rb_container_->selectedButtonIndex() != -1) {
		isAnswered = true;
		int code = question_ui_vec[form_index] -> wt_rb_container_->checkedId();
		cout << "no_mpn == 1, code: " << code << endl;
		data.push_back(code);
		s1 << code;
		ret_val.answered_ = true;
		ret_val.textData_= s1.str();
	} else {
		isAnswered = false;
	}
	/*
	string err_mesg;
	UserInput user_input;
	user_input.theUserResponse_ = user_response::UserEnteredData;
	user_input.questionResponseData_ = s1.str();
	//AbstractRuntimeQuestion * q = this_users_session -> ptr_last_question_visited ;
	AbstractQuestionnaire * abs_qnre_ptr = AbstractQuestionnaire::qnre_ptr;
	AbstractRuntimeQuestion * q = abs_qnre_ptr->last_question_visited[0];
	bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
	if (valid_input) {
		if (user_input.theUserResponse_ == user_response::UserSavedData) {
			cerr  << "NOT YET DONE"
				<< __FILE__ << "," << __LINE__ << "," << __PRETTY_FUNCTION__
				<< endl
				<< "invoking callback_ui_input with UserSavedData" << endl;
			// this call will return really fast
			//  (if you consider io fast)
			//  but what I mean is we wont add much to the call stack
			callback_ui_input (user_input,
				abs_qnre_ptr->last_question_visited,
				this_users_session -> theQuestionnaire_, nest_level + 1);
			//GetUserInput (callback_ui_input, q, theQuestionnaire);
			cout << "callback_ui_input has returned after UserSavedData" << endl;
		} else {
			cout << "reached here: "
				<< __PRETTY_FUNCTION__ << endl;
			callback_ui_input (user_input,
					 abs_qnre_ptr->last_question_visited,
					 this_users_session ->theQuestionnaire_, nest_level + 1);
			cout << "callback_ui_input has returned"
				<< __PRETTY_FUNCTION__ << endl;
		}
		// move all this into callback_ui_input
		// case UserEnteredData
	} else {
		// we should be passing an error message too
		//GetUserInput (callback_ui_input, q, theQuestionnaire);
		// do nothing - the callback just continues to wait for data
	}
	*/
	//cout << __PRETTY_FUNCTION__ << "not yet implemented" << endl;
	return ret_val;
}

UIReturnValue QuestionnaireApplication::handleCBDataInput (int nest_level,
		int form_index)
{
	vector<int32_t> data;
	bool isAnswered = false;
	UIReturnValue  ret_val;
	stringstream s1;

#if 0
	for (set<int32_t>::iterator it = cbData_.begin(); it != cbData_.end(); ++it) {
		//cout << " " << *it;
		data.push_back (*it);
		s1 << " " << (*it);
	}
	cout << " vec_cb.size(): " << vec_cb.size() << "no_mpn > 1" << endl;
#endif

	for (int i = 0; i < question_ui_vec[form_index]->vec_cb.size(); ++i) {
		if (question_ui_vec[form_index]->vec_cb[i]->checkState() == Wt::Checked) {
			int code =question_ui_vec[form_index]->map_cb_code_index[i];
			data.push_back(code);
			cout << "vec_cb[" << i << "] is checked,   code: " << code << endl;
			isAnswered = true;
			s1 << " " << code;
		}
	}
	if (isAnswered == true) {
		ret_val.answered_ = true;
		ret_val.textData_= s1.str();
	}
	/*
	UserInput user_input;
	user_input.questionResponseData_ = s1.str();
	user_input.theUserResponse_ = user_response::UserEnteredData;
	cerr << "FIXME: taking only 1st question on page:" << __PRETTY_FUNCTION__
		<< ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
		<< endl;
	AbstractQuestionnaire * abs_qnre_ptr = AbstractQuestionnaire::qnre_ptr;
	AbstractRuntimeQuestion * q = abs_qnre_ptr->last_question_visited[0];
	//AbstractRuntimeQuestion * q = this_users_session -> ptr_last_question_visited ;
	string err_mesg;
	bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
	if (valid_input) {
		if (user_input.theUserResponse_ == user_response::UserSavedData) {
			cerr  << "NOT YET DONE"
				<< __FILE__ << "," << __LINE__ << "," << __PRETTY_FUNCTION__
				<< endl
				<< "invoking callback_ui_input with UserSavedData" << endl;
			// this call will return really fast
			//  (if you consider io fast)
			//  but what I mean is we wont add much to the call stack
			callback_ui_input (user_input,
					abs_qnre_ptr->last_question_visited,
					this_users_session -> theQuestionnaire_, nest_level + 1);
			//GetUserInput (callback_ui_input, q, theQuestionnaire);
			cout << "callback_ui_input has returned after UserSavedData" << endl;
		} else {
			cout << "reached here: "
				<< __PRETTY_FUNCTION__ << endl;
			callback_ui_input (user_input,
					abs_qnre_ptr->last_question_visited,
					this_users_session -> theQuestionnaire_, nest_level + 1);
			cout << "callback_ui_input has returned"
				<< __PRETTY_FUNCTION__ << endl;
		}
		// move all this into callback_ui_input
		// case UserEnteredData
	} else {
		// we should be passing an error message too
		//GetUserInput (callback_ui_input, q, theQuestionnaire);
		// do nothing - the callback just continues to wait for data
	}
	*/
	//cout << __PRETTY_FUNCTION__ << "not yet implemented" << endl;
	cout << "Exit: "
		<< __PRETTY_FUNCTION__
		<< ", data : " << ret_val.textData_
		<< endl;
	return ret_val;
}

void QuestionnaireApplication::handleRangeQuestionData(int nest_level)
{
	cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
	/*
	string current_question_response = le_data_->text().narrow();
	//AbstractRuntimeQuestion * last_question_served = this_users_session-> ptr_last_question_visited;
	AbstractRuntimeQuestion * last_question_served =
		AbstractQuestionnaire::qnre_ptr->last_question_visited[0];
	if (last_question_served->no_mpn==1) {
		UserInput user_input;
		user_input.questionResponseData_ = current_question_response ;
		user_input.theUserResponse_ = user_response::UserEnteredData;
		//AbstractRuntimeQuestion * q = this_users_session -> ptr_last_question_visited ;
		AbstractRuntimeQuestion * q =
			AbstractQuestionnaire::qnre_ptr->last_question_visited[0];
		cerr << "FIXME: taking only 1st question on page:" << __PRETTY_FUNCTION__
			<< ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
			<< endl;
		string err_mesg;
		bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
		if (valid_input) {
			if (user_input.theUserResponse_ == user_response::UserSavedData) {
				cerr  << "NOT YET DONE"
					<< __FILE__ << "," << __LINE__ << "," << __PRETTY_FUNCTION__
					<< endl
					<< "invoking callback_ui_input with UserSavedData" << endl;
				// this call will return really fast
				//  (if you consider io fast)
				//  but what I mean is we wont add much to the call stack
				callback_ui_input (user_input,
						AbstractQuestionnaire::qnre_ptr->last_question_visited,
						this_users_session -> theQuestionnaire_, nest_level + 1);
				//GetUserInput (callback_ui_input, q, theQuestionnaire);
				cout << "callback_ui_input has returned after UserSavedData" << endl;
			} else {
				cout << "reached here: "
					<< __PRETTY_FUNCTION__ << endl;
				callback_ui_input (user_input,
						AbstractQuestionnaire::qnre_ptr->last_question_visited,
						this_users_session -> theQuestionnaire_,
						nest_level + 1);
				cout << "callback_ui_input has returned"
					<< __PRETTY_FUNCTION__ << endl;
			}
			// move all this into callback_ui_input
			// case UserEnteredData
		} else {
			// do nothing
		}
	} else if (last_question_served->no_mpn > 1) {
		string utf8_response = le_data_->text().toUTF8();
		if (utf8_response != "")
		{
			stringstream file_name_str;
			file_name_str << last_question_served->questionName_ << "."
				<< jno << "_" << ser_no << ".dat";
			fstream open_end_resp(file_name_str.str().c_str(), ios_base::out|ios_base::ate);
			open_end_resp << utf8_response << endl;
			//last_question_served->input_data.insert(96);
			//last_question_served->isAnswered_ = true;
			stringstream ss1 ;
			ss1 << 96;
			UserInput user_input;
			user_input.questionResponseData_ = ss1.str();
			user_input.theUserResponse_ = user_response::UserEnteredData;
			//AbstractRuntimeQuestion * q = this_users_session -> ptr_last_question_visited ;
			AbstractRuntimeQuestion * q = AbstractQuestionnaire::qnre_ptr->last_question_visited[0];
			cerr << "FIXME: taking only 1st question on page:" << __PRETTY_FUNCTION__
				<< ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
				<< endl;
			string err_mesg;
			bool valid_input = q->VerifyResponse(user_input.theUserResponse_, user_input.userNavigation_, err_mesg);
			if (valid_input) {
				callback_ui_input (user_input,
						AbstractQuestionnaire::qnre_ptr->last_question_visited,
						this_users_session -> theQuestionnaire_, nest_level + 1);
			}
		}
		else
		{
			// Do nothing - but we should print a default error message on the screen
		}
	}
	*/
	cout << __PRETTY_FUNCTION__ << "not yet implemented" << endl;
	cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
}

/*
void QuestionnaireApplication::ConstructThankYouPage()
{
	WContainerWidget * new_form = new WContainerWidget();
	WText * txt = new WText(WString::tr("thank_you"), new_form);
	WText * survey_code = new WText(WString::tr("vege_source_code"), new_form);
	setCentralWidget(new_form);
	cout << "ConstructThankYouPage\n";
}
*/

void QuestionnaireApplication::handleSave()
{
	UserInput user_input;
	user_input.userNavigation_ = SAVE_DATA;
	user_input.theUserResponse_ = user_response::UserSavedData;
	callback_ui_input (user_input,
			//this_users_session->ptr_last_question_visited,
			//this_users_session->theQuestionnaire_->last_question_visited,
			AbstractQuestionnaire::qnre_ptr->last_question_visited,
			this_users_session->theQuestionnaire_, 1);
}

void QuestionnaireApplication::handleDataInput()
{
	cout << __PRETTY_FUNCTION__ << endl;
	// Iterate over all the forms in the last question visited
	// and ensure that they have a response
	// If any question is blank, report a message on the screen, highlighting
	// a blank question and at the same time reporting an error message
	// Go forward only if all the questions on the page have a valid response
	cerr << "FIXME: taking only 1st question on page:" << __PRETTY_FUNCTION__
		<< ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
		<< endl;
	cout << "question_ui_vec.size(): " << question_ui_vec.size() << endl;

	// question_ui_vec contains all the forms for question in
	// corresponding order
	vector <UIReturnValue> ui_question_status;
	for (int32_t i = 0;
		i < AbstractQuestionnaire::qnre_ptr->last_question_visited.size();
		++i) {
		AbstractRuntimeQuestion * last_question_served =
				AbstractQuestionnaire::qnre_ptr->last_question_visited[i];

		//if (NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion *>(this_users_session -> ptr_last_question_visited ))
		if (NamedStubQuestion *nq = dynamic_cast<NamedStubQuestion *>(last_question_served)) {
			//AbstractRuntimeQuestion * last_question_served = this_users_session -> ptr_last_question_visited ;
			vector<int32_t> data;
			bool isAnswered = false;
			cout << "returned back data from question: " << nq->questionName_ << endl;
			if (last_question_served->no_mpn == 1) {
				UIReturnValue ret_val =  handleRBDataInput(1, i);
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
	}
	bool all_questions_answered = true;
	int n_answered = 0;
	stringstream not_answered_question_list;
	for (int32_t i=0; i<ui_question_status.size(); ++i ) {
		if (ui_question_status[i].answered_ == false) {
			all_questions_answered = false;
			not_answered_question_list
				<< " "
				<< AbstractQuestionnaire::qnre_ptr->last_question_visited[i]->questionName_;
		} else {
			++n_answered;
		}
	}
	if (all_questions_answered == false) {
		// display message on screen - all questions are not answered
		string err_mesg ("Please answer all the questions on the page: the following question(s) are missing an anwer");
		err_mesg += not_answered_question_list.str();
		print_ui_error_message (err_mesg);
	} else {
		// send question for back end verification
		UserInput user_input;
		for (int32_t i=0; i<ui_question_status.size(); ++i ) {
			user_input.theUserResponse_ = user_response::UserEnteredData;
			user_input.questionResponseDataVec_.push_back(ui_question_status[i].textData_);
		}
		AbstractQuestionnaire * abs_qnre_ptr = AbstractQuestionnaire::qnre_ptr;
		callback_ui_input (user_input,
			abs_qnre_ptr->last_question_visited,
			this_users_session -> theQuestionnaire_, 1);
	}

}

void QuestionnaireApplication::print_ui_error_message (string & err_mesg)
{
	if (wtxt_err_mesg_ == 0) {
		wtxt_err_mesg_ = new WText();
	}
	wtxt_err_mesg_->setText(err_mesg);
	currentForm_->addWidget (wtxt_err_mesg_);
}
