/*
 * =====================================================================================
 *
 *       Filename:  AbstractQuestionnaire.h
 *
 *    Description:  Extract all common functionality of the questionnaire out
 *    			This should simplify code generation
 *
 *        Version:  1.0
 *        Created:  Friday 15 February 2013 09:59:03  IST
 *       Revision:  none
 *       Compiler:  c++
 *
 *         Author:  Neil Xavier D'Souza,
 *        Company:
 *
 * =====================================================================================
 */

#ifndef QSCRIPT_ABSTRACT_QUESTIONNAIRE_H
#define QSCRIPT_ABSTRACT_QUESTIONNAIRE_H

#include <vector>
#include <string>
#include <fstream>
#include <dirent.h>

#include "question.h"
#include "base_text.h"
#include "user_navigation.h"
#include "qscript_lib.h"
#include "EvalReturnValue.h"


//#include "AsciiFlatFileQuestionDiskMap.h"
//#include "XtccDataFile.h"
//#include "qtm_data_file.h"
//#include "qtm_datafile_conf_parser.h"


struct ComputePreviousQuestionRetVal {
	AbstractRuntimeQuestion * singlePreviousQuestion_;
	string questionGroupName_;
	ComputePreviousQuestionRetVal():
		singlePreviousQuestion_(0), questionGroupName_()
	{ }
};


struct AbstractQuestionnaire
{
	static AbstractQuestionnaire * qnre_ptr;
	AbstractRuntimeQuestion * last_question_answered;
	std::vector<AbstractRuntimeQuestion *> last_question_visited;
	std::vector <AbstractRuntimeQuestion*> question_list;
	std::fstream messages;
	bool back_jump;
	std::string jno;
	int ser_no;
	bool stopAtNextQuestion;
	int32_t questions_start_from_here_index;
	int ser_no_pos;
	std::string jumpToQuestion;
	int32_t jumpToIndex;
	std::vector <BaseText> base_text_vec;
	AbstractQuestionnaire (std::string p_jno);
	void print_question_messages(AbstractRuntimeQuestion * q);
	//void print_summary_axis (std::vector<qtm_data_file_ns::QtmDataDiskMap*> & v, std::fstream & qtm_qax_file);

	//virtual void compute_flat_file_map_and_init() = 0;
	virtual /* vector<AbstractRuntimeQuestion *> */ EvalReturnValue eval2 (UserNavigation p_navigation_mode,
				const vector<AbstractRuntimeQuestion *> & p_last_question_visited,
				AbstractRuntimeQuestion * p_jump_to_index,
				const string & p_jump_to_group_name) = 0;
	void write_data_to_disk(const std::vector<AbstractRuntimeQuestion*>& q_vec
		, std::string jno
		, int32_t ser_no);
	int write_data_to_buffer (const vector<AbstractRuntimeQuestion*>& q_vec
		, std::string jno
		, int32_t ser_no, char * & buffer, int & n_left);
	int32_t ComputeJumpToIndex(AbstractRuntimeQuestion * q);
	void reset_questionnaire();
	//AbstractRuntimeQuestion * ComputePreviousQuestion(AbstractRuntimeQuestion * q);
	struct ComputePreviousQuestionRetVal ComputePreviousQuestion(AbstractRuntimeQuestion * q);
	void DisplayActiveQuestions();
	//void write_qtm_data_to_disk();
	//void write_ascii_data_to_disk();
	//void write_xtcc_data_to_disk();
	void do_freq_counts();
	private:
	AbstractQuestionnaire& operator = (const AbstractQuestionnaire&);
	AbstractQuestionnaire (const AbstractQuestionnaire&);

};

void GetUserResponse(std::string & qno, int32_t & qindex);
int read_a_serial_no (DIR * directory_ptr, string jno, struct AbstractQuestionnaire * qnre);

#endif /*  QSCRIPT_ABSTRACT_QUESTIONNAIRE_H */
