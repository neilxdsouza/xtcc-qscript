#ifndef qscript_lib_h
#define qscript_lib_h

//#include <sstream>
//#include <iosfwd>
#include <string>
#include <sys/stat.h>
#include <vector>
#include <map>
#include <string>
#include "question_disk_data.h"

struct AbstractRuntimeQuestion;
//using namespace std;
int32_t check_if_reg_file_exists(std::string jno, int32_t ser_no);
int32_t load_data(std::string jno, int32_t ser_no,
		std::map <std::string, question_disk_data*> * qdd_map_ptr);

int32_t load_data_from_string(const char * survey_data,
		map <string, question_disk_data*> * qdd_map_ptr,
		map <string, vector<int> >  * randomization_order_ptr);

//void merge_disk_data_into_questions(FILE * qscript_stdout);
//void clear_previous_data();
//void merge_disk_data_into_questions2(FILE * qscript_stdout, AbstractRuntimeQuestion * & p_last_question_answered,
//		AbstractRuntimeQuestion * & p_last_question_visited, const vector <AbstractRuntimeQuestion*> question_list);
struct named_attribute_list;
void merge_disk_data_into_questions2(FILE * qscript_stdout,
		AbstractRuntimeQuestion * & p_last_question_answered,
		vector<AbstractRuntimeQuestion *> & p_last_question_visited,
		const std::vector <AbstractRuntimeQuestion*> question_list,
		std::map <string, question_disk_data*> * qdd_map_ptr,
		const vector <named_attribute_list *> & p_named_attribute_list_vec,
		const map <string, vector <int> > & p_map_randomization_order);

#endif /* qscript_lib_h */
