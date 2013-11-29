#include "question_logic.h"
#include "json.h"
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
	//cout << __PRETTY_FUNCTION__ << endl;
	printf ("%s\n", __PRETTY_FUNCTION__);
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
	} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {
		vector <string> err_mesg_vec;
		cout << "mode: user_response::UserEnteredData" << endl;
		bool all_questions_success =
			eval_single_question_logic_with_input (p_user_input,
					q_vec, theQuestionnaire,
					nest_level + 1, err_mesg_vec);
		if (all_questions_success) {
			question_eval_loop2 (p_user_input, q_vec, 0, theQuestionnaire, nest_level + 1);
			cout << __PRETTY_FUNCTION__ << " - case UserEnteredData - success, invoking question_eval_loop2"
					<< endl;
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
		cout << "under stdout either the user can enter data or navigation" << endl
			<< "but under ncurses or other guis - it's possible to enter data" << endl
			<< " AND ask to save by pressing f4, in which case we should save the data "
			<< " and then try to validate the user input - just like we would in a normal case"
			<< endl;
		// nxd: this function needs to be cleaned up
		//      we can easily downcast to an AbstractQuestionnaire and then there is no need for this
		//      function to be present here
		theQuestionnaire->write_data_to_disk (theQuestionnaire->question_list, theQuestionnaire->jno, theQuestionnaire->ser_no);
	} else {
		cerr << __PRETTY_FUNCTION__ << " unhandled case theUserResponse_" << endl;
	}
	printf("EXIT: %s\n", __PRETTY_FUNCTION__);
}

void question_eval_loop2 (
	UserInput p_user_input,
	const vector<AbstractRuntimeQuestion *> & last_question_visited,
	AbstractRuntimeQuestion * jump_to_question, struct TheQuestionnaire * theQuestionnaire, int nest_level)
{
	//my_log_from_cpp ("question_eval_loop2");
	printf ("Enter: %s\n", __PRETTY_FUNCTION__);
	//cout << endl << "Enter: " << __PRETTY_FUNCTION__ << endl;
	//cout << "arg values: " << endl;
	if (p_user_input.userNavigation_ == NAVIGATE_NEXT) {
		//cout << "p_user_input.userNavigation_ == NAVIGATE_NEXT" << endl;
		printf ("p_user_input.userNavigation_ == NAVIGATE_NEXT\n");
	} else if (p_user_input.userNavigation_ == NAVIGATE_PREVIOUS) {
		printf ("p_user_input.userNavigation_ == NAVIGATE_PREVIOUS\n");
	} else {
		printf ("FIXME: p_user_input.userNavigation_ == Unhandled value\n");
	}
	if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {
		printf ("p_user_input.theUserResponse_ == UserEnteredNavigation");
	} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {
		cout << "p_user_input.theUserResponse_ == UserEnteredData" << endl;
	} else if (p_user_input.theUserResponse_ == user_response::UserClearedData) {
		cout << "p_user_input.theUserResponse_ == UserClearedData" << endl;
	} else if (p_user_input.theUserResponse_ == user_response::UserSavedData) {
		cout << "p_user_input.theUserResponse_ == UserSavedData" << endl;
	} else if (p_user_input.theUserResponse_ == user_response::NotSet) {
		cout << "p_user_input.theUserResponse_ == NotSet" << endl;
	} else {
		cout << "FIXME: p_user_input.theUserResponse_ == Unhandled value " << endl;
	}


	//cout << "p_user_input.questionResponseData_:" << p_user_input.questionResponseData_ << endl;

	if (last_question_visited.size() > 0) {
		//cout << "last_question_visited->questionName_:"
		//	<<  last_question_visited->questionName_
		//	<< endl;
		printf ("last_question_visited->questionName_:%s\n",
				last_question_visited[0]->questionName_.c_str());
	} else {
		//cout << "last_question_visited->questionName_: is NULL"  << endl;
		printf ("last_question_visited->questionName_ is NULL\n");
	}

	if (last_question_visited.size() > 0) {
		//my_log_from_cpp ("last_question_visited.size() > 0");
		if (p_user_input.theUserResponse_ == user_response::UserEnteredNavigation) {
			if (p_user_input.userNavigation_ == NAVIGATE_PREVIOUS) {
				//fprintf(qscript_stdout, "user_navigation == NAVIGATE_PREVIOUS unhandled\n");
				printf("%s, %s, %d, user_navigation == NAVIGATE_PREVIOUS unhandled\n",
						__PRETTY_FUNCTION__, __FILE__, __LINE__);
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
				cout << "Unhandled case userNavigation_ ... exiting" << endl
					<< __FILE__ << ","
					<< __LINE__ << ","
					<< __PRETTY_FUNCTION__ << ","
					<< endl;
				exit(1);
			}
		} else if (p_user_input.theUserResponse_ == user_response::UserEnteredData) {
			// the management of correctly accepting data is handled
			// by : callback_ui_input
			// if we have reached back again here - it means it's
			// time to get the next question




		} else if (p_user_input.theUserResponse_ == user_response::UserViewedVideo) {
				// do nothing
				// once we exit this major block == last_question_visited
				// the bottom of this function will handle it
		} else if (p_user_input.theUserResponse_ == user_response::UserCapturedTime) {
				// do nothing
				// once we exit this major block == last_question_visited
				// the bottom of this function will handle it
		} else {
			cout << "Unhandled case userNavigation_ ... exiting" << endl;
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
			printf(" eval2 has returned NULL => End of qnre();\n");
			//my_log_from_cpp(" eval2 has returned NULL => End of qnre();\n");
			show_end_of_qnre_page();
		} else {
			stringstream eval2_retval_str;
			eval2_retval_str << "q_vec.size(): " << q_vec.size() ;
			for (int i=0; i < q_vec.size(); ++i) {
				eval2_retval_str << q_vec[i]->questionName_;
				for (int j=0; j < q_vec[i]->loop_index_values.size(); ++j) {
					eval2_retval_str << "$" << q_vec[i]->loop_index_values[j];
				}
				eval2_retval_str << endl;
			}
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
	//my_log_from_cpp ("Entered called_from_the_dom");
	//my_log_from_cpp (data);
	string str_data (data);
	vector <string> question_data_vec = split_on_char (data, '|');
	string str_other_specify_data(other_specify_data);
	if (str_other_specify_data.length() > 0) {
		json_value * the_json_object = json_parse (str_other_specify_data.c_str(), str_other_specify_data.length());
		if ( AbstractQuestionnaire::qnre_ptr->last_question_visited.size() == 1) {
			NamedStubQuestion * nq = dynamic_cast <NamedStubQuestion*> (AbstractQuestionnaire::qnre_ptr->last_question_visited[0]);
			if (nq) {
				nq->nr_ptr->stubs[6].stub_text = "New Other Specify Brand 1";
				nq->nr_ptr->stubs[7].stub_text = "New Other Specify Brand 2";
			}
		}
	}
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
		} else if (q->q_type == image) {
			user_input.theUserResponse_ = user_response::UserViewedImage;
		} else if (q->q_type == audio) {
			user_input.theUserResponse_ = user_response::UserListenedToAudio;
		} else if (q->q_type == video_capture || q->q_type == audio_capture || q->q_type == image_capture) {
			user_input.theUserResponse_ = user_response::UserCapturedTime;
		} else {

			if (question_data_vec[i].length() > 0) {
				user_input.theUserResponse_ = user_response::UserEnteredData;
				user_input.questionResponseDataVec_.push_back(question_data_vec[i]);
			} else {
				all_questions_answered = false;
				not_answered_question_list << " " << q->questionName_;
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
