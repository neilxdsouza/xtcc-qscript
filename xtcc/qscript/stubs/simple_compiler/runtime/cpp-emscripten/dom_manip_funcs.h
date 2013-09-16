#ifndef dom_manip_funcs_h
#define dom_manip_funcs_h

extern "C" {

void print_to_question_area(const char * question_text_ptr);
void print_to_stub_area (const char * question_type, int no_mpn, const char * stub_info, int counter);
void save_qnre_data(char * qnre_data);
void show_end_of_qnre_page();
void create_question_form (char * question_json_ptr, char * stubs_json_ptr);
//void print_to_question_response_area(const char * question_text_ptr);

}

#endif /* dom_manip_funcs_h */
